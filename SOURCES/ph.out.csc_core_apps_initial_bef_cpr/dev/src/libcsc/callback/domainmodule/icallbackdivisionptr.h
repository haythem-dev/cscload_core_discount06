/*
 * icallbackdivisionptr.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKDIVISIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKDIVISIONPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackDivision;
typedef boost::shared_ptr<ICallbackDivision> ICallbackDivisionPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKDIVISIONPTR_H
