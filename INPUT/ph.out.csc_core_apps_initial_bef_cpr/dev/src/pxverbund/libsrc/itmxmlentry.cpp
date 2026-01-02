#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxartsto.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "types/origintypeenum.inc"
#include "pxstockbooking.hpp"
#include "pxttype.hpp"
#include "pxvartikellokallist.hpp"
#include <logger/loggerpool.h>
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to check for Stockinformations on XML        */
/*  Stock Demand Functions.                                                   */
/*----------------------------------------------------------------------------*/
int pxOrderItem :: AvailabilityQuery( const long  ArtikelNr )
{
    ArtikelNr_     = ArtikelNr;
    PosTyp_        = TypeProductStocked;

    if ( ArtBase(cDBGET_READONLY) )     // read  product base object
    {
       if ( !ArtBase_->IsGoodState() )
       {
          if ( pxGlobalNoDatabaseWrite)
             pxGlobalNoWriteToLog = true;
          FehlerArtikel_ = ArtStateNotFound;
          PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtikelNr_);
          pxGlobalNoWriteToLog = false;
          HandleError();                   // product or return the error
          return ErrorState();
       }

       if (ArtBase_->IsNotSaleable())
       {
          ArtBase_->Put();              // unlock artbase
          return ErrorState();
       }

       if (ArtBase_->IsStopSelling())   // stock difference
       {
          FehlerMenge_ |= QStateNotOnHand;
          //PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
          ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
          SetInhibitTransferBem();         // do not transfer text to pharmos
          HandleError();                   // product or return the error
          return ErrorState();
       }
       // Authorization check:
       if (!(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
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
       if ( ArtBase_->IsKzPsychoStoffe() && !(Order().Customer()->IsPsychoAllowed()))
       {                                // then: customer no authorized
          FehlerArtikel_ = ArtStateNotAuthorized;
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

       if ( ArtBase_->IsNotViaDCT() || ArtBase_->IsNotViaXML() )
       {
          if ( !Session()->Device()->IsVideo() )      // is DCT (data communication terminal)
          {
             ArtBase_->Put();                         // unlock artbase
             FehlerArtikel_ = ArtStateNotOverDct;     // Info for caller
             FehlerMenge_  |= QStateNotOnHand;
             MengeBestellt_ = 0; //Menge;
             if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
             {
                CodeBlocage_ = ArtBase_->CodeBlocage();
                nString CBPrintCode;
                nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                ExternalError(pCode);
                //ArtBase_->ExternalError(pCode);
                //nError::operator = (ArtBase_->Error()); // copy error object
                HandleError();                   // product or return the error
                return ErrorState();
             }
             else
             {
                HandleError();
                return ErrorState();
             }
          }
       }

       if ( ArtBase_->IsGoodState() )           // NO errors
       {
           MengeGeliefert_ = Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_, *Order().Customer());
           if ( MengeGeliefert_ > 0 )
           {
              MengeGeliefert_ = CheckArtQuota(MengeGeliefert_);
           }
           else  // Verbund möglich???
           {
              pxVartikelLokalList ibtList(Session(), Order().Param());
              ibtList.getIBTWarehouseStockListWithoutTimeCheck( ArtBase_->ArtikelNr(), ArtBase_->FilialNr(), Order().IDFNr(), &Order() );
              pxVartikelLokal* stp = ibtList.QuantityInList(1);
              if (stp)
              {
                 MengeMoeglich_ = stp->Bestand();
              }
              else
              {
                 FehlerMenge_ |= QStateNotOnHand;
              }
           }
       }
    }
    else                                // could not find product
    {
       FehlerArtikel_ = ArtStateNotFound;
       PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
       HandleError();                   // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using long  input.         */
/*  Mainly used when invoked via the XML Order Entry Interface                */
/*  This function is used for product Stock Informations depend on what is    */
/*  comming in as QuanOrdered                                                 */
/*   - QuanOrdered  = 0    non concrete demand, is used just for green or red */
/*   - QuanOrdered  > 0    concrete demand, now it depends on Customers       */
/*                         XMLInfoLevel what kind of Information is returned  */
/*                         back to the caller                                 */
/*  errors set in the nError object instance are cleared. This allows for     */
/*  entering an order item under nearly all circumstances.                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: NewOrderItemQuery
(
    const long ProductId,           // article identification
    const long QuanOrdered         // quantity ordered
)
{
    std::stringstream s;
    s << "pxOrderItem::NewOrderItemQuery(ProductId=" << ProductId <<", QuanOrdered=" << QuanOrdered << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());

    pxCustBase& customer = *(Order().Customer());
    long        Qty = QuanOrdered;

    // Check incoming QuanOrdered to prevent bad use
    if ( !customer.IsInfoLevelNoLimit() )    // new feature Middle Level = 4 No Limit
    {
        if (Order().Param()->MaxQtyRequest() == 0 )
        {
           Qty = ((QuanOrdered) > 99 ? 99 : QuanOrdered);
        }
        else
        {
           Qty = ((QuanOrdered) > (Order().Param()->MaxQtyRequest()) ? Order().Param()->MaxQtyRequest() : QuanOrdered);
        }
    }

    // non concrete demand
    if ( QuanOrdered == 0 )
    {
        AvailabilityQuery(ProductId /*, Qty, TypeProductStocked, bPOST_DEFAULT*/);
        return ErrorState();
    }

    //concrete demand
    if ( QuanOrdered > 0 )
    {
       if ( customer.IsNoInfoLevel() )     // not allowed for new feature
       {
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_INFO, customer.KundenNr());
         //HandleError();                   // product or return the error
          return ErrorState();
       }

       if ( customer.IsInfoLevelLow() )     // new feature Low Level = 1
       {
          InitOrderItem_Core(ProductId, Qty, 0, QuanOrdered, BookingTypeDefault, TypeProductStocked, bPOST_DEFAULT);
          return ErrorState();
       }

       if ( customer.IsInfoLevelMiddle() )  // new feature Middle Level = 2
       {
          InitOrderItem_Core(ProductId, Qty, 0, QuanOrdered, BookingTypeDefault, TypeProductStocked, bPOST_DEFAULT);

          return ErrorState();
       }

       if ( customer.IsInfoLevelNoLimit() )  // new feature Middle Level = 4
       {
          InitOrderItem_Core(ProductId, Qty, 0, QuanOrdered, BookingTypeDefault, TypeProductStocked, bPOST_DEFAULT);

          return ErrorState();
       }

       if ( customer.IsInfoLevelHigh() )    // new feature Middle Level = 3
       {
          InitOrderItem_Core(ProductId, Qty, 0, QuanOrdered, BookingTypeReserveCustomerStock, TypeProductStocked, bPOST_DEFAULT);
       }
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* CompleteIItemQueryResult: this method  checks the result of the XML        */
/* ItemQuery methodes. At the moment this methode just works depend on        */
/* Customer XMLInfoLevel 3 (HighLevelInfo with Article Reservation)           */
/* Take care for a well constructed pxOrderItem object                        */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CompleteItemQueryResult
(
)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxOrderItem::CompleteItemQueryResult()");

    if ( !Order().Customer()->IsInfoLevelHigh() )        // = 3
        return ErrorState();

    if  ((MengeBestaetigt_ - MengeVerbund() ) > 0 )
    {
        // TimeCheck = StockResevation Allowed ??
        if( Order().StockReservTimeList()->TimeInWindow() )
            return ErrorState();

        pxGlobalNoDatabaseWrite = false;
        nDBBeginTransaction(cDBTransSet); // Begin data base transaction

        long QtyToReserve = (MengeBestaetigt_ - MengeVerbund());
        MengeReserviert_ = Session()->getStockBooking()->AddReservationForInfoOrder(*ArtBase_, *Order().Customer(), QtyToReserve);

        if (Session()->getStockBooking()->IsGoodState())
        {
            nDBCommit(cDBTransSet);
        }
        else
        {
            nDBRollBack();                   // and rollback updates
        }
        pxGlobalNoDatabaseWrite = true;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* ArticleExpireDate : returns the expiredate of the current article object   */
/* Returnvalues: YYYYMMDD if DatumVerfall exits within table                  */
/*               ArtikelLagerOrt                                              */
/*               otherwise  zero                                              */
/* Take care for a well constructed pxOrderItem object                        */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: ArticleExpireDate
(
)
{
    long expiredate = 0;
    pxArtStoreLoc*      storeloc = NULL;
    if ( ArtBase_ )
    {
       storeloc = new pxArtStoreLoc(Session(), ArtikelNr_, ArtBase_->FilialNr(),
                                    ArtBase_->LagerBereichNr(),
                                    ArtBase_->LagerFachNr());
       if ( storeloc->IsGoodState())
       {
          long a = storeloc->DatumVerfall();    // comes as YYMM
          if (a == 0 )                           // no date
          {
             delete storeloc;
             return  expiredate;
          }
          long b = a/100;                       // = YY
          expiredate = 2000;
          expiredate = (( expiredate+b)*10000) + ((a%100)*100)+1;
          delete storeloc;
       }
    }
    return  expiredate;
}
/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to check for Stockinformations on XML        */
/*  Stock Demand Functions.                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: NewOrderItemInfo
(
    const long  ArtikelNr,             // must read ArtBase via this number
    const long  Menge                  // quantity ordered
)
{
    pxCustBase&          customer = *(Order().Customer());
    ArtikelNr_     = ArtikelNr;           // copy these
    PosTyp_        = TypeProductStocked;  // into self
    long          Qty = Menge;

    // Check incoming QuanOrdered to prevent bad use
    if ( !customer.IsInfoLevelNoLimit() )    // new feature Middle Level = 4 No Limit
    {
        if (Order().Param()->ReserveMaxQty() == 0 )
        {
           Qty = ((Menge) > 99 ? 99 : Menge);
        }
        else
        {
           Qty = ((Menge) > (Order().Param()->ReserveMaxQty()) ? Order().Param()->ReserveMaxQty() : Menge);
        }
    }

    if ( ArtBase(cDBGET_READONLY) )     // read  product base object
    {
       if ( !ArtBase_->IsGoodState() )
       {
          if ( pxGlobalNoDatabaseWrite)
             pxGlobalNoWriteToLog = true;
          FehlerArtikel_ = ArtStateNotFound;
          PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtikelNr_);
          pxGlobalNoWriteToLog = false;
          HandleError();                   // product or return the error
          return ErrorState();
       }

       if (ArtBase_->IsNotSaleable())
       {
          return ErrorState();
       }

       if (ArtBase_->IsStopSelling())   // stock difference
       {
          FehlerMenge_ |= QStateNotOnHand;
          // PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
          ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
          SetInhibitTransferBem();         // do not transfer text to pharmos
          HandleError();                   // product or return the error
          return ErrorState();
       }
       // Authorization check (skipped if server's auto item posting is active):
       if ( !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
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
       if ( !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
           (ArtBase_->IsKzPsychoStoffe()) && !(Order().Customer()->IsPsychoAllowed()))
       {                                // then: customer no authorized
          FehlerArtikel_ = ArtStateNotAuthorized;
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

       if ( ArtBase_->IsNotViaDCT() || ArtBase_->IsNotViaXML() )
       {
          if ( !Session()->Device()->IsVideo() )      // is DCT (data communication terminal)
          {
             FehlerArtikel_ = ArtStateNotOverDct;     // Info for caller
             FehlerMenge_  |= QStateNotOnHand;
             MengeBestellt_ = Menge;
             if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
             {
                CodeBlocage_ = ArtBase_->CodeBlocage();
                nString CBPrintCode;
                nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                ExternalError(pCode);
                //ArtBase_->ExternalError(pCode);
                //nError::operator = (ArtBase_->Error()); // copy error object
                HandleError();                   // product or return the error
                return ErrorState();
             }
             else
             {
                HandleError();
                return ErrorState();
             }
          }
       }

       if ( ArtBase_->IsGoodState() )           // NO errors
       {
           long QInStock = Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_);
           bool isShortage = ( QInStock < Qty );
           long qtyRequested = Qty;
           if ( QInStock < Qty )
           {
              Qty = QInStock;
           }
           MengeGeliefert_ = Qty;
           if ( MengeGeliefert_ > 0 )
           {
              MengeGeliefert_ = CheckArtQuota(MengeGeliefert_);
           }
           bool isQuota = ( MengeGeliefert_ < Qty );
           if ( MengeGeliefert_ == 0 )
           {
              FehlerMenge_  |= QStateNotOnHand;
           }

           if( !isShortage ||
               isQuota )
           {
               return ErrorState();
           }

            // evaluating inter branch transfer amount
            long shortage = qtyRequested - MengeGeliefert_;
            pxVartikelLokalList * auxStoreList = AuxStoreLocList();
            pxVartikelLokal * maxAmountVartikelLokal = auxStoreList->QuantityInList( shortage );
            if( NULL != maxAmountVartikelLokal )
            {
                MengeMoeglich_ = ( shortage < maxAmountVartikelLokal->Bestand() ? shortage : maxAmountVartikelLokal->Bestand() );
            }

            // check subsequent delivery
            if(    0 < MengeMoeglich_
                && qtyRequested <= ( MengeGeliefert_ + MengeMoeglich_ ) )
            {
               return ErrorState();
            }

            // check possibility of subsquent delivery/Dispo
            const pxArtFlags& artflag = ArtBase()->ArtFlags();
            const pxArtClass& artclass = ArtBase()->ArtClass();
            if( artflag.IsAusserHandel()    ||
                IsAuxPosted()               ||
                artclass.IsOpiat()          ||
                artflag.IsEinkaufsSperre()  ||
                artflag.IsAuslaufArtikel() )
            {
                MengeNLMoeglich_ = 0;
                MengeDispoMoeglich_ = 0;
                return ErrorState();
            }

            MengeNLMoeglich_ = qtyRequested - MengeGeliefert_;

            if( !artflag.IsArtikelGefuehrt() && !ArtBase()->IsRestDelivery() )
            {
                if( artflag.IsAusserHandel()             ||
                    IsAuxPosted()                        ||
                    artflag.IsNichtGeliefertHersteller() ||
                    artflag.IsNichtLieferbarHersteller() ||
                    artflag.IsNichtUeberGrossHandel() )
                {
                    MengeDispoMoeglich_ = 0;
                    return ErrorState();
                }
                MengeDispoMoeglich_ = qtyRequested - MengeGeliefert_;
            }
        }
    }
    else                                // could not find product
    {
       FehlerArtikel_ = ArtStateNotFound;
       PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
       HandleError();                   // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}
