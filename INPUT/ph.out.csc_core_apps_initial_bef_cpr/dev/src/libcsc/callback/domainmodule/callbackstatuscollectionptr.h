/*
 * callbackdivisioncollectionptr.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackstatuscollection.h"

namespace libcsc {
    namespace callback {
        namespace domMod {

            typedef boost::shared_ptr<CallbackStatusCollection> CallbackStatusCollectionPtr;

            inline CallbackStatusCollectionPtr makeCallbackStatusCollection()
            {
                return CallbackStatusCollectionPtr(new CallbackStatusCollection());
            }

        } // namespace domMod
    } // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSCOLLETIONPTR_H
