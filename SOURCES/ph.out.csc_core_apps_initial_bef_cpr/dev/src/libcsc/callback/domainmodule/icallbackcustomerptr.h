/*
 * icallbackcustomerptr.h
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMERPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackCustomer;
typedef boost::shared_ptr<ICallbackCustomer> ICallbackCustomerPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMERPTR_H
