#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingRepository;
typedef boost::shared_ptr<ShipmentTrackingRepository> ShipmentTrackingRepositoryPtr;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_PTR_H
