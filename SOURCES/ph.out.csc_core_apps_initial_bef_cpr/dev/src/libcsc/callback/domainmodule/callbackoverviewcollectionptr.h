/*
 * callbackoverviewcollectionptr.h
 *
 *  Created on: 25.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackoverviewcollection.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef boost::shared_ptr<CallbackOverviewCollection> CallbackOverviewCollectionPtr;

inline CallbackOverviewCollectionPtr makeCallbackOverviewCollection()
{
    return CallbackOverviewCollectionPtr(new CallbackOverviewCollection());
}

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETIONPTR_H
