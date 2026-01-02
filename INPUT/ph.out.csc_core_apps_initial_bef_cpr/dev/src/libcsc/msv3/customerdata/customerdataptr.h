#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATAPTR_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATAPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {

class CustomerData;
typedef boost::shared_ptr<CustomerData> CustomerDataPtr;

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATAPTR_H
