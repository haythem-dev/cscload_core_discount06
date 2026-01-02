#ifndef GUARD_MAILPARAMETERPROXY_H
#define GUARD_MAILPARAMETERPROXY_H

//-------------------------------------------------------------------------------------------------//

#include "infrastructure/mail/imailparameterproxy.h"
#include <infrastructure/parameter/iparametergatewayptr.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_i18nstring.h>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

//-------------------------------------------------------------------------------------------------//

class MailParameterProxy : public IMailParameterProxy
{
public:
	MailParameterProxy();
	virtual ~MailParameterProxy();


	void injectParameterGateway(libutil::infrastructure::parameter::IParameterGatewayPtr paramGateway);

	virtual const basar::VarString&			getMailServer() const;
	virtual basar::Int32					getMailPort() const;
	virtual const basar::VarString&			getMailSender() const;
	virtual basar::cmnutil::CollBString&	getMailRecipients() const;

private:
	MailParameterProxy(const MailParameterProxy&);
	MailParameterProxy& operator=(const MailParameterProxy&);

	void									readGlobalRecipients() const;
	void									readRegionalRecipients() const;

	libutil::infrastructure::parameter::IParameterGatewayPtr	m_ParamGateway;

	mutable basar::I18nString									m_MailServer;
	mutable basar::Int32										m_MailPort;
	mutable basar::I18nString									m_MailSender;
	mutable basar::cmnutil::CollBString							m_Recipients;
};

//-------------------------------------------------------------------------------------------------//

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_MAILPARAMETERPROXY_H

//-------------------------------------------------------------------------------------------------//
