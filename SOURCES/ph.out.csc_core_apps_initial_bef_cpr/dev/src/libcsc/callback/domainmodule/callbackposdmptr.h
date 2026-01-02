/*
 * callbackposdmptr.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CallbackPosDM;
typedef boost::shared_ptr<CallbackPosDM> CallbackPosDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDMPTR_H
