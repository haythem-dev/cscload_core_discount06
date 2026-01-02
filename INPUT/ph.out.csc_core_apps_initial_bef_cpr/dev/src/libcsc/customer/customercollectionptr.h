#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>
#include <customer/customercollection.h>

namespace libcsc {
namespace customer {

	typedef boost::shared_ptr<CustomerCollection> CustomerCollectionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCOLLECTIONPTR_H
