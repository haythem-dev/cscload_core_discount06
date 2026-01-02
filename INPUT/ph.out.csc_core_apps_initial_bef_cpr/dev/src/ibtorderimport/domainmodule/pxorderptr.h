#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXORDERPTR_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXORDERPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport {
namespace domMod {

	class PxOrder;

	typedef boost::shared_ptr<PxOrder> PxOrderPtr;

} // namespace domMod
} // namespace ibtorderimport

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXORDERPTR_H
