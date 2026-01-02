#ifndef GUARD_IBTORDERIMPORT_USECASE_IOBTORDERMANAGERPTR_H
#define GUARD_IBTORDERIMPORT_USECASE_IOBTORDERMANAGERPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport {
namespace useCase {

	class IbtOrderManager;

	typedef boost::shared_ptr<IbtOrderManager> IbtOrderManagerPtr;

} // namespace useCase
} // namespace ibtorderimport

#endif // GUARD_IBTORDERIMPORT_USECASE_IOBTORDERMANAGERPTR_H
