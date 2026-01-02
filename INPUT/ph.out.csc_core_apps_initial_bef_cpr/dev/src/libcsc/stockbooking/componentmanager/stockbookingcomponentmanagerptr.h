#ifndef GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace stockbooking {

class StockBookingComponentManager;
typedef boost::shared_ptr<StockBookingComponentManager> StockBookingComponentManagerPtr;

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_PTR_H
