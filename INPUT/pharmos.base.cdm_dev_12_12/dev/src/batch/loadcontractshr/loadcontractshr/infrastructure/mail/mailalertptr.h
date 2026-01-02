#ifndef GUARD_INFRASTRUCTURE_MAILALERTPTR_H
#define GUARD_INFRASTRUCTURE_MAILALERTPTR_H

#include <boost/shared_ptr.hpp>

namespace loadcontractshr {
namespace infrastructure {
namespace mail {

	class MailAlert;

	typedef boost::shared_ptr<MailAlert> MailAlertPtr;

} // namespace mail
} // namespace infrastructure
} // namespace loadcontractshr

#endif // GUARD_INFRASTRUCTURE_MAILALERTPTR_H
