/*
 * callbackdmptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CallbackDM;
typedef boost::shared_ptr<CallbackDM> CallbackDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDMPTR_H
