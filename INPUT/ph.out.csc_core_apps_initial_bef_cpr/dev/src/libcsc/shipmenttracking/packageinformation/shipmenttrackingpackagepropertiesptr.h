#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageProperties;
typedef boost::shared_ptr<ShipmentTrackingPackageProperties> ShipmentTrackingPackagePropertiesPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageProperties& shipmentTrackingPackageProperties);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageProperties* shipmentTrackingPackageProperties);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackagePropertiesPtr shipmentTrackingPackageProperties);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_PTR_H
