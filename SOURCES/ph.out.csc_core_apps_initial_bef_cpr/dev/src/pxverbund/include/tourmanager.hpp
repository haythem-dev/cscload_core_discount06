#ifndef TOURMANAGER_HPP
#define TOURMANAGER_HPP

/*
Testfälle beachten:

- Sonntag und Ermittlung Lieferzeitpunkt (Es können auch Sonntags Aufträge kommen die nicht auf den nächsten Arbeitstag gehen dürfen!)

*/

/***************************************************************************************************************************/
/* includes */
/***************************************************************************************************************************/
#include "pxerrorloggable.hpp"
#include <utility>
#include "tourinfo.hpp"
#include "tourutil.hpp"
#include "csccustomer.hpp"
#include "pxorderitemtour.hpp"
#include "pxorderentryparamptr.h"
#include <logger/loggerpool.h>
#include <sstream>

class pxSession;
class pxArtBase;
class CustomerTourList;
class CustomerTour;
class pxCommType;
class IBTBranchList;
class IBTBranchesList;
class pxOrderPeriod;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourManager : public pxErrorLoggable
{
    public:
        static pxOrderPeriod getCurrentMSV3OrderPeriod(pxSession* session, const short branchno, const long customerno);
        static TourInfo getCustomerTourForArticle(pxSession* session, const short branchno, const long customerno, const long articleno = 0);
        static TourInfo getNextCustomerTourOccurrance(pxSession* session, const short branchno, const long customerno, const nString& tourid);
        static TourInfo determineReturnsTour(pxSession* session, const short branchno, const long customerno);
        static bool checkIsTourValid(pxSession* session, const short branchno, const long customerno, const nString& tourid, const nDate& deliverydate = TourUtil::getNullDate());

        /*############################################################################################################################*/
        /*                                       P U B L I C                                                                          */
        /*############################################################################################################################*/
    public:
        TourManager(    pxSession* session,
                        const long& orderno,
                        const short& branchno,
                        const long& customerno,
                        const pxCommType* commtype,
                        const nString& ordertype = "" );

        virtual                     ~TourManager();

        bool                        hasToDoTourDetermination();

        TourInfo                    getTourInformation( const nString& tourid );

        bool                        specialTourPossible( pxArtBase* article ) const;

        bool                        isArticleDeliverable( pxArtBase* article );

        bool                        isArticleDeliverableForIBT( const short ibtbranchno, pxArtBase* article );

        bool                        isTourValid(const nString& tourid, const pxCommType* pickingtype, const nDate& deliverydate = TourUtil::getNullDate());

        bool                        isTourValidForDate(const nString& tourid, const nDate& deliverydate = TourUtil::getNullDate());

        bool                        isTourValidForOrderClosure(const nString& tourid, const pxCommType* pickingtype, const bool checkDurationsAndTransitionTimes = true );

        void                        setOrderType( const nString& ordertype );

        void                        setPickingType( const pxCommType* commtype );

        TourInfo                    determineTour();

        TourInfo                    determineFollowingTour( TourInfo* currentTourInfo );

        pxOrderItemTourList*        getTourInformation( const long& orderno, const long& lineno );

        void                        resetTourInformation( const long& orderno, const long& lineno );

        void                        removeTourInformationIBT( const long& orderno, const long& lineno );

        void                        saveTourInformation( const long& orderno, const long& lineno, const TourInfo& tourinfo );

        bool                        useOrderTypeSpecificTour();

        void                        injectIBTBranchNo( const short& ibtbranchno );
        void                        injectNLevelIBTType( const short& nlevelibttype );
        void                        injectIBTTypeArticle( const short& ibttypearticle );
        void                        injectDeliveryDate( const nDate& deliverydate );
        void                        injectArticle( pxArtBase* article );
        void                        injectNewOrderFlag( const bool neworder );
        void                        injectDesiredTourId( const nString& desiredtourid );
        void                        injectIsOrderFromIBT( const bool isorderfromibt );
        void                        injectNoCheckForTransitionTimesAndPickingDurations( const bool b = true );
        void                        injectTimeOffset( nTime timeOffset );
        void                        injectNoDelayedDelivery( const bool b = true );
        void                        injectUseTransportExclusion(const bool b = true);
        void                        injectReturnsTourSearch(const bool b = true);
        void                        injectLatestPossibleTourSearch(const bool b , const nDate&  tourdeparturedatetime);

        void                        setNotEarlierThanOrderTour(nString tourid, nDate tourdate);

        void                        resetArgInjections();

        nString                     serializeArgs() const;

        /*############################################################################################################################*/
        /*                                       P R O T E C T E D                                                                    */
        /*############################################################################################################################*/
    protected:

        CustomerTour*               getTour(const nString& tourid);

        /*############################################################################################################################*/
        /*                                       P R I V A T E                                                                        */
        /*############################################################################################################################*/
    private:
        TourManager&                operator = (const TourManager&);

        void                        checkDesiredTour();

        nDate                       getDeliveryDateTimePPE() const;

        void                        resetError();

        void                        checkCustomerSpecialSettings();
        void                        checkShuttleCustomer();

