#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMERPTR_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class ICustomer;
	typedef boost::shared_ptr<ICustomer> ICustomerPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMERPTR_H
