/*
 * callbackstatusdmptr.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
	namespace callback {
		namespace domMod {

			class CallbackStatusDM;
			typedef boost::shared_ptr<CallbackStatusDM> CallbackStatusDMPtr;

		} // namespace domMod
	} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSDMPTR_H
