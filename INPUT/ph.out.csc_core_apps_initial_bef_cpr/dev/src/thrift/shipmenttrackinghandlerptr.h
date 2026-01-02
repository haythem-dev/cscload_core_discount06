#ifndef GUARD_CSC_SERVICE_SHIPMENTTRACKINGHANDLER_PTR_H
#define GUARD_CSC_SERVICE_SHIPMENTTRACKINGHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "shipmenttrackinghandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<ShipmentTrackingHandler> ShipmentTrackingHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_SHIPMENTTRACKINGHANDLER_PTR_H
