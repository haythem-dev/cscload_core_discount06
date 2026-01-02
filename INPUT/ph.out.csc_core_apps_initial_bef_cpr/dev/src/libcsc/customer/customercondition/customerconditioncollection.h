#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONCOLLECTION_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONCOLLECTION_H

#include <vector>
#include <customer/customercondition/icustomerconditionptr.h>

namespace libcsc {
namespace customer {

	typedef std::vector<ICustomerConditionPtr> CustomerConditionCollection;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONCOLLECTION_H
