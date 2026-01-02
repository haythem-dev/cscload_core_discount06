#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxholiday.hpp"
#include "pxeventreason.hpp"
#include "pxordvtr.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"
#include "tourassignmentutil.hpp"

/*----------------------------------------------------------------------------*/
/* DayNightMergeProcessing                                                    */
/* The current Order(*this) will be scanned for IBT article to be placed in a */
/* separate order in Branch calculated be destBranchNo.                       */
/* Ibtposq is count of ibt positions within this order                        */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: DayNightMergeProcessing
(
    int& IbtPosq
)
{
    nDate today;
    Order::States State = Order::LeaveAsIs;
    nString KdAuftragArt;                   // ordertype
    pxOrder* seporder                 = NULL;         // separates order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();
    pxCustBase* destCustomer = NULL;
    pxOrderList   *DeferredOrders_ = NULL; // ptr to list deferred orders
    long MengeVerbund = 0;
    long QtyOrdered   = 0;
    pxCustRouteList*      rl = NULL;
    //pxCustRoute*     rlentry = NULL;
    bool cNODELETE           = false;
    short destBranchNo      = 0;
    long  itemDepartureDate = 0;

/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/

    if ( IbtPosq == 0 )
    {
       return State;
    }
    if ( !isDayNightMergeNecessary() )
    {
        return State;
    }

    // try to do daynightmerge
    destBranchNo = customer->GetDayNightDestBranchNo();
    if (destBranchNo == 0 )
    {
       return State;               // do not try to split it again(anchor)
    }
    // just for non workedup IBT positions for destBranchNo
    if ( CountIBTDestinationBranchItems( destBranchNo ) == 0 )
    {
        return State;
    }
    if (Param()->IsSIbtCstOrg() && ( Session()->isFrance() || Session()->isFrancePrewhole() ) )
    {
       RangeCalculation();                 // do just RangeCalculation to include ibtpos
    }

    if ( seporder == NULL )
    {
       itemDepartureDate = getDayNightMergeIBTPositionDepartureDate(destBranchNo);
       DeferredOrders_ = new pxOrderList(Session());
       seporder = GetOrderFromDestBranch(DeferredOrders_, Customer_->IDFNr(), destBranchNo, itemDepartureDate );
       // Open the order for update
       if ( seporder )
       {
          seporder->OpenOrder(cDBOPEN_INSERT);
          if ( !seporder->IsGoodState() )
          {
             delete DeferredOrders_;
             return State;
          }
          cNODELETE = true;
       }
       else
       {
          destCustomer =  new pxCustBase(Session(), destBranchNo, IDFNr_);
          if ( !(destCustomer->IsGoodState()) )          // then customer not found
          {
             SetProblemClearance();  // manual clearance required
             State = Order::EntryDeferred;
             SetEventCode(pxEventReason::CustomerError);
             ClearError();
             delete DeferredOrders_;
             delete destCustomer;
             return State;
          }
          if ( destCustomer->Flags().IsKundeGesperrt() )
          {
             SetProblemClearance();  // manual clearance required
             State = Order::EntryDeferred;
             SetEventCode(pxEventReason::CustomerError);
             ClearError();
             delete DeferredOrders_;
             delete destCustomer;
             return State;
          }
          seporder = new pxOrder(Session(),*destCustomer);
          if ( !seporder->IsGoodState() )
          {
             SetProblemClearance();  // manual clearance required
             State = Order::EntryDeferred;
             SetEventCode(pxEventReason::CustomerError);
             ClearError();
             delete seporder;
             seporder = NULL;
             delete DeferredOrders_;
             delete destCustomer;
             return State;
          }
          seporder->OrderType(KdAuftragArt_,KoArt_,BuchArt_);
          seporder->SetTenderNo(TenderNo_);
          // maybe combination or ordertype is not available
          if (!seporder->IsGoodState() )
          {
             SetProblemClearance();  // manual clearance required
             State = Order::EntryDeferred;
             SetEventCode(pxEventReason::ErrorOnMethodeOrderType);
             ClearError();
             delete seporder;
             seporder = NULL;
             delete DeferredOrders_;
             delete destCustomer;
             return State;
          }
          rl = seporder->RouteList();
          if (rl)
          {
             //if ( !(Session()->Device()->IsVideo()) )
             //{
                seporder->RouteAssign();                // assign a default route
             //}
             /*
             if ( !(seporder->TourId().IsEmpty()) )
             {
                rlentry = rl->FindNextAllocatableRoute(seporder->TourId());
                if (rlentry )
                {
                   seporder->SetTourId( rlentry->TourId());
                }
             }
             */
          }
          // reload Session()->Branch_, because Session()->Branch_ is now positioned to
          // destination branch, while read customer from destination branch
          if  ( Customer_ )
          {
             Customer_->ReloadSessionCustomerBranch();
          }
       }
    }

    // Now scan this order for IBT article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->IsDayNightMergePosition() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if (item->IsAuxPosted() )
       {
          if ( item->VerbundFilialNr() != destBranchNo )
             continue;
          if ( item->isIbtBookingCompleted() )
             continue;

//          // check whether day night mege or normal IBT delivery is faster
//          bool DNMFaster = item->Order().getTourAssignmentUtil()->isDayNightMergeDeliveryFaster( item, destBranchNo );
//          if (DNMFaster == false)
//             continue;

          if ( seporder->Param()->IsSDiscountCalcBaseQtyConfirmed() )
          {
             QtyOrdered = item->MengeVerbund();
          }
          else
          {
             QtyOrdered = item->MengeBestellt();
          }
          //MengeVerbund = item->MengeVerbund();        // save Verbundmenge
          //first undo auyposting on src
          item->nDBBeginTransaction(cDBTransRecord);
          // prevent deleting pxdeliverypos(IBT)
          item->SetIBTPosDayNightMerge();
          item->UndoAuxPosting();
          item->ClearIBTPosDayNightMerge();
          item->CancelArtQuota();
          Error() = item->Error();
          if ( IsGoodState() )
          {
             item->nDBCommit(cDBTransRecord);
          }
          else
          {
             item->nDBRollBack();
             break;
          }
          delitem = seporder->bookDayNightMergePosition(item, QtyOrdered, MengeVerbund);
          if (delitem->IsGoodState() )
          {
             delitem->UndoRedoItemDiscount(item);
             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();
             // now delete item members
             cleanupDayNightMergePosition(item, KdAuftragNr);
          }
       }
       else if ( isNonSatisfiedIBTPosition(item) )
       {
          if ( seporder->Param()->IsSDiscountCalcBaseQtyConfirmed() )
          {
             QtyOrdered = item->MengeVerbund();
          }
          else
          {
             QtyOrdered = item->MengeBestellt();
          }
          delitem = seporder->NewOrderItem_03(item->ArtikelNr(), QtyOrdered,0L,0L,
                    FREESALE_PRICE,
                    pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                    bPOST_IGN_LACK);
          //delitem = seporder->bookDayNightMergePosition(item, QtyOrdered, MengeVerbund);
          if (delitem->IsGoodState() )
          {
             delitem->UndoRedoItemDiscount(item);
             nString KdAuftragNr;
             KdAuftragNr = seporder->KdAuftragNr();
             // now delete item members
             cleanupDayNightMergePosition(item, KdAuftragNr);
          }
       }
    }

    if ( seporder )
    {
        if ( seporder->IsOrderConsolidation() )
        {
            seporder->Close(Order::EntryDeferred);   // set order state flags
        }
        else
        {
            seporder->Close(Order::EntryClosed);   // set order state flags
        }
        if (!cNODELETE)
        {
            delete seporder;
        }
    }
    if (  DeferredOrders_ )
    {
       delete DeferredOrders_;
    }
    if (destCustomer )
    {
       delete destCustomer;
    }
    return State;
}

