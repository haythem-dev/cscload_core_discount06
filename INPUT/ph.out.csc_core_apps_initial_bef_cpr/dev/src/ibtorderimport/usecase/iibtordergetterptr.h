#ifndef GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTERPTR_H
#define GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport {
namespace useCase {

	class IIbtOrderGetter;

	typedef boost::shared_ptr<IIbtOrderGetter> IIbtOrderGetterPtr;

} // namespace useCase
} // namespace ibtorderimport

#endif // GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTERPTR_H
