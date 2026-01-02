#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATASQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATASQLMAPPER_H

#include "shipmenttrackingetaanddeliverydatamapperbase.h"
#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingEtaAndDeliveryDataSQLMapper : public ShipmentTrackingEtaAndDeliveryDataMapperBase
{
public:
    ShipmentTrackingEtaAndDeliveryDataSQLMapper(ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData);
    virtual ~ShipmentTrackingEtaAndDeliveryDataSQLMapper();

    //! \brief Get SQL Statement to query Shipment Tracking ETA and "Delivered at" Information from Warehouse database
    static const basar::VarString getSelectSQL(
        const basar::VarString& dbNameWarehouse,
        const std::list<basar::Int32>& pickingDateList,
        const std::list<basar::VarString>& trackingBarcodeList,
        const basar::VarString& transmedStatusDeliveredToCustomerIds
    );

    void setResultSet(const basar::db::sql::ResultsetRef resultSet) { m_ResultSet = resultSet; }

protected:
    //! \brief Mapping Shipment Tracking ETA and Delivery Data from Warehouse database
    virtual void doMapTimesAndComputeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection);
    virtual void doSetTimesAndDelayFallback(EtaDelayEvaluationCollection etaDelayEvaluationCollection);

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingEtaAndDeliveryDataSQLMapper(const ShipmentTrackingEtaAndDeliveryDataSQLMapper&);
    ShipmentTrackingEtaAndDeliveryDataSQLMapper & operator=(const ShipmentTrackingEtaAndDeliveryDataSQLMapper&);

    void computeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection);

    basar::db::sql::ResultsetRef      m_ResultSet;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATASQLMAPPER_H