        bool                        isArrivalBefore(CustomerTour* ct, nDate dateToCheck);
        bool                        isNotEarlierThanOrderTour( CustomerTour* ct );
        bool                        isDesiredTourCheckSuccessful( CustomerTour* ct );
        bool                        isIBTTourCheckSuccessful( CustomerTour* ct );
        bool                        isTourAssignabilityCheckSuccessful( CustomerTour* ct );
        bool                        isArticleAssignabilityCheckSuccessful( CustomerTour* ct, pxArtBase* article );
        bool                        isWeekdayCheckSuccessful( CustomerTour* ct, short weekday );
        //Commented because AuftrÃ¤ge verzÃ¶gern icht mÃ¶glich
        //bool                        isTourOverMidnightMatchingNextWeekday( CustomerTour* ct, short weekday );
        bool                        isTransportExclusionEnabled();
        bool                        isReturnsTourCheckSuccessful(CustomerTour* ct);

        bool                        isHoliday(const nDate& dateToCheck);
        nDate                       changeDeliveryDateForPublicHolidays( const nDate& deliverydate );

        void                        delayDelivery();

        void                        delayDeliveryForArticle();
        bool                        delayDeliveryDespiteEmergencyService(long datum = 0);

        void                        determineLocalTour();

        void                        determineCurrentTour( pxArtBase* article );

        void                        determineSubsequentTour( pxArtBase* article );

        void                        determineSubsequentLatestPossibleTour(pxArtBase* article);

        void                        determineTourForDeliveryDate( const nDate& deliverydate, pxArtBase* article );

        void                        determineIBTTour();

        CustomerTour*               getNextAssignableTour(const nString& tourid);

        nString                     getOrderTypeSpecificTour();

        CustomerTour*               getTourForWeekday(const nString& tourid, const TourUtil::WeekDayEnum weekday);

        bool                        isArticleWithSpecialDeliveryConditions( pxArtBase* article ) const;

        bool                        isCoolArticle( pxArtBase* article ) const; // todo: gehört in pxArtBase

        bool                        isCoolBelow8Article( pxArtBase* article ) const; // todo: gehört in pxArtBase

        bool                        isCoolBelow20Article( pxArtBase* article ) const; // todo: gehört in pxArtBase

        bool                        isPsychotropicArticle( pxArtBase* article ) const; // todo: gehört in pxArtBase

        bool                        isCurrentTourValid(const nString& tourid, const pxCommType* pickingtype, const bool closeorder = false, const bool checkDurationsAndTransitionTimes = true );

        bool                        isDeliveryDateInTheFuture() const;

        bool                        isInsideBusinessHours(const nDate& datetime);

        bool                        isNarcoticArticle( pxArtBase* article ) const; // todo: gehört in pxArtBase

        bool                        isUpcomingTourValid(const nString& tourid, const nDate& deliverydate);

        void                        loadTours();

        void                        checkDesiredTourExistence();

        TourInfo                    getCustomerTourAsTourInfo(const CustomerTour* ct, const nDate& date = TourUtil::getNullDate() ) const;

        void                        transferCustomerTour2TourInfo(const CustomerTour* ct, const nDate& date = TourUtil::getNullDate());

        void                        setTourInfoError(const int value);

        CSCCustomer*                getCustomer();
        IBTBranchesList*            getIBTBranchesList();

        short                       m_HolidaysLoadedForBranch;
        pxHoliDayList*              m_HolidayList;
        pxHoliDayList*              getHolidayList();

        const long                  m_OrderNo;
        const short                 m_BranchNo;
        const long                  m_CustomerNo;
        long                        m_ShuttleCustomerNo;

        bool                        m_ToursLoaded;
        TourInfo                    m_TourInfo;
        CustomerTourList*           m_CustomerToursCurrent;
        CustomerTourList*           m_CustomerToursWeek;
        CSCCustomer*                m_Customer;
        const pxOrderEntryParamPtr  m_OrderEntryParam;
        nString                     m_OrderType;
        const pxCommType*           m_PickingType;
        IBTBranchesList*            m_IBTBranchesList;
        pxSession*                  m_Session;
        pxOrderItemTourList*        m_pxOrderItemTourList;

        /* arguments for route determination */
        bool                        m_ArgAcceptAutoAssignableToursOnly;
        short                       m_ArgIBTBranchNo;
        short                       m_ArgIBTTypeArticle;
        short                       m_ArgNLevelIBTType;
        nDate                       m_ArgDeliveryDate;
        pxArtBase*                  m_ArgArticle;
        bool                        m_ArgNewOrder;
        nString                     m_ArgDesiredTourId;
        nTime                       m_ArgTimeOffset;
        bool                        m_ArgUseTimeOffset;
        bool                        m_ArgForceTimeOffsetUsage;
        bool                        m_ArgIBTTourDetermination;
        bool                        m_ArgIsOrderFromIBT;
        bool                        m_ArgNoCheckForTransitionTimesAndPickingDurations;
        bool                        m_ArgInIBTShuttleTourDetermination;
        bool                        m_ArgNoDelayedDelivery;
        bool                        m_ArgUseTransportExclusion;
        nDate                       m_ArgOrderTourDate;
        nString                     m_ArgOrderTourID;
        bool                        m_ArgNotEarlierThanOrderTour;
        bool                        m_ArgReturnsToursOnly;
        bool                        m_ArgSearchLatestPossibleTour;
        nDate                       m_ArgLatestArrival;

        /* arguments for route determination */

        friend class TourAssignmentUtil;
};

#endif // TOURMANAGER_HPP
