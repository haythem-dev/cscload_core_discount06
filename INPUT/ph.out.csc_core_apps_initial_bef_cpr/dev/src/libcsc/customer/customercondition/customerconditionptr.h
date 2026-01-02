#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class CustomerCondition;
	typedef boost::shared_ptr<CustomerCondition> CustomerConditionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONPTR_H
