#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFOPTR_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFOPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class OrderInfo;
	typedef boost::shared_ptr<OrderInfo> OrderInfoPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFOPTR_H
