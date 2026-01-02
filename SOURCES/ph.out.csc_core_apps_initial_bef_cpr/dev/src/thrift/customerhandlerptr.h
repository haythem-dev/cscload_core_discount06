#ifndef GUARD_CUSTOMERHANDLER_PTR_H
#define GUARD_CUSTOMERHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "customerhandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<CustomerHandler> CustomerHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CUSTOMERHANDLER_PTR_H
