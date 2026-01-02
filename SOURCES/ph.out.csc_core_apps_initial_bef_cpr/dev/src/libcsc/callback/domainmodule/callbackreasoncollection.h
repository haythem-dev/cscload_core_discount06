/*
 * callbackreasoncollection.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETION_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETION_H

#include "base/dmcollection/dmcollection.h"
#include "icallbackreasonptr.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef base::DmCollection<ICallbackReasonPtr> CallbackReasonCollection;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONCOLLETION_H
