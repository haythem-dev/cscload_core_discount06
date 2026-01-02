#ifndef TOURINFO_HPP
#define TOURINFO_HPP

/***************************************************************************************************************************/
/* includes */
/***************************************************************************************************************************/
#include <date.hpp>

class pxOrderItemTour;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourInfo
{
        /*############################################################################################################################*/
        /*                                       P U B L I C                                                                          */
        /*############################################################################################################################*/
    public:
        TourInfo();
        TourInfo( pxOrderItemTour* orderitemtour );
        TourInfo( const TourInfo& src );
        virtual					~TourInfo();

        void					init();

        const nDate&			getTourDepartureDateTime() const;
        const nDate&			getTourDepartureDateTimeNormalized() const;
        const nDate&			getCustomerDeliveryDateTimeMin() const;
        const nDate&			getCustomerDeliveryDateTimeMax() const;
        const nDate&			getTourClosingDateTime() const;
		bool					getTourClosingDateTimeAvailable() const;

        const nString&			getTourID() const;
        const nDate&			getTourDate() const;
        int						getDrivingDuration() const;
        char					getPickingType() const;
        short					getDeliveryTimeBuffer() const;
        long					getLagRechTour() const;

        short					getIBTBranchNo() const;
        int						getIBTCustomerNo() const;
        short					getIBTType() const;
        const nString&			getIBTTourID() const;
		const nDate&			getIBTTourDate() const;
        bool					isDayIBT() const;

        bool					getTourFound() const;

        int						getWarning() const;
        int						getError() const;

        nString					serialize() const;

        /*############################################################################################################################*/
        /*                                       P R O T E C T E D                                                                    */
        /*############################################################################################################################*/
    protected:
        void					setWarning( const int value );
        void					setError( const int value );

        void					setTourDepartureDateTime(const nDate& value);        
		void					setTourDepartureDateTimeNormalized(const nDate& value);
        void					setCustomerDeliveryDateTimeMin(const nDate& value);
        void					setCustomerDeliveryDateTimeMax(const nDate& value);
        void					setTourClosingDateTime(const nDate& value);

        void					setTourID(const nString& value);
        void					setTourDate(const nDate& value);
        void					setDrivingDuration(const long value);
        void					setPickingType(const char value);
        void					setDeliveryTimeBuffer(const short value);
        void					setLagRechTour(const long value);

        void					setIBTBranchNo(const short value);
        void					setIBTCustomerNo(const int value);
        void					setIBTType(const short value);
        void					setIBTTourId(const nString& value);
		void					setIBTTourDate(const nDate& value);
        void					setIBTSameDay(const bool value);

        void					setTourFound(const bool value);

		void					setTourClosingDateTimeAvailable(bool value = true);

        void					resetErrorsAndWarnings();

        /*############################################################################################################################*/
        /*                                       P R I V A T E                                                                        */
        /*############################################################################################################################*/
    private:		

        bool					m_TourFound;					// false if there´s no tour available

        nDate					m_TourDepartureDateTime;			// tour departure time (might be nulldate -> today)
        nDate					m_TourDepartureDateTimeNormalized;	// tour departure time (might be tomorrow 03:30)
        nDate					m_CustomerDeliveryDateTimeMin;	// tour departure time + driving duration
        nDate					m_CustomerDeliveryDateTimeMax;	// tour departure time + driving duration + karenz
		nDate					m_TourClosingDateTime;		
		bool					m_TourClosingDateTimeAvailable; // tour closing date time available after tour determination?

        int						m_Warning;						// last Warning number (-> write event for warnings)
        int						m_Error;						// last Error number (-> treat as error)

        nString					m_TourID;						// TourID for customer delivery
        nDate					m_TourDate;						// TourDate for customer delivery
        long					m_DrivingDuration;				// DrivingDuration to get to the customer
        char					m_PickingType;					// Type of Picking
        short					m_DeliveryTimeBuffer;			// Karenz time for the tour
        long					m_LagRechTour;

        // special information only for ibt orders
        short					m_IBTBranchNo;					// BranchNo for IBT order
        int						m_IBTCustomerNo;				// Customer for IBT order
        short					m_IBTType;						// type of IBT
        short					m_IBTSameDay;					// day IBT
        nString					m_IBTTourId;					// TourId IBT Customer
		nDate					m_IBTTourDate;					// TourDate for IBT Shuttle Tour


        friend class TourManager;
        friend class TourAssignmentUtil;
};

#endif // TOURINFO_HPP
