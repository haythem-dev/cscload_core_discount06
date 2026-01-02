#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcalcdiscount.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to identify and order stocked products.      */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CalcOrderItem
(
    const long  ArtikelNr,             // must read ArtBase via this number
    const long  Menge,                 // desired product quantity
    const long  MengeNatra,            // quantity in kind
    const long  MengeNachfrage,        // quantity in kind
    BookingType  btype,                 // item/quantity booking type
    ItemType     PosTyp,                // product identification mode
    int          flags                  // internal posting flags
)
{
    ArtikelNr_     = ArtikelNr;         // copy these
    PosTyp_        = PosTyp;            // into self

    if ( ArtBase(cDBGET_READONLY) )     // read only
    {
       if ( !ArtBase_->IsGoodState() )
       {
          if ( pxGlobalNoDatabaseWrite)
             pxGlobalNoWriteToLog = true;
          FehlerArtikel_ = ArtStateNotFound;
          MengeBestellt_ = Menge;
          PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtikelNr_);
          pxGlobalNoWriteToLog = false;
          HandleError();                   // product or return the error
          return ErrorState();
       }

       if (ArtBase_->IsNotSaleable())
       {
           if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
           {
              CodeBlocage_ = ArtBase_->CodeBlocage();
              nString CBPrintCode;
              nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
              ExternalError(pCode);
          }
          else
          {
              ExternalCondition(CMsgStream(), CMSG_ART_NOTACTIVE, ArtikelNr_);
          }
          FehlerArtikel_ = ArtStateNotFound;
          MengeBestellt_ = Menge;
          HandleError();                   // product or return the error
          return ErrorState();
       }

       if (ArtBase_->IsStopSelling())   // stock difference
       {
          FehlerMenge_ |= QStateNotOnHand;
          MengeBestellt_ = Menge;
          //PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
          ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
          SetInhibitTransferBem();      // do not transfer text to pharmos
          HandleError();                   // product or return the error
          return ErrorState();
       }

       // Authorization check (skipped if server's auto item posting is active):
       if ( !(flags & bPOST_AUTO_ITEM) &&
            !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
            !(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
       {                                // then: customer no authorized
          FehlerArtikel_ = ArtStateNotAuthorized;
          MengeBestellt_ = 0;
          if ( Session()->Device()->IsVideo() )      // just for video devices
          {
             ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
          }
          else
          {
             ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
          }
          HandleError();
          return ErrorState();
       }
       // Check Psychotropical stuff:
       if ( !(flags & bPOST_AUTO_ITEM) &&
            !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
           (ArtBase_->IsKzPsychoStoffe()) && !(Order().Customer()->IsPsychoAllowed()))
       {                                // then: customer no authorized
          FehlerArtikel_ = ArtStateNotAuthorized;
          MengeBestellt_ = 0;
          if ( Session()->Device()->IsVideo() )      // just for video devices
          {
             ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
          }
          else
          {
             ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
          }
          HandleError();
       }
       else
       {                                // post item:
          if ( PostOrderQuantity(Menge, MengeNatra, MengeNachfrage, btype, flags, cDEFAULT)
               == nSTATE_GOOD )
          {
             ;
          }
          else
          {
             HandleError();
          }
       }
    }
    else                                // could not find product
    {
       FehlerArtikel_ = ArtStateNotFound;
       MengeBestellt_ = Menge;
       PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
       HandleError();                   // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to identify and order stocked products.      */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemDiscountInfo
(
    const long  ArtikelNr              // must read ArtBase via this number
)
{
    ArtikelNr_     = ArtikelNr;         // copy these

    if ( !ArtBase() || !ArtBase()->IsGoodState() )     // read only
    {
       FehlerArtikel_ = ArtStateNotFound;
       //MengeBestellt_ = Menge;
       PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
       HandleError();                   // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SaveArtDiscountInfoList                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: SaveArtDiscountInfoList
(
    pxDiscountList* dlist,               // must read ArtBase via this number
    pxCalcDiscountList* calclist,
    long QOrdered
)
{
    int  retval = 0;
    pxDiscountListIter iter(*dlist);
    pxDiscount*        dlistentryp;
    pxDiscount*        newentryp;

    if ( !IsProFormaBooking() )
       return retval;

    if ( dlist == NULL )
       return retval;
    if ( dlist->Entries() == 0 )
       return retval;

    if ( !ArtDiscountList_ )
    {
       ArtDiscountList_ = new pxDiscountList(Session() );
       while ( (dlistentryp = (pxDiscount*) ++iter) != NULL )
       {
          newentryp = new pxDiscount(*dlistentryp);
          ArtDiscountList_->Append(newentryp);
       }
    }

    pxDiscountListIter cursor(*ArtDiscountList_);
    while ( (newentryp = (pxDiscount*) ++cursor) != NULL )
    {
       if ( newentryp->GrossProfitPct() > pxConstants::dZero )
       {
           pxCalcDiscount* calcp = calclist->BestBuyGrossProfitPct();
          if (calcp)
          {
             newentryp->DiscountValuePct(CalcDiscountPercentage(newentryp->GrossProfitPct(), calcp->CascadeLevel(), QOrdered));
          }
       }
    }

    return retval;
}
int pxOrderItem ::bookDiscountValPctManProforma( double value)
{
    pxGlobalNoDatabaseWrite = true;
    SetDiscountValPctMan(value);
    ItemUpdateDiscountList();
    pxGlobalNoDatabaseWrite = false;
    return ErrorState();
}
