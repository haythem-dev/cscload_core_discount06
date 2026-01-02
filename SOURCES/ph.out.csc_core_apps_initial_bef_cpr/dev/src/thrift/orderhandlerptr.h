#ifndef GUARD_CSC_SERVICE_ORDERHANDLER_PTR_H
#define GUARD_CSC_SERVICE_ORDERHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "orderhandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<OrderHandler> OrderHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_ORDERHANDLER_PTR_H
