#ifndef GUARD_LIBCSC_CUSTOMER_TENDERINFOPTR_H
#define GUARD_LIBCSC_CUSTOMER_TENDERINFOPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class TenderInfo;
	typedef boost::shared_ptr<TenderInfo> TenderInfoPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TENDERINFOPTR_H
