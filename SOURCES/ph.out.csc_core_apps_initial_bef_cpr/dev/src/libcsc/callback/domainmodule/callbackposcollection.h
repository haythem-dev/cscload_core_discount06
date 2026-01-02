/*
 * callbackposcollection.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETION_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETION_H

#include "base/dmcollection/dmcollection.h"
#include "icallbackposptr.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef base::DmCollection<ICallbackPosPtr> CallbackPosCollection;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSCOLLETION_H
