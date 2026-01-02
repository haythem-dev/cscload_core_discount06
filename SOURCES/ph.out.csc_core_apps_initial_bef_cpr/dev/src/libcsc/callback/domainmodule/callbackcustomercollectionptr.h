/*
 * callbackcustomercollectionptr.h
 *
 *  Created on: 19.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackcustomercollection.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef boost::shared_ptr<CallbackCustomerCollection> CallbackCustomerCollectionPtr;

inline CallbackCustomerCollectionPtr makeCallbackCustomerCollection()
{
    return CallbackCustomerCollectionPtr(new CallbackCustomerCollection());
}

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERCOLLETIONPTR_H
