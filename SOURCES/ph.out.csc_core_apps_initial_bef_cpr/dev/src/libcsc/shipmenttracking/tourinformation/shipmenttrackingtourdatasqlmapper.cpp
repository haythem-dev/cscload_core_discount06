#include "shipmenttrackingtourdatasqlmapper.h"
#include "shipmenttrackingtourdata.h"
#include "shipmenttracking/packageinformation/shipmenttrackingcurrentwhslinecontext.h"

#include <libbasarcmnutil_timespan.h>
#include <util/loggingutils.h>

#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingTourDataSQLMapper::ShipmentTrackingTourDataSQLMapper(ShipmentTrackingTourDataPtr shipmentTrackingTourData, const basar::db::sql::ResultsetRef resultSet, const basar::VarString& fieldPrefix) :
    ShipmentTrackingTourDataMapperBase(shipmentTrackingTourData),
    m_ResultSet(resultSet),
    m_FieldPrefix(fieldPrefix)
{
}


ShipmentTrackingTourDataSQLMapper::~ShipmentTrackingTourDataSQLMapper()
{
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Tour Data Information from Outbound database
//----------------------------------------------------------------------------------
void ShipmentTrackingTourDataSQLMapper::mapFromOutboundData()
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingTourDataSQLMapper::mapFromOutboundData()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setTourId               (m_ResultSet.getString(m_FieldPrefix + "touridxori"));          // <- (a)kdauftragpostour.tourid (== dktsv.tsv_tour)

    int deliveryDate = m_ResultSet.getInt32(m_FieldPrefix + "deliverydatexori");            // integer formatted date (YYYYMMDD)
    setDeliveryDate         (deliveryDate);

    int deliveryTime = m_ResultSet.getInt16(m_FieldPrefix + "deliverytimexori") * 100000;   // integer formatted time (hhmmssttt)

    setPlannedTimeOfArrival(basar::DateTime(deliveryDate, deliveryTime));                   // <- (a)kdauftragpostour.deliverydate + (a)kdauftragpostour.deliverytime
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Tour Data Information from Warehouse database
//----------------------------------------------------------------------------------
void ShipmentTrackingTourDataSQLMapper::mapFromWarehouseData(basar::Int32 pickingDate, ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext)
{
    //METHODNAME_DEF(ShipmentTrackingTourDataSQLMapper, mapFromWarehouseData);
    //BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << pickingDate);

    basar::VarString tourId = currentWhsLineContext->getTourId();           // DKTSV.tsv_tour
    setTourId                   (tourId);                                   // <- (a)kdauftragpostour.tourid (== dktsv.tsv_tour)

    // -----------------------------
    // Compute PlannedTimeOfArrival:
    int tourDepartureTime = atoi(tourId.substr(0, 4).c_str());              // integer formatted time [hhmm]
    int addDays = 0;
    while (tourDepartureTime >= 2400)
    {
        addDays++;
        tourDepartureTime -= 2400;
    }
    tourDepartureTime *= 100000;                                            // integer formatted time (hhmmssttt)

    basar::DateTime plannedTimeOfArrival(pickingDate, tourDepartureTime);

    // -------------------------
    // Compute Delivery Duration (Fahrzeit):
    int deliveryDurationInMin = currentWhsLineContext->getDeliveryDurationInMin();  // time span in minutes: DKTSV.tsv_fahrzeit
    
    // convert from minutes to: HHmm
    int addHours = 0;
    while (deliveryDurationInMin >= 60)
    {
        addHours++;
        deliveryDurationInMin -= 60;
    }

    // update addDays if addHours > 24
    while (addHours >= 24)
    {
        addDays++;
        addHours -= 24;
    }

    int deliveryDuration = (addHours * 100 + deliveryDurationInMin) * 100000; // convert from minutes to Basar addTime fomrat: integer formatted time (hhmmssttt) to add, can be negative

    // ----------------------
    // Apply computed values:
    if (addDays > 0)
    {
        plannedTimeOfArrival.addDays(addDays);
    }

    plannedTimeOfArrival.addTime(deliveryDuration);

    setPlannedTimeOfArrival (plannedTimeOfArrival);                         // <- dktsv.tsv_tran_date + (substring(dktsv.tsv_tour, 4) as HH:mm) + dktsv.tsv_fahrzeit UNITS MINUTE; Note: time from TourId format: HH:mm/BH

    setDeliveryDate         (plannedTimeOfArrival.getDate());

    //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "tourId: " << tourId << ", tourDepartureTime: " << tourDepartureTime << ", addDays: " << addDays << ", addHours: " << addHours << ", deliveryDurationInMin: " << deliveryDurationInMin << ", deliveryDuration: " << deliveryDuration << ", " << m_TourData);
}

} // end namespace shipmenttracking
} // end namespace libcsc
