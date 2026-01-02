#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATASQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATASQLMAPPER_H

#include "shipmenttrackingtourdatamapperbase.h"
#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include "shipmenttracking/packageinformation/shipmenttrackingcurrentwhslinecontextptr.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourDataSQLMapper : public ShipmentTrackingTourDataMapperBase
{
public:
    ShipmentTrackingTourDataSQLMapper(ShipmentTrackingTourDataPtr shipmentTrackingTourData, const basar::db::sql::ResultsetRef resultSet, const basar::VarString& fieldPrefix = "");
    virtual ~ShipmentTrackingTourDataSQLMapper();

    void            mapFromOutboundData();
    void            mapFromWarehouseData(basar::Int32 pickingDate, ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext);

protected:

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingTourDataSQLMapper(const ShipmentTrackingTourDataSQLMapper&);
    ShipmentTrackingTourDataSQLMapper & operator=(const ShipmentTrackingTourDataSQLMapper&);

    basar::db::sql::ResultsetRef    m_ResultSet;
    basar::VarString                m_FieldPrefix;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATASQLMAPPER_H
