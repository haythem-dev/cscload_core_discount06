#ifndef CUSTOMERTOUR_HPP
#define CUSTOMERTOUR_HPP

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <time.hpp>
#include "tourutil.hpp"
#include "pxorderentryparamptr.h"
#include <libbasarcmnutil_datetime.h>

class CSCCustomer;
class pxArtBase;
class pxCommType;
struct tCUSTOMERTOUR;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerTour : public pxDBRecord
{

        /*############################################################################################################################*/
        /*                                       P U B L I C                                                                          */
        /*############################################################################################################################*/
    public:

        CustomerTour( pxSession* session, const short branchno, const long customerno );

        virtual						~CustomerTour();

        long						getDrivingDuration() const;

        short						getDeliveryTimeBuffer() const;

        long						getLagRechTour() const;

        nDate						getPickingDate() const;

        nTime						getPickingTime() const;

		nDate						getPickingDateTime() const;

        char						getPickingType() const;

        nString						getTourId() const;

        nTime						getTourTime() const;

        nDate						getTourDepartureDateTime(const nDate& date = TourUtil::getNullDate() ) const;

        nDate						getTourDeliveryDateTimeMin(const nDate& date = TourUtil::getNullDate()) const;

        nDate						getTourDeliveryDateTimeMax(const nDate& date = TourUtil::getNullDate()) const;

        TourUtil::WeekDayEnum		getWeekDay() const;

        bool						hasCoolPermission() const;

        bool						hasCoolBelow8Permission() const;

        bool						hasCoolBelow20Permission() const;

        bool                        isReturnsTour() const;

        bool						hasExpired( const pxCommType* pickingtype, const bool checkDurationAndTransitionTimes = true ) const;

        bool						hasNarcoticsPermission() const;

        bool						hasPsychotropicPermission() const;

		bool						isAssignable( bool acceptAutoAssignableToursOnly = false, nTime timeoffset = TourUtil::getCurrentTime(), bool forceTimeCheck = false );

        bool						isAutoAssignable() const;

		bool						isDepartureOnPublicHoliday();

        bool						isIBTTour() const;

        bool						isPseudoTour() const;

        bool						isValidForArticle( pxArtBase* article ) const;

		void						setPickingDate( const nDate& date );

		void						injectNoCheckForTransitionTimesAndPickingDurations( const bool b = true );

		void						injectIBTShuttleTourDetermination( const bool b = true );

		void						injectIBTOrderImport( const bool b = true );

		nDate						getTourClosingDateTime( const pxCommType* pickingtype = NULL, nDate datetouse = TourUtil::getNullDate() ) const;

		short						getBranchNo() const;
		long						getCustomerNo() const;


		/*############################################################################################################################*/
        /*                                       P R O T E C T E D                                                                    */
        /*############################################################################################################################*/
    protected:

        CustomerTour&				Assign( CustomerTour& dest, const tCUSTOMERTOUR& src );

        tCUSTOMERTOUR&				Assign( tCUSTOMERTOUR&  dest, const CustomerTour& src );

        bool						hasOrderType( const nString& ordertype = "" ) const;

        void						Init();

        void						setWeekDay( const short& weekday );

        /*############################################################################################################################*/
        /*                                       P R I V A T E                                                                        */
        /*############################################################################################################################*/
    private:

        CustomerTour( pxSession* session, const short branchno, const long customerno, tCUSTOMERTOUR& src );

        CustomerTour( CustomerTour& src );

        CustomerTour&				operator=( const CustomerTour& src );

        CustomerTour&				operator=( const tCUSTOMERTOUR& src );

        virtual int					CompareTo( const nCollectable *that/*, void *p,const long lparm*/ ) const;

        nDate						calcTourDeliveryDateTime( const long& additionalSecs, const nDate& date = TourUtil::getNullDate() ) const;

        const CSCCustomer*			getCustomer() const;

        nTime						getExpiryTime( const pxCommType* pickingtype, const bool checkDurationAndTransitionTimes = true ) const;

		const pxOrderEntryParamPtr	getOrderEntryParam() const;

		long						getTourTransitionTime() const;

        bool						isAssignableBeforeTourDeparture(long& timelimit);

        bool						isAssignableBeforeTransition(long& timelimit);

		short						m_BranchNo;
		long						m_CustomerNo;

        char						m_AutoAssignable;

        long						m_DrivingDuration;

        long						m_TimeEndOfPicking;

        char						m_IbtTour;

        nString						m_OrderType;

        nDate						m_PickingDate;

        nString						m_TourId;

        short						m_TransitionTime; // transition time from tourplantag

        short						m_TourTransitionTime; // transition time from tour

        TourUtil::WeekDayEnum		m_WeekDay;

        short						m_IsCoolTour;

        short						m_IsCoolBelow8Tour;

        short						m_IsCoolBelow20Tour;

        short						m_IsNarcoticsTour;

        short						m_IsPsychotropicTransportExcluded;

        char						m_PickingType;

        short						m_DeliveryTimeBuffer; // Karenzzeit

        long						m_LagRechTour;

		bool						m_ArgNoCheckForTransitionTimesAndPickingDurations;

		bool 						m_IBTShuttleTourDetermination;

		bool						m_IBTOrderImport;

        short                       m_ReturnsTour;

		mutable CSCCustomer*		m_Customer;

        friend class CustomerTourList;
};

#endif /* CUSTOMERTOUR_HPP */
