#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_DATAFILTER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_DATAFILTER_H

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace shipmenttracking {

// forward declaration:
struct ShipmentTrackingDataFilter;

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingDataFilter& shipmentTrackingDataFilter);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingDataFilter* shipmentTrackingDataFilter);

namespace libcsc {
namespace shipmenttracking {

struct ShipmentTrackingDataFilter
{
public:
    //! \brief enum to help simplify assembly of the TnT data lookup query	\n no-throw
    enum DateFilterMode { ToteDeliveryMode = 0, ArchivedPickingDate = 1, CurrentPickingDate = 2 };

    //! \brief default constructor \n no-throw
    ShipmentTrackingDataFilter() : 
        ToteDeliveryDate(),
        PickingDate(),
        DetailsDesired(false),
        SpecificTourID(""),
        SendPharmosOrderNumbers(false),
        SendPickingOrderNumbers(false),
        SendPackagePosNos(false),
        CurrentDate(basar::cmnutil::Date::getCurrent()) // explicitely setting it to current, although the default costructor would set it to current date. I don't want to rely on default constructor, which could maybe change...
    {
        this->ToteDeliveryDate.setInvalid(); //NOTE: let the date be uninitalized, thus set to an invalid date 99991231 on purpose. Ses desc below.
        this->PickingDate.setInvalid();      //NOTE: let the date be uninitalized, thus set to an invalid date 99991231 on purpose. Ses desc below.
    }

    //! \brief a helper: get DateFilterMode based on ToteDeliveryDate and PickingDate values for easier data processing	\n no-throw
    ShipmentTrackingDataFilter::DateFilterMode      getDateFilterMode() const
    { 
        return this->ToteDeliveryDate.isValid() ? 
            ShipmentTrackingDataFilter::ToteDeliveryMode :
            !this->PickingDate.isValid() || this->PickingDate >=  this->CurrentDate ? 
            ShipmentTrackingDataFilter::CurrentPickingDate :
            ShipmentTrackingDataFilter::ArchivedPickingDate;
    }

    const basar::Date& getCurrentDate() const { return this->CurrentDate; }

    //NOTE: one of the following dates: ToteDeliveryDate or PickingDate is mandatory, and only one may be provided!

    /*! \brief This is one of 2 mandatory Request Dates. Date for which the customer delivery information has to be fetched, i.e. the date on which the totes are planned to be delivered to the customer.
         Value interval: <Min, Max) i.e. excluding the Max, i.e. the invalid date 99991231. Invalid date means "Not set"!
         NOTE: Dates interpretation:
               1) if ToteDeliveryDate is set to a valid date, the PickingDate must be set to an invalid date! PickingDate will (thus) be ignored in this case.
                  ToteDeliveryDate can be a past, a current or a future date. Note that there can be totes, wchich will be shipped tomorrow, or next week etc.
                  TnT requests work now also for open (i.e. not closed yet) orders. And of course one can request an overview of totes in the past.
               2) if ToteDeliveryDate is set to a *INVALID* date (Max), the PickingDate will be taken into accont. Its value will be interpreted as follows:
                  - A PickingDate for past, i.e. for yesterday and older dates: the query will look up just the Archive - starting with archive table "akdauftrag".
                  - A PickingDate for current day or valid future date: the query will look up just the current, not yet archived orders: i.e. closed orders and orders not closed yet, using the SQL query based on curent table "kdauftrag".
                  - A PickingDate is an invalid date (Max): same query as if PickingDate was set for current day or valid future date will be used.
    */
    basar::Date         ToteDeliveryDate;

    /*! \brief This is one of 2 mandatory Request Dates. Date on which the Customer Order was closed, the Picking was done and Delivery Advice was generated.
         Value interval: <Min, currentDate) U <currentDate, Max>
         NOTE: Dates interpretation:
               1) if ToteDeliveryDate is set to a valid date, the PickingDate must be set to an invalid date 99991231! PickingDate will (thus) be ignored in this case.
                  ToteDeliveryDate can be a past, a current or a future date. Note that there can be totes, wchich will be shipped tomorrow, or next week etc.
                  TnT requests work now also for open (i.e. not closed yet) orders. And of course one can request an overview of totes in the past.
               2) if ToteDeliveryDate is set to a *INVALID* date (Max), the PickingDate will be taken into accont. Its value will be interpreted as follows:
                  - A PickingDate for past, i.e. for yesterday and older dates: the query will look up just the Archive - starting with archive table "akdauftrag".
                  - A PickingDate for current day or valid future date: the query will look up just the current, not yet archived orders: i.e. closed orders and orders not closed yet, using the SQL query based on curent table "kdauftrag".
                  - A PickingDate is an invalid date (Max): same query as if PickingDate was set for current day or valid future date will be used.
    */
    basar::Date         PickingDate;

    /*! \brief Mandatory: flag indicating if also the Line Details are desired */
    bool                DetailsDesired;

    /*! \brief Optional: filter for a specific tour -> if details for a specific tour are desired, the one of the ToteDeliveryDate or PickingDate and only one of the must be defined! */
    basar::VarString    SpecificTourID;

    /*! \brief Optional: flag indicating if also the PharmosOrderNo is needed or not */
    bool                SendPharmosOrderNumbers;

    /*! \brief Optional: flag indicating if also the PickingOrderNo and PickingOrderPageNo is needed or not */
    bool                SendPickingOrderNumbers;

    /*! \brief Optional: flag indicating if also the PackagePosNo is needed or not */
    bool                SendPackagePosNos;

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingDataFilter& shipmentTrackingDataFilter);

private:

    /*! \brief Just an internal helper for estimating use of today's or archive data */
    basar::Date         CurrentDate;

};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_DATAFILTER_H
