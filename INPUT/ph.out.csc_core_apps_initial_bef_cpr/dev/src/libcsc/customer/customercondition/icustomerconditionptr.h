#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITIONPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class ICustomerCondition;
	typedef boost::shared_ptr<ICustomerCondition> ICustomerConditionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITIONPTR_H
