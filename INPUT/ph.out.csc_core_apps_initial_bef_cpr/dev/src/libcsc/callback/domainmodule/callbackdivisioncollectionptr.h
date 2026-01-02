/*
 * callbackdivisioncollectionptr.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONCOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONCOLLETIONPTR_H

#include <boost/shared_ptr.hpp>
#include "callbackdivisioncollection.h"

namespace libcsc {
namespace callback {
namespace domMod {

typedef boost::shared_ptr<CallbackDivisionCollection> CallbackDivisionCollectionPtr;

inline CallbackDivisionCollectionPtr makeCallbackDivisionCollection()
{
    return CallbackDivisionCollectionPtr(new CallbackDivisionCollection());
}

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONCOLLETIONPTR_H
