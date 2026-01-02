#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingRequestProcessingContext;
typedef boost::shared_ptr<ShipmentTrackingRequestProcessingContext> ShipmentTrackingRequestProcessingContextPtr;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_PTR_H
