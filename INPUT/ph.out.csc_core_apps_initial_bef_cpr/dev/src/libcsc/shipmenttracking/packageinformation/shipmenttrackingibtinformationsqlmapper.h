#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONSQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONSQLMAPPER_H

#include "shipmenttrackingibtinformationsqlmapperptr.h"
#include "shipmenttrackingibtinformationmapperbase.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttrackingcurrentwhslinecontextptr.h"
#include "shipmenttrackingpackagepropertiessqlmapper.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtInformationSQLMapper : public ShipmentTrackingIbtInformationMapperBase
{
public:
    ShipmentTrackingIbtInformationSQLMapper(
        ShipmentTrackingRequestProcessingContextPtr context,
        ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation
    );
    virtual ~ShipmentTrackingIbtInformationSQLMapper();

    void setResultSet(const basar::db::sql::ResultsetRef resultSet);

    void mapFromOutboundData(basar::Int32 cscOrderNo, bool isNarcotic);

    void fillCloneFromOutboundData(const ShipmentTrackingIbtInformationSQLMapper& originalIbtInfoBuilder);

    void mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext);

protected:

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingIbtInformationSQLMapper(const ShipmentTrackingIbtInformationSQLMapper&);
    ShipmentTrackingIbtInformationSQLMapper & operator=(const ShipmentTrackingIbtInformationSQLMapper&);

    basar::db::sql::ResultsetRef      m_ResultSet;

    // tightly connected
    ShipmentTrackingPackagePropertiesSQLMapper m_PackagePropertiesMapper;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONSQLMAPPER_H
