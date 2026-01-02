#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESSQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESSQLMAPPER_H

#include "shipmenttrackingpackagepropertiesmapperbase.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttrackingcurrentwhslinecontextptr.h"

#include <libbasardbsql_resultsetref.h>


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackagePropertiesSQLMapper : public ShipmentTrackingPackagePropertiesMapperBase
{
public:
    ShipmentTrackingPackagePropertiesSQLMapper(
        ShipmentTrackingRequestProcessingContextPtr context,
        ShipmentTrackingPackagePropertiesPtr packageProperties,
        const basar::VarString& fieldPrefix = ""
    );
    virtual ~ShipmentTrackingPackagePropertiesSQLMapper();

    void setResultSet(const basar::db::sql::ResultsetRef resultSet) { m_ResultSet = resultSet; }

    void mapFromOutboundData(basar::Int32 cscOrderNo, bool isNarcotic);

    void fillCloneFromOutboundData(const ShipmentTrackingPackagePropertiesSQLMapper& originalPackagePropertiesBuilder);

    void mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext) { mapFromWarehouseData(currentWhsLineContext, false); }
    void mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext, bool updateCustomerPartFromIbtForMissingLocalIbt);

protected:

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingPackagePropertiesSQLMapper(const ShipmentTrackingPackagePropertiesSQLMapper&);
    ShipmentTrackingPackagePropertiesSQLMapper & operator=(const ShipmentTrackingPackagePropertiesSQLMapper&);

    //! \brief Request Processing Context info, like User's choice, server file config data, etc.
    ShipmentTrackingRequestProcessingContextPtr             m_Context;

    basar::db::sql::ResultsetRef  m_ResultSet;
    basar::VarString              m_FieldPrefix;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESSQLMAPPER_H
