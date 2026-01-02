/*
 * critdmptr.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CritDM;
typedef boost::shared_ptr<CritDM> CritDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDMPTR_H
