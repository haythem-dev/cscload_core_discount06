#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORYPTR_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

class ICustomerRepository;
typedef boost::shared_ptr<ICustomerRepository> ICustomerRepositoryPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORYPTR_H
