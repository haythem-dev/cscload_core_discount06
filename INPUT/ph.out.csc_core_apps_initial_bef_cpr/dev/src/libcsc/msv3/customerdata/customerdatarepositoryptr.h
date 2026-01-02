#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATAREPOSITORYPTR_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATAREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace msv3 {

class CustomerDataRepository;
typedef boost::shared_ptr<CustomerDataRepository> CustomerDataRepositoryPtr;

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATAREPOSITORYPTR_H
