#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcsterm.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcustdisccondition.hpp"
#include "pxsubordertype.hpp"
#include <boost/numeric/conversion/cast.hpp>
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Return max. possible validity date for the current order type.            */
/*  Returns a null date if setting a validity date is inhibited for either    */
/*  the order type or the customer.                                           */
/*----------------------------------------------------------------------------*/
nDate
pxOrder :: GetMaxValDate
(
)
{
    nDate vdate;
    if ( Customer()->Flags().IsValutaSperre() || OrderType().IsNoValidity()
         || ( OrderType().ValMonths() <= 0 ) )
       vdate = pxConstants::NullDate;   // then validity date not allowed
    else                                // set to max value
       vdate.AddMonth(OrderType().ValMonths());
    return vdate;
}

/*----------------------------------------------------------------------------*/
/*  Set validity date in self. Returns current error state.                   */
/*  When running with a non-video device, the validity date is set to the     */
/*  maximum possible value if the date sanity check signalled an error.       */
/*----------------------------------------------------------------------------*/
int pxOrder::ValDate( const nDate& vdate )                // desired validity date
{
    if ( !IsChangeable() )
       return ErrorState();             // order not changeable for some reason

    nDate date(vdate);                  // guarantee constness
    if ( VerifyValDate(date) )          // then sanity check returned bad state
    {
       if ( Session()->Device()->IsVideo() ) // for a video device, we return
          return ErrorState();          // the error object's state
       ClearError();                    // Clear error condition, then set date
       date = GetMaxValDate();          // to max allowed value.
    }

    DatumValuta_ = date;                // set validity date in self
    SetDirty();                         // must update order record
    return ErrorState();
}

int pxOrder::ValDate(const basar::Date& date)
{
    nDate tmpDate(date.getDate());
    return ValDate(tmpDate);
}

/*----------------------------------------------------------------------------*/
/*  Add n months to current date, then set validity date in self to resulting */
/*  date.                                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ValDate
(
    const int  months
)
{
    nMoney           DiffValue(0.0);          // exceedance of  Creditlimit
    bool  valuedatenotNullDate = false;
    if ( months > 0)                    // then calc validity date
    {
       if ( DatumValuta_ !=  pxConstants::NullDate )
       {
          valuedatenotNullDate = true;
       }
       nDate vdate;                     // construct today's date value
       // maybe months = count of days p.e.in Serbia
       if ( Session()->isSerbia() || Session()->isBulgaria() || Session()->isGermany() )
       {
          vdate = vdate+ months;       // add just days
       }
       else
       {
          vdate.AddMonth(months);       // add desired number of months
       }
       ValDate(vdate);
       if ( Session()->isBulgaria() && AnzPos_ > 0 && !valuedatenotNullDate )
       {
          DiffValue = OrderValuesToCustomerDebtlimitK2();
          if ( DiffValue > pxConstants::mZero )             // credit limit exhausted
          {
             ValDate(nDate(0L));
             ExternalCondition(CMsgStream(),CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double) DiffValue);
             return ErrorState();
          }

          DiffValue = OrderValuesToCustomerDebtlimitK1();
          if ( DiffValue > pxConstants::mZero )             // credit limit exhausted
          {
             ValDate(nDate(0L));
             ExternalCondition(CMsgStream(),CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double) DiffValue);
             return ErrorState();
          }

       }

       return ValDate(vdate);           // and let this method do the real work
    }
    else
    {
       if ( Session()->isBulgaria() && AnzPos_ > 0 )
       {
          if ( DatumValuta_ !=  pxConstants::NullDate )
          {
             UndoCustomerDebtlimitK2();
             UndoCustomerDebtlimitK1();
          }
       }
       return ValDate(nDate(0L));       // clear validity date
    }
}

/*----------------------------------------------------------------------------*/
/*  Add n months to current date, then set validity date in self to resulting */
/*  date.                                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ValDateMonAuto
(
    const short months
)
{
    if ( months > 0)                    // then calc validity date
    {
       nDate vdate;                     // construct today's date value
       vdate.AddMonth(months);       // add desired number of months
       return ValDate(vdate);           // and let this method do the real work
    }
    else
       return ValDate(nDate(0L));       // clear validity date
}

/*----------------------------------------------------------------------------*/
/*  Return validity months calculation from the validity date currently set.  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ValMonth
(
)
{
    int retval = 0;
    long  years    = 0;
    long  months   = 0;
    long  days     = 0;
    if ( DatumValuta_ != pxConstants::NullDate && DateTimeCreated() != pxConstants::NullTime)
    {                                   // ensure dates are valid
       DatumValuta_.GetDiff(DateTimeCreated(), years, months, days);
       // maybe days have to be returned p.e.in Serbia
       if ( Session()->isSerbia() || Session()->isBulgaria() || Session()->isGermany() )
       {
           retval = (int) DatumValuta_.GetAbsday() - (int) nDate(DateTimeCreated()).GetAbsday();
       }
       else
       {
          retval = (int) months;
       }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Return validity months calculation from the validity date currently set.  */
