/*
 * callbackoverviewitemdmptr.h
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CallbackOverviewItemDM;
typedef boost::shared_ptr<CallbackOverviewItemDM> CallbackOverviewItemDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDMPTR_H
