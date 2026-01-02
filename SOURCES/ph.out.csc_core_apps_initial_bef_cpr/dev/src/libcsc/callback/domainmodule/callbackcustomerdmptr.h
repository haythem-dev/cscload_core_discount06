/*
 * callbackcustomerdmptr.h
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CallbackCustomerDM;
typedef boost::shared_ptr<CallbackCustomerDM> CallbackCustomerDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDMPTR_H
