#ifndef GUARD_CSC_SERVICE_INQUIRYHANDLER_PTR_H
#define GUARD_CSC_SERVICE_INQUIRYHANDLER_PTR_H

#include <boost/shared_ptr.hpp>
#include "inquiryhandler.h"

namespace csc {
namespace service {

typedef boost::shared_ptr<InquiryHandler> InquiryHandlerPtr;

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_INQUIRYHANDLER_PTR_H
