/*
 * callbackreasoncollectionptr.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackreasoncollection.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef boost::shared_ptr<CallbackReasonCollection> CallbackReasonCollectionPtr;

inline CallbackReasonCollectionPtr makeCallbackReasonCollection()
{
    return CallbackReasonCollectionPtr(new CallbackReasonCollection());
}

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETIONPTR_H
