/*
 * callbackoverviewcollection.h
 *
 *  Created on: 25.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETION_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETION_H

#include "base/dmcollection/dmcollection.h"
#include "icallbackoverviewitemptr.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef base::DmCollection<ICallbackOverviewItemPtr> CallbackOverviewCollection;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWCOLLETION_H
