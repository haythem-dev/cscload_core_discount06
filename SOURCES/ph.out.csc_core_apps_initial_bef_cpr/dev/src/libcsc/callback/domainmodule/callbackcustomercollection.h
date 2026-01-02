/*
 * callbackcustomercollection.h
 *
 *  Created on: 19.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETION_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETION_H

#include "base/dmcollection/dmcollection.h"
#include "icallbackcustomerptr.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef base::DmCollection<ICallbackCustomerPtr> CallbackCustomerCollection;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETION_H
