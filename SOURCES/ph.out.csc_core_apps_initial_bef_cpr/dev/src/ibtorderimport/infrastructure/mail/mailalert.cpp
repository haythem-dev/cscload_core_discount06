#include "mailalert.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include "imailparameterproxy.h"
#include <libbasarcmnutil_email.h>
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

//-----------------------------------------------------------------------------------------

MailAlert::MailAlert(const log4cplus::Logger& logger) :
	m_Logger(logger)
{
}

//-----------------------------------------------------------------------------------------

MailAlert::~MailAlert()
{
}

//-----------------------------------------------------------------------------------------

void MailAlert::injectParameterProxy( IMailParameterProxyPtr paramProxy )
{
	m_ParamProxy = paramProxy;
}

//-----------------------------------------------------------------------------------------

const log4cplus::Logger& MailAlert::getLogger()
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------

bool MailAlert::send(const basar::VarString& subject, const basar::VarString& body)
{
	basar::cmnutil::Smtp		smtpServer( getMailServer(), static_cast<basar::Int16>(getMailPort()) );   // todo parameter!!!
	basar::cmnutil::MailMessage	mail;

	mail.setContentType(basar::cmnutil::MailMessage::TEXT_PLAIN);
	mail.setFrom( getMailSender() );
	basar::cmnutil::CollBString::const_iterator it = getMailRecipients().begin();
	while (it != getMailRecipients().end())
	{
		mail.setTo(*it);
		++it;
	}
	mail.setSubject(subject);
	mail.setBody(body);

	basar::cmnutil::Smtp::RetCodeEnum retval = smtpServer.connect();
	if (retval == basar::cmnutil::Smtp::SMTP_SUCCESS)
	{
		retval = smtpServer.send(mail);
		smtpServer.disconnect();
	}
	return (basar::cmnutil::Smtp::SMTP_SUCCESS == retval);
}

//-----------------------------------------------------------------------------------------

const basar::VarString& MailAlert::getMailServer()
{
	return m_ParamProxy->getMailServer();
}

//-----------------------------------------------------------------------------------------

basar::Int32 MailAlert::getMailPort()
{
	return m_ParamProxy->getMailPort();
}

//-----------------------------------------------------------------------------------------

const basar::VarString& MailAlert::getMailSender()
{
	return m_ParamProxy->getMailSender();
}

//-----------------------------------------------------------------------------------------

basar::cmnutil::CollBString& MailAlert::getMailRecipients()
{
	return m_ParamProxy->getMailRecipients();
}

//-----------------------------------------------------------------------------------------

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

//-----------------------------------------------------------------------------------------
