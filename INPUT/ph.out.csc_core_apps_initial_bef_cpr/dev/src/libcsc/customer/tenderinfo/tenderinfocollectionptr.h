#ifndef GUARD_LIBCSC_CUSTOMER_TENDERINFOCOLLECTIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_TENDERINFOCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>
#include <customer/tenderinfo/tenderinfocollection.h>

namespace libcsc {
namespace customer {

	typedef boost::shared_ptr<TenderInfoCollection> TenderInfoCollectionPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TENDERINFOCOLLECTIONPTR_H
