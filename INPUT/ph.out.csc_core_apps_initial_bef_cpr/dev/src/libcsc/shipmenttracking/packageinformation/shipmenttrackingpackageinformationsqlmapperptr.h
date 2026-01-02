#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageInformationSQLMapper;
typedef boost::shared_ptr<ShipmentTrackingPackageInformationSQLMapper> ShipmentTrackingPackageInformationSQLMapperPtr;

typedef std::list<ShipmentTrackingPackageInformationSQLMapperPtr> ShipmentTrackingPackageInformationSQLMapperCollection;

typedef boost::shared_ptr<ShipmentTrackingPackageInformationSQLMapperCollection> ShipmentTrackingPackageInformationSQLMapperCollectionPtr;

typedef std::map<std::string, ShipmentTrackingPackageInformationSQLMapperPtr> ShipmentTrackingPackageInformationSQLMapperStrMap;
typedef std::map<basar::Int32, ShipmentTrackingPackageInformationSQLMapperPtr> ShipmentTrackingPackageInformationSQLMapperInt32Map;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_PTR_H
