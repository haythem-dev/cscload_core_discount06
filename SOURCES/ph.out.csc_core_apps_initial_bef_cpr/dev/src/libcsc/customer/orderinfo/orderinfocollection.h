#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTION_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTION_H

#include <vector>
#include <customer/orderinfo/iorderinfoptr.h>

namespace libcsc {
namespace customer {

	typedef std::vector<IOrderInfoPtr> OrderInfoCollection;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTION_H
