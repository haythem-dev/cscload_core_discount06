#ifndef GUARD_INFRASTRUCTURE_IMAILALERT_H
#define GUARD_INFRASTRUCTURE_IMAILALERT_H

#include <libbasar_definitions.h>

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

class IMailAlert
{
public:
	virtual ~IMailAlert() {};

	virtual bool send(const basar::VarString&, const basar::VarString&) = 0;
};

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

#endif // GUARD_INFRASTRUCTURE_IMAILALERT_H
