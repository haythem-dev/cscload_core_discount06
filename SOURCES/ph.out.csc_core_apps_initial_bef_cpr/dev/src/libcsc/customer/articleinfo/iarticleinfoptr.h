#ifndef GUARD_LIBCSC_CUSTOMER_IARTICLEINFOPTR_H
#define GUARD_LIBCSC_CUSTOMER_IARTICLEINFOPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

	class IArticleInfo;
	typedef boost::shared_ptr<IArticleInfo> IArticleInfoPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IARTICLEINFOPTR_H