/*----------------------------------------------------------------------------*/
short
pxOrder :: ValMonthManuellInMonths
(
)
{
    short retval = 0;
    long  years    = 0;
    long  months   = 0;
    long  days     = 0;
    if ( DatumValuta_ != pxConstants::NullDate && DateTimeCreated() != pxConstants::NullTime)
    {                                   // ensure dates are valid
        DatumValuta_.GetDiff(DateTimeCreated(), years, months, days);
        // maybe days have to be returned p.e.in Serbia
        retval = boost::numeric_cast<short>(months);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Return validity months calculation from the validity date currently set.  */
/*----------------------------------------------------------------------------*/
short
pxOrder :: ValMonthBatch
(
)
{
    short retval = 0;
    long  years    = 0;
    long  months   = 0;
    long  days     = 0;
    if ( DatumValutaBatch_ != pxConstants::NullDate && DateTimeCreated() != pxConstants::NullTime)
    {                                   // ensure dates are valid
        DatumValutaBatch_.GetDiff(DateTimeCreated(), years, months, days);
        retval = boost::numeric_cast<short>(months);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Validity date sanity check.                                               */
/*  Sets error object instance in self to contain the sanity check diagnostic.*/
/*----------------------------------------------------------------------------*/
int
pxOrder :: VerifyValDate
(
    const nDate&   vdate
)
{
    ClearError();                       // Set error object to good state
    if ( vdate != 0L )                   // Allow null date being passed thru
    {
       if ( !vdate.IsValid() )          // then invalid date format detected
          return ExternalError(CMsgStream(), CMSG_ORD_VALDATE_FORMAT);

       nDate today;                     // Contains this day's date now
       if ( vdate < today )             // validity date may not be < today's date
          return ExternalError(CMsgStream(), CMSG_ORD_VALDATE_LOW);

       if ( Customer()->Flags().IsValutaSperre() ) // inhibited for this customer
          return ExternalError(CMsgStream(), CMSG_ORD_VALDATE_CUST,
                               IDFNr());

       nDate maxvdate(GetMaxValDate()); // Will contain max allowed value for
                                        // current order type
       if ( !maxvdate.IsValid() )       // then: validity date setting not allowed
          return ExternalError(CMsgStream(), CMSG_ORD_VALDATE_ORDERTYPE,
                               (char*)(OrderType().KdAuftragArt()));

       if ( vdate > maxvdate )          // then: attempt to go off limits
          return ExternalError(CMsgStream(), CMSG_ORD_VALDATE_LIMIT,
                               (char*)(OrderType().KdAuftragArt()), OrderType().ValMonths());

    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Close validity  date                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void
pxOrder :: CloseValDate
(
)
{
    ClearError();                       // Set error object to good state
    pxCustBase&       customer = *Customer();
    pxCustTerms&        cterms = customer.Terms();
    const pxCustOrderType&        ot = OrderType();
    short              valday = cterms.TagAutoValuta();
    pxCustDiscCondition* CustCond = Customer_->CustDiscCondition();  // Customer discount conditions
    pxSubOrderType*      SubCond  = Customer_->SubOrderType();       // discountlist entryp
    short              CustCondValdays = 0;                         // count of days
    short              SubCondValdays  = 0;                         // count of days

    if ( (BatchSchreiben_ == cORTYPE_TRANSFER || BatchSchreiben_ == cORTYPE_BATCH_TRANSFER)
                                              && DatumValuta_ != pxConstants::NullDate )
       return;

    if ( IsNotUpdateValdate() )                         // order from Restdelivery System
    {
        return;
    }

    // Just pricetype
    if ( Session()->isBulgaria() && AnzPos_ > 0 )
    {
       if ( AnzPos_ == CountPriceTypeItems(RETAIL_PRICE) )
       {
          DatumValuta_ = pxConstants::NullDate;
          return;
       }
    }

    if ( CustCond != NULL && SubCond != NULL )          // for the french short list conditions
    {
       nDate now;                                       // current date
       CustCondValdays = CustCond->ValutaDays();        // Customers valdays
       SubCondValdays  = SubCond->ValutaDays();         // Subordertype valdays(discountlist)
       if (  CustCondValdays > 0 )                      // take Customers value
       {
           DatumValuta_ = now+CustCondValdays;
           return;
       }
       if (  SubCondValdays > 0 )                       // take discountlist value
       {
           DatumValuta_ = now+SubCondValdays;
           return;
       }
    }

    if ( OrderType().ValMonthsAuto() > 0 )
    {
       nDate maxvdate(GetMaxValDate()); // Will contain max allowed value for
       nDate  date;                     // current date
       long  cday = date.GetDay();     // get current day

       if ( !ot.IsTransfer() && !ot.IsScheduleQuantity()  && !ot.IsUnoTransfer() )
       {
          if ( valday == 0 || valday > cday )
             return;
       }

       if ( DatumValuta_ == pxConstants::NullDate )
       {
          date.AddMonth( OrderType().ValMonthsAuto()); // = current date + n Months
          DatumValuta_ = date;          // set validity date
       }
       else
       {
          DatumValuta_.AddMonth( OrderType().ValMonthsAuto()); // = DatumValuta + n Months
       }

       if ( maxvdate != pxConstants::NullDate )
       {
           DatumValuta_ = ( ( maxvdate > DatumValuta_) ? DatumValuta_ : maxvdate);
       }
       else
       {
           DatumValuta_ = pxConstants::NullDate;
       }
    }
}
/*----------------------------------------------------------------------------*/
/*  Close validity  date for Croatia                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void
pxOrder :: CloseValDateCroatia
(
)
{
    ClearError();                       // Set error object to good state
    pxCustBase&       customer = *Customer();
    pxCustTerms&        cterms = customer.Terms();
    const pxCustOrderType&        ot = OrderType();
    short           valdaymax = cterms.ValutaTageMax();
    nDate maxvdate(GetMaxValDate()); // Will contain  number of months
    nDate  date;                     // current date

    if ( (BatchSchreiben_ == cORTYPE_TRANSFER || BatchSchreiben_ == cORTYPE_BATCH_TRANSFER)
                                              && DatumValuta_ != pxConstants::NullDate )
       return;

    if ( ot.ValMonthsAuto() > 0 && valdaymax == 0 )
    {

       if ( DatumValuta_ == pxConstants::NullDate )
       {
          date.AddMonth( ot.ValMonthsAuto()); // = current date + n Months
          DatumValuta_ = date;          // set validity date
       }
       else
       {
          DatumValuta_.AddMonth( ot.ValMonthsAuto()); // = DatumValuta + n Months
       }

    }
    else if ( (ot.ValMonthsAuto() > 0   && valdaymax > 0 ) ||
              (ot.ValMonthsAuto() == 0 && valdaymax > 0 ))
    {
       date += (long)valdaymax;
       DatumValuta_ = date;
    }

    if ( maxvdate != pxConstants::NullDate && DatumValuta_ != pxConstants::NullDate)
    {
        DatumValuta_ = ( ( maxvdate > DatumValuta_) ? DatumValuta_ : maxvdate);
    }
    else
    {
        DatumValuta_ = pxConstants::NullDate;
    }
}

/*----------------------------------------------------------------------------*/
/*  ValMonthManuell: this methode uses DatumValuta and DatumValutaBatch to    */
/*  calculate ValutaMonManuell.                                               */
/*  Case 1:  DatumValuta > 0 and DatumValutaBatch = 0 and ValutaMonAuto = 0   */
/*  Case 2:  DatumValuta > 0 and DatumValutaBatch = 0 and ValutaMonAuto > 0   */
/*  Case 3:  DatumValuta > 0 and DatumValutaBatch > 0 and ValutaMonAuto = 0   */
/*----------------------------------------------------------------------------*/
void
pxOrder :: ValMonthManuell
(
)
{
    short monthsBatch = 0;

    ValutaMonAuto_ = OrderType().ValMonthsAuto();
    if ( DatumValuta_ == pxConstants::NullDate )
        return;

    if ( DatumValutaBatch_ == pxConstants::NullDate &&  ValutaMonAuto_ == 0 )
        ValutaMonManuell_ = ValMonthManuellInMonths();

    if ( DatumValutaBatch_ == pxConstants::NullDate &&  ValutaMonAuto_ > 0 )
    {
        ValutaMonManuell_ = ValMonthManuellInMonths();
        ValutaMonManuell_ -= ValutaMonAuto_;
        return;
    }

    if ( DatumValutaBatch_ != pxConstants::NullDate &&  ValutaMonAuto_ == 0 )
    {
        ValutaMonManuell_ = ValMonthManuellInMonths();
        monthsBatch = ValMonthBatch();
        ValutaMonManuell_ -= monthsBatch;
    }
    return;
}

/*----------------------------------------------------------------------------*/
/*  RestDeliveryValdate:                                                      */
/*  The Valdate is stored into the Restdelivery Positions within this order   */
/*  This methode looks for restdelivery positions within this order           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: RestDeliveryValdate
(
)
{
    pxOrderItem *item;
    pxOrderItemListIter it(*ItemList_);

/*----------------------------------------------------------------------------*/
/*  Prevent unnecessary overhead                                              */
/*----------------------------------------------------------------------------*/
    if ( DatumValuta() == pxConstants::NullDate )
       return ErrorState();

/*----------------------------------------------------------------------------*/
/*  Now scan the list of positions and update Restdelivery Items              */
/*----------------------------------------------------------------------------*/
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( !item->IsNachliefern() )
          continue;
       item->RestDeliveryValdate();
       Error() = item->Error();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* GetValutaDays;  Get Difference between DatumValuta and Current day         */
/* Returnvalue is count of days   or zero                                     */
/*----------------------------------------------------------------------------*/
long
pxOrder :: GetValutaDays
(
)
{
    long retval = 0;
    nDate now;
    if ( DatumValuta_ != pxConstants::NullDate && now != pxConstants::NullDate )
    {
       if ( DatumValuta_ > now )
       {
          long  currentdays     =  now.GetAbsday();
          long  ValutaDays      =  DatumValuta_.GetAbsday();
          retval  = ValutaDays - currentdays;
       }
    }
    return retval;
}
