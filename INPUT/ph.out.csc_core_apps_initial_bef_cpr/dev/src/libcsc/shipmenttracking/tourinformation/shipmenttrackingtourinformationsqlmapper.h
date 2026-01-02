#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_H

#include "shipmenttrackingtourinformationsqlmapperptr.h"
#include "shipmenttrackingtourinformationmapperbase.h"
#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include <libbasardbsql_resultsetref.h>
#include <persistence/iaccessorptr.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourInformationSQLMapper : public ShipmentTrackingTourInformationMapperBase
{
public:
    ShipmentTrackingTourInformationSQLMapper(ShipmentTrackingTourInformationPtr shipmentTrackingTourInformation);
    virtual ~ShipmentTrackingTourInformationSQLMapper();

    void mapShipmentTrackingTourInformationFromOutboundData(const basar::db::sql::ResultsetRef resultSet);
    void mapShipmentTrackingTourInformationFromWarehouseData(ShipmentTrackingTourDataPtr redirectedToTourData);

protected:

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingTourInformationSQLMapper(const ShipmentTrackingTourInformationSQLMapper&);
    ShipmentTrackingTourInformationSQLMapper & operator=(const ShipmentTrackingTourInformationSQLMapper&);

    basar::db::sql::ResultsetRef      m_ResultSet;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_H
