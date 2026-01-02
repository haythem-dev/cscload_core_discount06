#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTION_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTION_H

#include <vector>
#include <customer/icustomerptr.h>

namespace libcsc {
namespace customer {

	typedef std::vector<ICustomerPtr> CustomerCollection;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTION_H
