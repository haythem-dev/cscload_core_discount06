#include "pxcstbas.hpp"
#include "pxsess.hpp"
#include "pxgoodsdelivery.hpp"
#include "pxorder.hpp"
#include "pxholiday.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

extern pxOrderList* gBORDERLIST;
/*----------------------------------------------------------------------------*/
/* ParkDeliveryOrder: special methode for customers with NachLieferTyp = '7'  */
/* this Methode within the Interface Program pvhx01(Stockreceipt)      .      */
/*----------------------------------------------------------------------------*/
int
pxCustBase :: ParkDeliveryOrder
(
    pxGoodsDelivery*  GDentry,
    pxOrder**          order,
    pxOrderItem**      item
)
{
    pxHoliDayList* holidaylist = Session()->HoliDayList(Vertriebszentrum());
    nDate now;
//  no order available yet
    if ( !(*order) )
    {
        *order = FindBatchOrder( GDentry->DeliveryPos()->BatchAuftragNr());
        if ( *order != NULL)             // order found
        {
            (*order)->OpenOrder(cDBOPEN_INSERT);
            if (!(*order)->IsGoodState())
            {
                if (gBORDERLIST != NULL)
                    gBORDERLIST->Clear();
                delete *order;
                *order = NULL;
            }
        }
        if (!*order)
        {
            *order = new pxOrder(Session(), *this);
            if (!(*order)->IsGoodState() )
            {
                delete *order;
                *order = NULL;
                return ErrorState();
            }
            else
            {
                (*order)->SetBatchOrderNr(GDentry->DeliveryPos()->BatchAuftragNr());
                nMessage text(Session()->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                nString bem = text.String();
                bem.Compress('\n');
                (*order)->Bemerkungen(bem);
                (*order)->BatchSchreiben(cORTYPE_FR_CUSTOMER_ORDER);
                if ( (*order)->DatumAuslieferung() == pxConstants::NullDate )
                    (*order)->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,Vertriebszentrum())));
                (*order)->SetDDNotClose();
                (*order)->DafueAuftragNr((long)cDCTSequenceNumDDELMax);
                (*order)->SetVerzoegerAusgeliefert();
            }
        }
    }
    else
    {
        // order there but maybe customerchange
        if ( (*order)->IDFNr() != GDentry->IDFNr() ||
             (*order)->BatchAuftragNr() != GDentry->DeliveryPos()->BatchAuftragNr() )  // other Customer or Batchorder
        {
            (*order)->Close(Order::EntryClosed);      // close current order
            if (gBORDERLIST != NULL)
                gBORDERLIST->Clear();
            delete *order;
            *order = NULL;
            *order = FindBatchOrder( GDentry->DeliveryPos()->BatchAuftragNr());
            if (*order != NULL)             // order found
            {
                (*order)->OpenOrder(cDBOPEN_INSERT);
                if (!(*order)->IsGoodState())
                {
                    if (gBORDERLIST != NULL)
                        gBORDERLIST->Clear();
                    delete *order;
                    *order = NULL;
                }
            }
            if (!*order)
            {
                *order = new pxOrder(Session(), *this);
                if (!(*order)->IsGoodState() )
                {
                    Error() = (*order)->Error();
                    delete *order;
                    *order = NULL;
                    return ErrorState();
                }
                else
                {
                    (*order)->SetBatchOrderNr(GDentry->DeliveryPos()->BatchAuftragNr());
                    nMessage text(Session()->CMsgStream(), CMSG_ITM_RESTDELIVERY);
                    nString bem = text.String();
                    bem.Compress('\n');
                    (*order)->Bemerkungen(bem);
                    (*order)->BatchSchreiben(cORTYPE_FR_CUSTOMER_ORDER);
                    if ( (*order)->DatumAuslieferung() == pxConstants::NullDate )
                        (*order)->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,Vertriebszentrum())));
                    (*order)->SetDDNotClose();
                    (*order)->DafueAuftragNr((long)cDCTSequenceNumDDELMax);
                    (*order)->SetVerzoegerAusgeliefert();
                }
            }
        }
    }
    *item = (*order)->NewOrderItem_16(GDentry->DeliveryPos());   // make item
    if (*item != NULL)
    {
        nString itemtxt = (*item)->Bemerkungen();
        itemtxt.Strip();

        nMessage text(Session()->CMsgStream(), CMSG_ITM_RESTDELIVERY);
        nString bem = text.String();
        bem.Compress('\n');
        if ( itemtxt.IsEmpty() )
        {
            itemtxt += bem;
        }
        else
        {
            itemtxt = itemtxt + " " + bem;
        }
        (*item)->Bemerkungen(itemtxt);
        (*item)->SetBatchPosNr(GDentry->DeliveryPos()->BatchPosNr());
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* FindBatchOrder: searches for an deferred order depend on  BatchAuftragNr   */
/*----------------------------------------------------------------------------*/
pxOrder*
pxCustBase :: FindBatchOrder
(
    const long BatchAuftragNr
)
{
    // Read orders
    nDate now;
    if ( gBORDERLIST == NULL )
        gBORDERLIST = new pxOrderList(Session());
    gBORDERLIST->SelectBatchOrder(VertriebszentrumNr_, KundenNr_, "0001%", BatchAuftragNr,
                                  Order::EntryDeferred,
                                  Order::NOT_Invoiced,
                                  Order::NOT_Cancelled,
                                  Order::cStateLast);

    // Step through it
    pxOrderListIter orderiter(*gBORDERLIST);
    pxOrder* order = NULL;

    while ((order = (pxOrder*)++orderiter) != NULL)
    {
        if ( order->DatumAuslieferung() != pxConstants::NullDate )
            break;
    }
    return order;
}
