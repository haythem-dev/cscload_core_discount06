/*
 * newcallbackdmptr.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class NewCallbackDM;
typedef boost::shared_ptr<NewCallbackDM> NewCallbackDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDMPTR_H
