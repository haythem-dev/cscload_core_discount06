#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "types/messagecodeenum.inc"
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/bookingcompletedchecker/ibookingcompletedchecker.h>
#include <subseqdelivery/workupcompletedchecker/iworkupcompletedchecker.h>

/*----------------------------------------------------------------------------*/
/*  Cancel entire order or a specific item group.                             */
/*  Specify pxDVC_UNDEFINED to cancel all order items or a device type group  */
/*  to cancel items entered by a matching device type group.                  */
/*  For instance, specify pxDVC_DCT to cancel all order items transmitted via */
/*  a data communication device.                                              */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CancelOrder
(
    pxDeviceType t,
    Order::CancelArgs args
)

{
    ClearError();
    if ( !IsChangeable() )
        return ErrorState();

    if (!ItemList_ )                    // then order item processing not open
        return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
    if ( !(t == pxDVC_UNDEFINED || IsVideo(t) || IsDCT(t)) )
        return ExternalError(CMsgStream(), CMSG_ORD_INVALID_CANCEL, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsPseudoLock() )
    {
        if ( !IsLocked() )                  // order still locked ??
        {
            return ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
        }
    }

    if ( !(Param()->IsSCrema()) )
    {
        if (IsKreditLimitErreicht()  && args != Order::cCancel_UnConditional)
        {
            return ExternalError(CMsgStream(), CMSG_ORD_INVALID_CANCEL, KdAuftragNr_);
        }
    }
    if (IsSeparateArtGroup()  && args != Order::cCancel_UnConditional)
        return ExternalError(CMsgStream(), CMSG_ORD_INVALID_CANCEL, KdAuftragNr_);

    CancelRebateOrder();                    // unlock DKRAK records ( (BG application)
    if ( IsNoCics() )
    {
        if ( !(Session()->Device()->IsVideo()))
        {
            SetEntryDeferred();
            SetProblemClearance();
            ClearError();
        }
        else
        {
            return ErrorState();
        }
    }
    //CancelDebtLimitSumDayTurnOver();        // return WertLieferung_ to debtlimt(Crema)
    //UndoCreditDayTurnOver();                // return ordervalues to debtlimit(BG application)
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    pxOrderItem *item;

    pxDevice *dvcp = Session()->Device();
    if(IsNoDebtLimitCheck()) FirstTransPos_ = 0;

/*----------------------------------------------------------------------------*/
/*  Prevent entire cancel of existing deferred orders during OrderEntry on    */
/*  NonVideo Devices(DCT). Just cancel and delete the appended positions      */
/*  during the current transmission.                                          */
/*----------------------------------------------------------------------------*/
    if ( !(dvcp->IsVideo()) && !IsNewOrder() && FirstTransPos_ > 0 )
        iterator += FirstTransPos_;

    // SR-16070785 check ibt booking and delayed deliveries only in case of a real order
    bool mustCheckIBT = false;
    bool mustCheckSubSeqentialDelivery = false;
    if( false == this->isProductAvailabilityRequest() )
    {
        mustCheckIBT = Session()->getIbtComponentManager()->getBookingCompletedChecker()->isIBTBookingCompleted( FilialNr(), this->KdAuftragNr() );
        mustCheckSubSeqentialDelivery = Session()->getSudWorkupCompletedChecker()->isSUDWorkupCompleted( this->KdAuftragNr(), this->IDFNr() );
    }

//  Cancel all order items with a matching device type:
    while ( (item =  (pxOrderItem*) ++iterator) != NULL )
    {
        if ( mustCheckIBT )
        {
            if ( item->isIbtBookingCompleted() )
            {
                continue;
            }
        }

        if ( mustCheckSubSeqentialDelivery )
        {
            if ( Session()->getSudWorkupCompletedChecker()->isSUDWorkupCompleted( this->KdAuftragNr(), this->IDFNr(), item->PosNr() ) )
            {
                if ( checkReleasedDeliveryPosInSameOrder( this->KdAuftragNr(), item->ArtikelNr()) )
                {
                   mustCheckSubSeqentialDelivery = false;
                }
                else
                {
                   continue;
                }
            }
        }

        if ( (t == pxDVC_UNDEFINED)
              || ( IsVideo(t) && IsVideo(item->GeraetTyp()) )
              || ( IsDCT(t) && IsDCT(item->GeraetTyp()) ) )
        {
            if ( !(dvcp->IsVideo()) && !IsNewOrder() && FirstTransPos_ > 0 )
            {
                item->SetCancelAndDeleteItem();
//              item->CancelAndDeleteItem();
//              delete (pxOrderItem*)iterator.Remove();  // remove entry from list
            }
            else
            {
                if ( item->IsUnKnownProduct() )
                {
                    continue;
                }
                item->SetCancelItem();
//              item->CancelItem(pxOrderItem::CancelOptionDefault);
            }
        }
    }

    ItemList_->Sort(cASCENDING, pxOrderItemList::SortByArticleNo);
    iterator.Reset();
    while ( (item =  (pxOrderItem*) ++iterator) != NULL )
    {
        if (item->IsCancelItem())
        {
            item->CancelItem(pxOrderItem::CancelOptionDefault);
            item->ClearCancelItem();
        }
        if (item->IsCancelAndDeleteItem())
        {
            item->CancelAndDeleteItem();
            item->ClearCancelAndDeleteItem();
            delete (pxOrderItem*)iterator.Remove();  // remove entry from list
        }
    }
    ItemList_->Sort(cASCENDING, pxOrderItemList::SortByPosNr);

    if ( (t == pxDVC_UNDEFINED) )       // then cancel entire order
    {
        if ( !(dvcp->IsVideo()) && !IsNewOrder() && !IsNoDebtLimitCheck())
        {
            if ( !IsGoodState() )               // an error occurred
            {
                return ErrorState();
            }
            ReCountDCTPositions();        // recount
            Close(Order::EntryDeferred);         // just close order processing
        }
        else
        {
            if ( mustCheckIBT || mustCheckSubSeqentialDelivery) // hasAtLeastOneUncancellablePosition
            {
                SetEntryClosed();            // must do a normal close
            }
            else
            {
                OrderTourId_.Clear();              // clear route assignment
                SetCancelled();               // order entirely cancelled
            }
            CloseOrder();                 // must close order processing
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  a data communication device.                                              */
/*----------------------------------------------------------------------------*/
void
pxOrder :: ReCountDCTPositions
(
)
{
    pxOrderItemListIter iterator(*ItemList_); // define an iterator
    pxOrderItem *item;

    AnzPosDafue_         = 0;
    AnzAlphaText_        = 0;
    AnzPosDafueFehler_   = 0;

//  Count DCT positions
    while ( (item =  (pxOrderItem*) ++iterator) != NULL )
    {
        if ( (item->GeraetTyp() == pxDVC_DCT_SERIAL) ||
            (item->GeraetTyp() == pxDVC_DCT_PARALLEL) )
        {
            AnzPosDafue_++;               // count DCT items
            if ( item->IsDispoItem() )
            {
                AnzAlphaText_++;         // it was a text item
            }
            else if ( (!(item->IsArtStateGood() && item->IsQStateGood())    &&
                        item->QState() != pxOrderItem :: QStateLimitCheck ) ||
                        item->IsAuxPosted())
                AnzPosDafueFehler_++;      // any DC error or condition
        }
    }
}
