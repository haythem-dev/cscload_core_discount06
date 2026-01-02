/*
 * callbackitemdmptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CallbackItemDM;
typedef boost::shared_ptr<CallbackItemDM> CallbackItemDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDMPTR_H
