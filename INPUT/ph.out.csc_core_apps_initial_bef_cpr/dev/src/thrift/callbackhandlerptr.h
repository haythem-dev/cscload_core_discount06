#ifndef GUARD_CSC_SERVICE_CALLBACKHANDLER_PTR_H
#define GUARD_CSC_SERVICE_CALLBACKHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "callbackhandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<CallbackHandler> CallbackHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_CALLBACKHANDLER_PTR_H
