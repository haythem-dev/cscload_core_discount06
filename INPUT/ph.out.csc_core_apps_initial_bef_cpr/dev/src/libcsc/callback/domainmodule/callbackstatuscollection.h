/*
 * callbackstatuscollection.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETION_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETION_H

#include "base/dmcollection/dmcollection.h"
#include "icallbackstatusptr.h"

namespace libcsc {
	namespace callback {
		namespace domMod {

			typedef base::DmCollection<ICallbackStatusPtr> CallbackStatusCollection;

		} // namespace domMod
	} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETION_H
