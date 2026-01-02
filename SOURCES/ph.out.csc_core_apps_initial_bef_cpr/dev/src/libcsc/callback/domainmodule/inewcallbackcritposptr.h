/*
 * inewcallbackcritposptr.h
 *
 *  Created on: 30.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOSPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOSPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class INewCallbackCritPos;
typedef boost::shared_ptr<INewCallbackCritPos> INewCallbackCritPosPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOSPTR_H
