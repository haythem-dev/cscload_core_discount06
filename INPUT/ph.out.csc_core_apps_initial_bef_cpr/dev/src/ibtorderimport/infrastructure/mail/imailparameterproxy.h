#ifndef GUARD_IMAILPARAMETERPROXY_H
#define GUARD_IMAILPARAMETERPROXY_H

//-------------------------------------------------------------------------------------------------//

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

//-------------------------------------------------------------------------------------------------//

class IMailParameterProxy
{
public:
	virtual ~IMailParameterProxy() {};

	virtual const basar::VarString&			getMailServer() const = 0;
	virtual basar::Int32					getMailPort() const = 0;
	virtual const basar::VarString&			getMailSender() const = 0;
	virtual basar::cmnutil::CollBString&	getMailRecipients() const = 0;
};

//-------------------------------------------------------------------------------------------------//

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IMAILPARAMETERPROXY_H

//-------------------------------------------------------------------------------------------------//
