#ifndef GUARD_LIBCSC_CUSTOMER_IORDERINFOPTR_H
#define GUARD_LIBCSC_CUSTOMER_IORDERINFOPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class IOrderInfo;
	typedef boost::shared_ptr<IOrderInfo> IOrderInfoPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IORDERINFOPTR_H
