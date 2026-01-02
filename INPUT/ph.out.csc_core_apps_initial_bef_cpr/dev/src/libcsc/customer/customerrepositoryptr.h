#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORYPTR_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

class CustomerRepository;
typedef boost::shared_ptr<CustomerRepository> CustomerRepositoryPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORYPTR_H
