#ifndef GUARD_RETURNSHANDLER_PTR_H
#define GUARD_RETURNSHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "returnshandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<ReturnsHandler> ReturnsHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_RETURNSHANDLER_PTR_H
