#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEINFOCOLLECTIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEINFOCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>
#include <customer/articleinfo/articleinfocollection.h>

namespace libcsc {
namespace customer {

	typedef boost::shared_ptr<ArticleInfoCollection> ArticleInfoCollectionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEINFOCOLLECTIONPTR_H
