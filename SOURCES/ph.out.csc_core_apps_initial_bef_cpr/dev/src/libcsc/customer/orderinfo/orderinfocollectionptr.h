#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>
#include <customer/orderinfo/orderinfocollection.h>

namespace libcsc {
namespace customer {

	typedef boost::shared_ptr<OrderInfoCollection> OrderInfoCollectionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFOCOLLECTIONPTR_H
