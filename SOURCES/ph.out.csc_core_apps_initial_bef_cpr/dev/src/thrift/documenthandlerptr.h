#ifndef GUARD_CSC_SERVICE_DOCUMENTHANDLER_PTR_H
#define GUARD_CSC_SERVICE_DOCUMENTHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "documenthandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<DocumentHandler> DocumentHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_DOCUMENTHANDLER_PTR_H
