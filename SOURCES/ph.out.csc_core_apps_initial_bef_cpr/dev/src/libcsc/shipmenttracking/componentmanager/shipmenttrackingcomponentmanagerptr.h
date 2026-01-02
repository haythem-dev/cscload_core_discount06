#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingComponentManager;
typedef boost::shared_ptr<libcsc::shipmenttracking::ShipmentTrackingComponentManager> ShipmentTrackingComponentManagerPtr;

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_PTR_H