/*----------------------------------------------------------------------------*/
/* GetOrderFromDestBranch                                                     */
/* This function looks for a deferred order for customer with given IDFNr and */
/* destination branchno                                                       */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  GetOrderFromDestBranch
(
    pxOrderList*    DeferredOrders,
    const long     IDFNr,
    const short    destBranchNo,
    long           itemDepartureDate
)
{
    pxOrder*       seporder = NULL;
    nDate today;

    if ( !IsChangeable() )
       return seporder;;
/*----------------------------------------------------------------------------*/
/*  First get the new customer from the database                              */
/*----------------------------------------------------------------------------*/
    pxCustBase    *newcustomer =  new pxCustBase(Session(), destBranchNo, IDFNr);
    if ( !(newcustomer->IsGoodState()) )          // then customer not found
    {
       ExternalError(CMsgStream(), CMSG_CST_NOTFOUND, IDFNr);
       return seporder;
    }

/*----------------------------------------------------------------------------*/
/*  Locate table entries for order type, commission type and stock transaction*/
/*  for the new customer                                                      */
/*----------------------------------------------------------------------------*/
    pxCustOrderType *ot = newcustomer->OrderTypeList()->Find(KdAuftragArt_,newcustomer->Vertriebszentrum(),newcustomer->KundenNr());
    pxCommType      *ct = Session()->CommTypeList(newcustomer->Vertriebszentrum())->Find(KoArt_,newcustomer->Vertriebszentrum());
    pxStockTrans    *st = Session()->StockTransList(newcustomer->Vertriebszentrum())->Find(BuchArt_,newcustomer->Vertriebszentrum());
    if ( !ot )
    {
       ExternalError(CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)KdAuftragArt_,IDFNr);
       return seporder;
    }
    if ( !ct )
    {
       ExternalError(CMsgStream(), CMSG_ORD_INVALID_COMMTYPE,(int)KoArt_);
       return seporder;
    }
    if ( !st )
    {
       ExternalError(CMsgStream(), CMSG_ORD_INVALID_STOCKTRANS,(int)BuchArt_);
       return seporder;
    }

    // Test for a valid combination:
    if ( !(Session()->OrderValidTransList(newcustomer->Vertriebszentrum())->Find(KdAuftragArt_, KoArt_ - '0', BuchArt_ - '0',newcustomer->Vertriebszentrum())) )
    {
       ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB,
                      (char*)KdAuftragArt_, (int) KoArt_, (int) BuchArt_);
       return seporder;
    }

    if ( !ot->IsOrderCons() )
    {
       return seporder;
    }

    DeferredOrders->SelectByCustomerNo(Customer_->IDFNr(), "", "",destBranchNo,
                         Order::NOT_EntryInProgress,
                         Order::NOT_UpdateInProgress,
                         Order::NOT_ProblemClearance,
                         Order::EntryDeferred,
                         Order::cStateLast );

    pxOrderListIter it(*DeferredOrders);
    while ( (seporder = (pxOrder*) ++it) != NULL )
    {
       if ( seporder->DatumAuslieferung().GetYYYYMMDD() != 0 )
       {
          if ( seporder->DatumAuslieferung().GetYYYYMMDD() != itemDepartureDate )
          {
             continue;
          }
       }
       else
       {
           if (itemDepartureDate != today.GetYYYYMMDD())
           {
               continue;
           }
       }
       if ( seporder->BatchSchreiben() != BatchSchreiben() )
       {
           continue;
       }

       if ( KdAuftragArt_ == seporder->KdAuftragArt() &&
            BuchArt_      == seporder->BuchArt()      &&
            KoArt_        == seporder->KoArt() )
       {
           break;
       }
    }
    return seporder;
}
/*----------------------------------------------------------------------------*/
/* isDayNightMergeNecessary                                                   */
/*----------------------------------------------------------------------------*/
bool pxOrder :: isDayNightMergeNecessary()
{
    bool  retval = false;
    pxCustBase* customer = Customer();

    if ( !Param()->IsSDayNightMerge())        // only if DayNightMerge Param
    {
       return  retval = false;
    }
    else
    {
        retval = true;
    }

    if ( IsPseudoLock() )                   // Do not Splitt if PreudoLock
    {
       retval = false;
    }

    if ( CommType_->IsNoShipment() )
    {
       retval = false;
    }

    if ( IsDoNotSplittOrder() )
    {
       retval = false;
    }
    if ( IsSeparatedOrder() )      // if oder already separated
    {
       retval = false;             // do not try to split it again(anchor)
    }
/*----------------------------------------------------------------------------*/
/*  Do not seperate  for Versandapo with BA order                             */
/*----------------------------------------------------------------------------*/
    if ( customer->Flags().IsVersandApo() && customer->Flags().IsBaAuftrag() )
    {
       retval = false;               // do not try to split it again(anchor)
    }

    if (CommType_->IsNoShipment() || CommType_->IsShipDisposal() || CommType_->IsShipDeliveryNote() )
    {
       retval = false;              // do not try to split it again(anchor)
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/* bookDayNightMergePosition                                                  */
/*----------------------------------------------------------------------------*/
pxOrderItem*  pxOrder :: bookDayNightMergePosition(pxOrderItem* item, const long QtyOrdered, const long QtyIBT)
{
    pxOrderItem* delitem = NULL;
    if ( item->PreisEKApoFree() != pxConstants::mZero )
    {
       // now rebook position in seporder with suivra ammount(MengeVerbund) and free price
       delitem = NewOrderItem_09(item->ArtikelNr(), QtyOrdered, (short)0 ,item->PreisEKApoFree(), 0L, QtyIBT,
                    FREESALE_PRICE,
                    pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                    bPOST_DEFAULT);
    }
    else if (item->MengeVerbund() >= QtyOrdered )
    {
       // now rebook position in seporder with QtyOrdered
       delitem = NewOrderItem_03(item->ArtikelNr(), QtyOrdered,0L,0L,
                    FREESALE_PRICE,
                    pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                    bPOST_DEFAULT);
    }
    else
    {
       // Partial IBT booking
       delitem =NewOrderItem_03(item->ArtikelNr(), QtyOrdered,0L,0L,
                   FREESALE_PRICE,
                   pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                   bPOST_IGN_LACK);
    }

    return delitem;
}
/*----------------------------------------------------------------------------*/
/* isNonSatisfiedIBTPosition                                                  */
/*----------------------------------------------------------------------------*/
bool pxOrder :: isNonSatisfiedIBTPosition(pxOrderItem* item)
{
    bool retval = false;
    if (!Session()->isFrancePrewhole() )
    {
        return retval;
    }
    if ( item->ArtBase()->IsAuxStockProduct() && item->MengeBestaetigt() == 0 && item->MengeBestellt() > 0 )
    {
        retval = true;
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/* cleanupDayNihgtMergePosition                                               */
/*----------------------------------------------------------------------------*/
int  pxOrder :: cleanupDayNightMergePosition(pxOrderItem* item, const nString& KdAuftragNr)
{
   item->MengeBestaetigt( 0L);
   item->MengeGeliefert( 0L);
   item->MengeAbgebucht( 0L);
   item->MengeNatra( 0L);
   nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_AUXDELIVERY_S,(char*)&KdAuftragNr);
   nString posbem = msg.String();
   posbem.Compress('\n');
   item->Bemerkungen(posbem);
   item->SetDayNightMergePosition();
   return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* getDayNightMergeIBTPositionDepartureDate                                   */
/*----------------------------------------------------------------------------*/
long pxOrder ::getDayNightMergeIBTPositionDepartureDate(const short destBranchno)
{
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    long departureDate = 0;
    // Now scan this order for IBT article
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->IsCancelled())
            continue;
        if (item->IsDayNightMergePosition())
            continue;
        if (item->ArtikelNr() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->IsAuxPosted())
        {
            if (item->VerbundFilialNr() != destBranchno)
                continue;
            if (item->isIbtBookingCompleted())
                continue;
            departureDate = item->getItemTourDate();
        }
    }
    return departureDate;
}