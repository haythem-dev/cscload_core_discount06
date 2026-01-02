#ifndef GUARD_INFRASTRUCTURE_MAILALERTPTR_H
#define GUARD_INFRASTRUCTURE_MAILALERTPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtrelevantcalculator {
namespace infrastructure {
namespace mail {

	class MailAlert;

	typedef boost::shared_ptr<MailAlert> MailAlertPtr;

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

#endif // GUARD_INFRASTRUCTURE_MAILALERTPTR_H
