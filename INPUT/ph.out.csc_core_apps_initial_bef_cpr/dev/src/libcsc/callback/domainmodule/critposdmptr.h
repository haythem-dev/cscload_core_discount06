/*
 * critposdmptr.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDMPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace callback {
namespace domMod {

class CritPosDM;
typedef boost::shared_ptr<CritPosDM> CritPosDMPtr;

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDMPTR_H
