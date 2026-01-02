/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxShuttleCustInfo:
France New Suivra

REVISION HISTORY

18 Sep 2011 V1.00 REV 00 written by Ysbrand Bouma
*/
#include "pxshuttlecustinfo.hpp"
#include "pxcstbas.hpp"
#include "pxcstrou.hpp"
#include "pxcustrouteweek.hpp"
#include "pxorder.hpp"
#include "tourassignmentutil.hpp"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Constructor for pxShuttleCustInfo object                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxShuttleCustInfo :: pxShuttleCustInfo
(
    pxSession* session,
    pxCustBase* ShuttleCustomer,
    short     filiale
)
{

    Init();
    Session_   = session;
    Customer_  = ShuttleCustomer;
    FilialNr_  = filiale;
}

/*----------------------------------------------------------------------------*/
/*  Destructor  for direct booking object                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxShuttleCustInfo :: ~pxShuttleCustInfo
()
{
    if (OrderInfo_) delete OrderInfo_;
    pxGlobalNoDatabaseWrite = false;
}

/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void
pxShuttleCustInfo :: Init()
{
    Customer_ = NULL;
    OrderInfo_ = NULL;
}
/*----------------------------------------------------------------------------*/
/*  Remove the remote position                                                */
/*----------------------------------------------------------------------------*/
int
pxShuttleCustInfo :: GetShuttleInfo
(
)
{
    pxCustRoute*        route          = NULL;
    pxCustRouteList*    rl             = NULL;
    pxCustRouteWeek*    routedayofweek = NULL;
    pxCustRouteWeekList* rwl           = NULL;
    nDate now;
    nDate deliverydate;

    if ( !Customer_ )
        return Error_.ErrorState();

    if ( OrderInfo_ == NULL )
    {
		OrderInfo_ = new pxOrder(Session_, Customer_, pxOrder::INFO_ORDER_TYPE_DEFAULT);
        if ( !OrderInfo_->IsGoodState() )
        {
            Error_.Error() = OrderInfo_->Error();
            delete OrderInfo_;
            pxGlobalNoDatabaseWrite = false;
            return Error_.ErrorState();
        }
        TourId_       = OrderInfo_->TourId();
        DeliveryDate_ = OrderInfo_->DatumAuslieferung();
        DayOfWeek_ = DeliveryDate_.GetDayOfWeek();
        if ( DayOfWeek_ == now.GetDayOfWeek() )
        {
            rl = Customer_->RouteList();
            if ( rl )
            {
                route = rl->Find(TourId_);
                if (route != NULL)
                {
                    ArrivalTime_ = route->Arrival();
                }
            }
        }
        else
        {
            rwl = Customer_->RouteWeekList();
            if ( rwl )
            {
                routedayofweek = rwl->GetEntry(TourId_, DayOfWeek_ );
                if (routedayofweek != NULL)
                {
                    nTime deltime(routedayofweek->Arrival()*100);
                    ArrivalTime_ = deltime;
                }
            }
        }
    }

    return Error_.ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Is Good State ?                                                           */
/*----------------------------------------------------------------------------*/
bool
pxShuttleCustInfo :: IsGoodState()
{
    return Customer_ != NULL && Customer_->IsGoodState() &&
           OrderInfo_->IsGoodState() && Error_.IsGoodState();
}

/*----------------------------------------------------------------------------*/
/*  Test if current order could be shipped using the named route.             */
/*----------------------------------------------------------------------------*/
bool pxShuttleCustInfo::IsValidRoute( const nString& RouteId )
{
    if ( OrderInfo_ == NULL )
    {
        return false;
    }
    return OrderInfo_->IsValidRoute(RouteId);
}

/*----------------------------------------------------------------------------*/
bool pxShuttleCustInfo::IsValidRouteForOrderClosure( const nString& tourid, const nDate& deliverydate /*= TourUtil::getNullDate()*/ )
{
    if( NULL == OrderInfo_ ) return false;
    if( TourUtil::isDateInTheFuture( deliverydate ) ) return true;

    OrderInfo_->getTourAssignmentUtil()->injectNoCheckForTransitionTimesAndPickingDurations(true);
    return OrderInfo_->IsValidRouteForOrderClose( tourid );
}
