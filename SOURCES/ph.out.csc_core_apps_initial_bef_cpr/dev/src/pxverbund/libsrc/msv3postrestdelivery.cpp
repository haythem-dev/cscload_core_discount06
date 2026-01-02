#include "pxorder.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxoeparm.hpp"
#include "types/origintypeenum.inc"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/* This methode handles a List  of deliverable Restdelivery positions of the  */
/* current customer. The entries of the list are only released for MSV3       */
/* orders with a default orderlabel. If the current order has no default      */
/* orderlabel, it looks for a deferred MSV3 order with default orderlabel,    */
/* if found, the posititions are booked to that order, otherwise a new order  */
/* will be opened with the default orderlabel and the position are released   */
/* to the new order.                                                          */
/*----------------------------------------------------------------------------*/
int  pxOrder :: MSV3PostRestDelivery(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::MSV3PostRestDelivery()" );
    int retval = 0;                                 // count items
    pxOrderList   *DeferredOrders_ = NULL;         // ptr to list deferred orders
    pxOrder* seporder              = NULL;         // separates order
    bool cNODELETE           = false;

    pxCustBase*  customer = Customer();
    const pxCustOrderType&    ot = OrderType();
    nDate today;
/*----------------------------------------------------------------------------*/
/*  Sanity check                                                              */
/*----------------------------------------------------------------------------*/
    if (!ot.IsNormal() )
    {
       return retval;
    }

    // Do nothing for Croatia . See Ticket SR-064132
    if( Session()->isCroatia())                // if Croatia
    {
       return retval;
    }

    //2015-01-14 Crema Problem mit abgetrenntem Defektauftrag
    if (IsSepDefectOrder() )
    {
       return retval;
    }

    // 2015-01-07 YB: do not add subsequent deliveries if it´s an VerbundAuftrag(batchschreiben == 1)
    if ( BatchSchreiben() == cORTYPE_AUXILIARY )
    {
       return retval;
    }
    // ignore customers with NachlieferTyp == 4 or 5
    // may be this is just a temporary change, so i did not changed the futher logik.
    if (customer->IsImmediateRestDeliveryUser() ||
        customer->IsParkRestDeliveryOrder()     ||
        customer->IsAskRestDeliveryUser() )
    {
       return retval;
    }

    if( isMSV3Order() && !hasDefaultOrderLabel() )
    {
        DeferredOrders_ = new pxOrderList(this->Session());
        seporder = getDeferredMSV3Order(DeferredOrders_,customer->IDFNr(),FilialNr(),ot.getDefaultOrderLabel());
        if ( seporder )
        {
            seporder->OpenOrder(cDBOPEN_INSERT);
            if ( !seporder->IsGoodState() )
            {
                BLOG_ERROR(libcsc::LoggerPool::getLoggerOrder(), seporder->ErrorMsg());
                delete DeferredOrders_;
                DeferredOrders_ = NULL;
                seporder = NULL;
            }
            else
            {
                cNODELETE = true;
            }
        }

        if ( seporder == NULL )
        {
            seporder = new pxOrder(Session(), *customer);
            if ( !seporder->IsGoodState() )
            {
                BLOG_ERROR(libcsc::LoggerPool::getLoggerOrder(), seporder->ErrorMsg());
                ClearError();
                delete seporder;
                seporder = NULL;
            }
            else
            {
                seporder->OrderType(KdAuftragArt_,KoArt_,BuchArt_);
                seporder->SetDefaultOrderLabel();
                seporder->SetOrderPeriodID(this->OrderPeriodID());
                seporder->SetRouteForOrderSeparation(TourId(), DatumAuslieferung());
            }
        }
        if ( seporder)
        {
            retval = seporder->releaseRestDeliveryItems(dlist);
            if ( seporder->IsGoodState() )
            {
                if (seporder->AnzPos() == 0)
                {
                    seporder->CancelOrder(pxDVC_UNDEFINED);
                }
                else if ( seporder->IsOrderConsolidation() )
                {
                    seporder->Close(Order::EntryDeferred);   // set order state flags
                }
                else
                {
                    seporder->Close(Order::EntryClosed);   // set order state flags
                }
            }
            else
            {
                seporder->SetProblemClearance();
                seporder->Close(Order::EntryDeferred);   // set order state flags
                BLOG_ERROR(libcsc::LoggerPool::getLoggerOrder(), seporder->ErrorMsg());
            }
            if (!cNODELETE)
            {
                delete seporder;
            }
            if (  DeferredOrders_ )
            {
                delete DeferredOrders_;
            }
            return retval;
        }
    }

    retval = releaseRestDeliveryItems(dlist);
    if ( IsGoodState() )                      // if all ok, then
       return retval;                          // return count

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* This methode searches for a deferred MSV3 order with a default orderlabel  */
/* for the current customer. If found, the pxOrder pointer will be returned,  */
/* otherwise NULL ponters goes back to the caller                             */
/*----------------------------------------------------------------------------*/
pxOrder*  pxOrder :: getDeferredMSV3Order(pxOrderList* DeferredOrders, const long IDFNr, const short branchno,  const nString& _orderlabel)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::getDeferredMSV3Order()" );

    pxOrder*       seporder = NULL;

    if ( !IsChangeable() )
       return seporder;

    DeferredOrders->SelectByCustomerNo(IDFNr, "", "",branchno,
                         Order::NOT_EntryInProgress,
                         Order::NOT_UpdateInProgress,
                         Order::NOT_ProblemClearance,
                         Order::EntryDeferred,
                         Order::cStateLast );

    pxOrderListIter it(*DeferredOrders);
    while ( (seporder = (pxOrder*) ++it) != NULL )
    {
        if( !isMSV3Order() )
        {
            continue;
        }

        if ( seporder->BatchSchreiben() != BatchSchreiben() )
        {
            continue;
        }

        if ( !seporder->isOrderLabelEqual(_orderlabel) )
        {
            continue;
        }

        /*if ( seporder->DatumAuslieferung() != pxConstants::NullDate && DatumAuslieferung != pxConstants::NullDate )
        {
            if ( seporder->DatumAuslieferung() != DatumAuslieferung )
            {
                continue;
            }
        }*/
        if ( KdAuftragArt_ == seporder->KdAuftragArt() &&
             BuchArt_      == seporder->BuchArt()      &&
             KoArt_        == seporder->KoArt() )
        {
            break;
        }
    }
    return seporder;
}


