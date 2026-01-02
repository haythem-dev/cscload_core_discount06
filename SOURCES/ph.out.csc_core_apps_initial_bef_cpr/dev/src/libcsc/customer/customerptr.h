#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERPTR_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class Customer;
	typedef boost::shared_ptr<Customer> CustomerPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERPTR_H
