#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstrou.hpp"
#include "pxcustrouteweek.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxdelpos.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxbranch.hpp"
#include "pxcstonr.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstprint.hpp"
#include "pxshuttlecustinfo.hpp"
#include "pxitemdiscount.hpp"
#include "pxorderitemtour.hpp"
#include "pxttype.hpp"
#include <base/irunnable.h>
#include <boost/shared_ptr.hpp>
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  ShuttleRouteAssign: new suivra France methode                             */
/*  It just works if Param()->IsSIbtCstOrg() (new Suivra in France).           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ShuttleRouteAssign
(
    const short BranchNo
)
{
    pxShuttleCustInfo*  ShuttleInfo = NULL;

    if ( ShuttleCustomer(BranchNo ) )
    {
        if ( this->TourId().IsEmpty() )
        {
            ShuttleInfo = new pxShuttleCustInfo(Session(), ShuttleCustomer_, BranchNo);
            ShuttleInfo->GetShuttleInfo();
            if ( ShuttleInfo->IsGoodState() )
            {
                DatumAuslieferung_ = ShuttleInfo->DeliveryDate();
                RouteAssignSpecificTour(ShuttleInfo->TourId());
            }
            delete ShuttleInfo;
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  ShuttleCustomer: new suivra France methode                                */
/*  It just works if Param()->IsSIbtCstOrg() (new Suivra in France).           */
/*----------------------------------------------------------------------------*/
pxCustBase*
pxOrder :: ShuttleCustomer
(
    const short BranchNo
)
{
    pxBranch* BGANRBranch = NULL;
    pxCustBase* customerBGANR = NULL;
    long BGANR_EK = 0;

    if (!Param()->IsSIbtCstOrg() )
        return ShuttleCustomer_ = NULL;

    if (ShuttleCustomer_ != NULL)       // then  shuttle customer reference is there
    {
        return ShuttleCustomer_;          // construct pxCustBase object
    }

    customerBGANR = new pxCustBase(Session(), BranchNo, IDFNr());
    if ( !customerBGANR->IsGoodState() )
    {
        delete customerBGANR;
        return ShuttleCustomer_ = NULL;
    }
    if ( customerBGANR->OriginalFilialNr() == 0 )
    {
        BGANRBranch = new pxBranch( Session(), BranchNo);
        if ( BGANRBranch->IsGoodState() )
        {
            BGANR_EK = BGANRBranch->BGANr_EK();
        }
        else
        {
            delete customerBGANR;
            delete BGANRBranch;
            return ShuttleCustomer_ = NULL;     // return NULL
        }
    }
    else
    {
        BGANRBranch = new pxBranch( Session(), customerBGANR->OriginalFilialNr());
        if ( BGANRBranch->IsGoodState() )
        {
            BGANR_EK = BGANRBranch->BGANr_EK();
        }
        else
        {
            delete customerBGANR;
            delete BGANRBranch;
            return ShuttleCustomer_ = NULL;     // return NULL
        }
    }
    ShuttleCustomer_ = new pxCustBase(Session(), FilialNr_, BGANR_EK);
    delete  customerBGANR;
    delete BGANRBranch;
    return ShuttleCustomer_;
 }

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes allocatable for current order        */
/*  shipment. Requires the order to be opened for order entry and an          */
/*  appropiate commission type being selected.                                */
/*  Returns NULL if a route may not be allocated for any reason.              */
/*----------------------------------------------------------------------------*/
pxCustRouteList*
pxOrder :: ShuttleRouteList
(
    const nString& KdAuftragArt
)
{
    ClearError();
    pxCustRouteList   *rl   = NULL;
    pxCustRouteList   *rlot = NULL;
    pxCustRouteList   *rlotsave = NULL;
    nDate today;
    nString ot = KdAuftragArt;
    ot.Strip();


    if (!Param()->IsSIbtCstOrg() )
        return rl;

    // Sanity checks:
    if ( !IsChangeable() )
        return NULL;
    if ( !IsEntryInProgress() )
        ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOENTRY);

    if ( ShuttleCustomer(FilialNr_ ) )
    {
        if ( IsGoodState() )                // ensure sanity so far
        {
            rl = ShuttleCustomer_->RouteList();
            if ( rl->Entries() == 0 )        // today no entries found
            {
                return rl;
            }
            if ( (rlot = ShuttleCustomer_->RouteListOrderType() ))
            {
                rlotsave = ShuttleCustomer_->OrdTypeRouteList();
                if ( !ot.IsEmpty() )
                {
                    if ( rlotsave->IsOrderTypeInList(ot) )
                    {
                        rl = ShuttleCustomer_->RouteListOrderType();
                    }
                }
                else
                {
                    if ( rlotsave->IsOrderTypeInList(KdAuftragArt_) )
                    {
                        rl = ShuttleCustomer_->RouteListOrderType();
                    }
                }
            }
            nTime time;                      // construct a time object
            long ctourkipp = ShuttleCustomer_->TourenKippZeit();
            long TourenKippZeit = 0;
            time -= Param()->TourVerspaetung() * 60L;
            if ( !Session()->Device()->IsVideo() ) // for a non videodevice
            {
                rl->Shrink(time, &TourenKippZeit); // first shrink list on TourenKippZeit
                if (TourenKippZeit == 0)
                {
                    time += ((ctourkipp >0 ) ? (ctourkipp * 60L) : (Param()->TourenKippZeit() * 60L));
                    if ( !(rl->Shrink(time)) )       // shrink list to contain allocatable
                    {                                // routes only
                        ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOMORE);
                        return rl = NULL;
                    }
                }
            }
            else
            {
                if ( !(rl->Shrink(time)) )       // shrink list to contain allocatable
                {                                // routes only
                    ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOMORE);
                    return rl = NULL;
                }
            }
        }
    }
    return rl;
}

/*----------------------------------------------------------------------------*/
/*  CountDayNightMergePositions                                               */
/*  look for kdauftragpos entries where entries are marked as                 */
/*  daynightmerge position.                                                   */
/*  Take care of a well constructed Item_ object                              */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CountDayNightMergePositions
(
)
{
    int  count = 0;
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;

    // Now scan this order for IBT article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( item->IsDayNightMergePosition() )
        {
            count++;
        }
    }

    return count;
}

/*----------------------------------------------------------------------------*/
/*  CountSeparatedPositions                                                   */
/*  look for kdauftragpos entries where entries are marked as                 */
/*  separated position.                                                       */
/*  Take care of a well constructed Item_ object                              */
/*----------------------------------------------------------------------------*/
int pxOrder :: CountSeparatedPositions()
{
    int  count = 0;
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;

    // Now scan this order for IBT article
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( item->IsSeparatePosition() )
        {
            count++;
        }
    }

    return count;
}

bool pxOrder::hasAtLeastOneCompletedIbtBooking()
{
    int  count = 0;
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;

    // loop over ALL items, no premature break to take sure all IBT requests got reloaded!
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( item->isIbtBookingCompleted() )
        {
            count++;
        }
    }
    return (count > 0);
}
