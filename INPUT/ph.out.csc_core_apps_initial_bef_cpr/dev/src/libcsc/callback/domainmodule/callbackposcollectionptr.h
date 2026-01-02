/*
 * callbackposcollectionptr.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackposcollection.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef boost::shared_ptr<CallbackPosCollection> CallbackPosCollectionPtr;

inline CallbackPosCollectionPtr makeCallbackPosCollection()
{
    return CallbackPosCollectionPtr(new CallbackPosCollection());
}

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETIONPTR_H
