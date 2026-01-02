#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxordvtr.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoeparm.hpp"
#include "pxcustrouteweek.hpp"
#include "pxholiday.hpp"
#include "pxshuttlecustinfo.hpp"
#include "pxoclpar.hpp"
#include "tourassignmentutil.hpp"
#include "tourinfo.hpp"
#include "tourmanager.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/pickingtypeenum.inc"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
void pxOrder::verifyCurrentTourAssignment()
{
    // if the current order has a tour from the past, the current tour has to be assigned
    TourInfo* currentTourInfo = getTourInformation();
    if (currentTourInfo->getTourFound())
    {
        if (TourUtil::getCurrentDate().GetYYYYMMDD() > currentTourInfo->getTourDate().GetYYYYMMDD())
        {
            if (!(CommType().IsNoShipment()) && !(Session()->Device()->IsFILE()))
            {
                getTourAssignmentUtil()->removeTourAssignments();
                RouteAssign();
                if (!IsGoodState())
                {
                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();
                    }
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
const TourInfo& pxOrder::getNormalDeliveryTourInfo(const nString& tourid, const short weekday /*= -1*/)
{
    if( !m_NormalDeliveryTourInfo.getTourFound() )
    {
        m_NormalDeliveryTourInfo = getTourAssignmentUtil()->getNormalDeliveryTour(tourid, weekday);
    }
    return m_NormalDeliveryTourInfo;
}

/*----------------------------------------------------------------------------*/
nDate pxOrder::CalcDeliveryDate( const long nextday )
{
    nDate now;
    long dow = now.GetDayOfWeek();
    if( dow >= nextday )
    {
        now += ( 7 - (dow - nextday) );
    }
    else
    {
        now += ( nextday - dow );
    }
    return now;
}

/*----------------------------------------------------------------------------*/
/*  RouteClearKippZeit: selects the Customer Routelist and assigns zero to    */
/*  KippZeit to every entry within the customers routelist.                   */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteClearKippZeit()
{
    getTourAssignmentUtil()->injectNoCheckForTransitionTimesAndPickingDurations(true);

    pxCustRouteList *rl = NULL;
    pxCustRoute *route = NULL;

    Customer()->DeleteRouteList();

    rl = Customer()->RouteList();

    pxCustRouteListIter cursor(*rl);
    if( rl->Entries() )
    {
        while ( (route = (pxCustRoute*) ++cursor) != NULL )
        {
            route->SetTourenKippZeit( (short) 0);
        }
    }

    return ErrorState();
}

// ========================================================================================
// ======================== T O U R M A N A G E R =========================================
// ========================================================================================

/*----------------------------------------------------------------------------*/
/*  Assign this order to be shipped with the next route scheduled for the     */
/*  customer from the RoutWeekList                                            */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteAssignDayType( const nDate& date )
{
    this->DatumAuslieferung_ = date;
    getTourAssignmentUtil()->resetInjections();
    return getTourAssignmentUtil()->assignTour();
}

/*----------------------------------------------------------------------------*/
/*  Assign this order to be shipped with the next route scheduled for the     */
/*  customer. This route is called the 'default route'.                       */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteAssign()
{
    getTourAssignmentUtil()->resetInjections();
    return getTourAssignmentUtil()->assignTour();
}


/*----------------------------------------------------------------------------*/
/*  Test if current order could be shipped using the named route.             */
/*----------------------------------------------------------------------------*/
bool pxOrder::IsValidRoute( const nString& RouteId ) // TourManager OK!!!
{
    return getTourAssignmentUtil()->isTourValid( RouteId );
}

/*----------------------------------------------------------------------------*/
/*  Test if current order could be shipped using the named route.             */
/*----------------------------------------------------------------------------*/
bool pxOrder::IsValidRouteForOrderClose( const nString& RouteId )
{
    return getTourAssignmentUtil()->isTourValidForOrderClosure( RouteId );
}


/*----------------------------------------------------------------------------*/
/* remove the currently assigned tour                                         */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteAssignClearTourAssignment()
{
    return getTourAssignmentUtil()->removeTourAssignments();
}

// Aktuelle Tour im Auftrag überspringen und auf Folgetour buchen
int pxOrder::RouteAssignNext()
{
    TourInfo* currentTourInfo = this->getTourInformation();
    return RouteAssignNext(currentTourInfo);
}

// Aktuelle Tour aus TourInfo-Offset im Auftrag überspringen und auf Folgetour buchen
int pxOrder::RouteAssignNext(TourInfo* offsetTourInfo)
{
    TourInfo* currentTourInfo = offsetTourInfo;
    if (currentTourInfo->getTourFound())
    {
        TourInfo followingTourInfo = this->getTourAssignmentUtil()->getTourManager()->determineFollowingTour(currentTourInfo);
        if (followingTourInfo.getTourFound())
        {
            if (TourUtil::isDateInTheFuture(followingTourInfo.getTourDate()))
            {
                this->DatumAuslieferung_ = followingTourInfo.getTourDate();
            }
            getTourAssignmentUtil()->resetInjections();
            getTourAssignmentUtil()->injectDesiredTourId(followingTourInfo.getTourID());
            return getTourAssignmentUtil()->assignTour();
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Assign this order to be shipped with the route named as 'RouteId'.        */
/*  If day = -1, so 'RouteId' r is assign for today, otherwise for            */
/*  the day defined by day. On invalid 'RouteId', an error is given back to   */
/*  the caller. This methode is just used on video users                      */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteAssign( const nString& r, const short day )
{
    getTourAssignmentUtil()->resetInjections();
    getTourAssignmentUtil()->injectDesiredTourId( r );
    getTourAssignmentUtil()->injectWeekday( day );
    return getTourAssignmentUtil()->assignTour();
}

/*-SH---------------------------------------------------------------------------*/
long pxOrder::getDeliveryTime()
{
    long retval = 0;
    nDate x = getTourInformation()->getCustomerDeliveryDateTimeMin();
    retval = x.GetHours() * 100 + x.GetMinutes();
    return retval;
}

/*-SH---------------------------------------------------------------------------*/
long pxOrder::getDeliveryDate()
{
    return getTourInformation()->getCustomerDeliveryDateTimeMin().GetYYYYMMDD();
}

/*-SH---------------------------------------------------------------------------*/
long pxOrder::getTourDate()
{
    return getTourInformation()->getTourDate().GetYYYYMMDD();
}

/*-SH---------------------------------------------------------------------------*/
nString pxOrder::TourId()
{
    nString tourid = getTourInformation()->getTourID();
    tourid.Strip();
    return tourid;
}

/*-SH---------------------------------------------------------------------------*/
TourInfo* pxOrder::getTourInformation()
{
    if( NULL == m_TourInfo )
    {
        m_TourInfo = new TourInfo( getTourAssignmentUtil()->getTourInformation( this->KdAuftragNr(), 0 ) );
    }

    return this->m_TourInfo;
}

/*-SH---------------------------------------------------------------------------*/
bool pxOrder::hasTourInformation()
{
    if( NULL == m_TourInfo )
    {
        return false;
    }
    if( !m_TourInfo->getTourFound() )
    {
        delete m_TourInfo;
        m_TourInfo = NULL;
        return false;
    }
    return true;
}

/*-SH---------------------------------------------------------------------------*/
TourAssignmentUtil* pxOrder::getTourAssignmentUtil()
{
    if( NULL == m_TourAssignmentUtil )
    {
        m_TourAssignmentUtil = new TourAssignmentUtil(this);
    }
    return m_TourAssignmentUtil;
}

/*----------------------------------------------------------------------------*/
void pxOrder::SetRoute( const nString& route ) // OK
{
    if( !route.IsEmpty() )
    {
        OrderTourId_ = route;
    }
}

/*----------------------------------------------------------------------------*/
void pxOrder::SetRouteForOrderSeparation( const nString& tourid, const nDate& deliverydate )
{
    this->DatumAuslieferung_ = deliverydate;
    getTourAssignmentUtil()->resetInjections();
    getTourAssignmentUtil()->injectDesiredTourId( tourid );
    getTourAssignmentUtil()->injectNoCheckForTransitionTimesAndPickingDurations(true);
    getTourAssignmentUtil()->assignTour();
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes allocatable for current order        */
/*  shipment. Requires the order to be opened for order entry and an          */
/*  appropiate commission type being selected.                                */
/*  Returns NULL if a route may not be allocated for any reason.              */
/*----------------------------------------------------------------------------*/
pxCustRouteList* pxOrder::RouteList( const nString& KdAuftragArt )
{
    ClearError();
    pxCustRouteList *rl = NULL;
    pxCustRouteList *rlotsave = NULL;
    nDate today;
    nString ot = KdAuftragArt;
    ot.Strip();

    if( !IsChangeable() )
    {
        return NULL;
    }

    if( !IsEntryInProgress() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOENTRY);
    }

    if( IsGoodState() )
    {
        rl = Customer()->RouteList();
        if( 0 == rl->Entries() )
        {
            return rl;
        }

        pxCustRouteList* rlot = Customer()->RouteListOrderType(ot);
        if (rlot)
        {
            rlotsave = Customer()->OrdTypeRouteList();
            if( !ot.IsEmpty() )
            {
                if( rlotsave->IsOrderTypeInList(ot) )
                {
                    rl = Customer()->OrdTypeRouteList();
                }
            }
            else
            {
                if( rlotsave->IsOrderTypeInList(KdAuftragArt_) )
                {
                    rl = Customer()->RouteListOrderType(ot);
                }
            }
        }

        nTime time;
        long ctourkipp = Customer()->TourenKippZeit();
        long TourenKippZeit = 0;
        time -= Param()->TourVerspaetung() * 60L;

        if( !Session()->Device()->IsVideo() )
        {
            rl->Shrink(time, &TourenKippZeit); // first shrink list on TourenKippZeit
            if( 0 == TourenKippZeit )
            {
                time += ((ctourkipp >0 ) ? (ctourkipp * 60L) : (Param()->TourenKippZeit() * 60L));
                if( !(rl->Shrink(time)) ) // shrink list to contain allocatable routes only
                {
                    ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOMORE);
                    return rl = NULL;
                }
            }
        }
        else
        {
            if( !(rl->Shrink(time)) ) // shrink list to contain allocatable routes only
            {
                ExternalError( CMsgStream(), CMSG_ORD_ROUTE_NOMORE );
                return rl = NULL;
            }
        }
    }
    return rl;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes guilty for this Customer all over    */
/*  the week.                                                                 */
/*  Returns NULL if a route may not be allocated for any reason.              */
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList* pxOrder::RouteWeekList( const nString& KdAuftragArt )
{
    ClearError();
    nString ot = KdAuftragArt;
    ot.Strip();
    pxCustRouteWeekList *rwl = NULL;
    pxCustRouteWeekList *rwlotsave = NULL;

    if( !IsChangeable() )
    {
        return NULL;
    }

    if( !IsEntryInProgress() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOENTRY);
    }

    if( IsGoodState() )
    {
        rwl = Customer()->RouteWeekList();
    }

    if( NULL == rwl || 0 == rwl->Entries() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_ROUTE_NOMORE);
        return NULL;
    }

    pxCustRouteWeekList* rwlot = Customer()->RouteWeekListOrderType(ot);
    if (rwlot)
    {
        rwlotsave = Customer()->OrdTypeRouteWeekList();
        if( !ot.IsEmpty() )
        {
            if( rwlotsave->IsOrderTypeInList(ot) )
            {
                rwl = Customer()->OrdTypeRouteWeekList();
            }
        }
        else
        {
            if( rwlotsave->IsOrderTypeInList(KdAuftragArt_) )
            {
                rwl  = Customer()->RouteWeekListOrderType(ot);
            }
        }
    }

    return rwl;
}

/*----------------------------------------------------------------------------*/
/*  Assign this order to be shipped with the route named as 'RouteId'. An     */
/*  empty string will remove the current assignment.                          */
/*----------------------------------------------------------------------------*/
int pxOrder::RouteAssignSpecificTour( const nString& r )
{
    getTourAssignmentUtil()->resetInjections();
    getTourAssignmentUtil()->injectDesiredTourId( r );
    return getTourAssignmentUtil()->assignTour();
}

/*----------------------------------------------------------------------------*/
/*  EstimateDepartureTime: calculates the estimate time of departure          */
/*  On Error: returnvalue = Errorcode and the errormessage in time,           */
/*  otherwise, returnvalue = 0 and time = HH:MM                               */
/*  Take care for a well constructed pxOrder Object(this)                     */
/*----------------------------------------------------------------------------*/
int pxOrder::EstimateDepartureTime( char* ctime )
{
    if (TourId().IsEmpty())
    {
        getTourAssignmentUtil()->resetInjections();
        if (getTourAssignmentUtil()->assignTour() > 0)
        {
            strcpy(ctime, ErrorMsg());
        }
    }
    else
    {
        if (!getTourAssignmentUtil()->isTourValid(TourId()))
        {
            strcpy(ctime, ErrorMsg());
        }
        else
        {
            TourInfo ti = getTourAssignmentUtil()->getTourInformation(KdAuftragNr(), 0);
            strcpy(ctime, (char*)TourUtil::getTourIdAsReadableHHMM(ti.getTourID()));
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Check routexpiretime to close the order even with urgent shipment         */
/*  This function is just for terminaltype dct developt                       */
/*----------------------------------------------------------------------------*/
bool pxOrder::ShipUrgentVerification()
{
    return getTourAssignmentUtil()->changeToUrgentPickingIfNecessary();
}

/*----------------------------------------------------------------------------*/
/*  SetNextValidRoute: DatumAuslieferung > now                                */
/*----------------------------------------------------------------------------*/
int pxOrder::SetNextValidRouteNormal( const nString& RouteId )
{
    getTourAssignmentUtil()->resetInjections();
    getTourAssignmentUtil()->injectDesiredTourId( RouteId );
    return getTourAssignmentUtil()->assignTour();
}

/*----------------------------------------------------------------------------*/
/*  SetNextValidRoute: DatumAuslieferung > now                                */
/*----------------------------------------------------------------------------*/
int pxOrder::SetNextValidRoute( const nString& RouteId )
{
    this->OrderTourId_ = "";
    getTourAssignmentUtil()->resetInjections();
    getTourAssignmentUtil()->injectDesiredTourId( RouteId );
    return getTourAssignmentUtil()->assignTour();
}
