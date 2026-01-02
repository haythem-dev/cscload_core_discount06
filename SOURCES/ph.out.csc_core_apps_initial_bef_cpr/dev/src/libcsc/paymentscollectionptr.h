#pragma once
#ifndef GUARD_LIBCSC_CUSTOMER_PAYMENTSCOLLECTIONPTR_H
#define GUARD_LIBCSC_CUSTOMER_PAYMENTSCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>
#include <customer/payments/paymentscollection.h>

namespace libcsc {
	namespace customer {

		typedef boost::shared_ptr<PaymentsCollection> CustomerConditionCollectionPtr;

	} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PAYMENTSCOLLECTIONPTR_H