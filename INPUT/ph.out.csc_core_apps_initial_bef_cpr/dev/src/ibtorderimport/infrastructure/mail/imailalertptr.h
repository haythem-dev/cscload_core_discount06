#ifndef GUARD_INFRASTRUCTURE_IMAILALERTPTR_H
#define GUARD_INFRASTRUCTURE_IMAILALERTPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

	class IMailAlert;

	typedef boost::shared_ptr<IMailAlert> IMailAlertPtr;

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

#endif // GUARD_INFRASTRUCTURE_IMAILALERTPTR_H
