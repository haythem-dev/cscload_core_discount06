#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSEPTR_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSEPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {

class OrderResponse;
typedef boost::shared_ptr<OrderResponse> OrderResponsePtr;

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSEPTR_H
