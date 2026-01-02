/*
 * icallbackposptr.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOSPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOSPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackPos;
typedef boost::shared_ptr<ICallbackPos> ICallbackPosPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOSPTR_H
