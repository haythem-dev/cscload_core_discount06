/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXSHUTTELCUSTINFO
Info Object for New Suivra France.

REVISION HISTORY

18 Sep 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXSHUTTLECUSTINFP_INC
   #define PXSHUTTLECUSTINFO_INC

#include "tourutil.hpp"
#include "pxerrorloggable.hpp"

class pxCustBase;
class pxOrder;
class pxSession;

class pxShuttleCustInfo
{

public:


// constructors:
                      pxShuttleCustInfo(pxSession *session, pxCustBase* ShuttleCustomer, short FilialNr);

// destructor:
    virtual           ~pxShuttleCustInfo();

// public member operators
    pxShuttleCustInfo&    operator=(const pxShuttleCustInfo& src);

// public member functions

    pxSession * Session();

//  Field updates
    void              SetTourId( nString& TourId)
                      { TourId_ = TourId; }
    void              SetDayOfWeek( long day )
                      { DayOfWeek_ = day;  }

    int              GetShuttleInfo();
    bool             IsValidRoute(const nString& RouteId);
	bool			 IsValidRouteForOrderClosure( const nString& tourid, const nDate& deliverydate = TourUtil::getNullDate() );
    bool             IsGoodState();

// Queries:
             long     DayOfWeek()                 { return DayOfWeek_         ;}
             nTime    ArrivalTime()               { return ArrivalTime_       ;}
             nString& TourId()                    { return TourId_            ;}
             nDate&   DeliveryDate()              { return DeliveryDate_      ;}

protected:
                      pxShuttleCustInfo();

    void              Init();

/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    pxSession*        Session_;
    pxCustBase*       Customer_;
    pxOrder*          OrderInfo_;          // Auftrag
    short             FilialNr_;           // Filialnummer
    pxErrorLoggable   Error_;
    long              DayOfWeek_;          // WeekDay
    nTime             ArrivalTime_;        // ShuttleTour Arrival Time
    nDate             DeliveryDate_;       // Delivery Date
    nString           TourId_;             // ShuttleTourId
private:
};
#endif
