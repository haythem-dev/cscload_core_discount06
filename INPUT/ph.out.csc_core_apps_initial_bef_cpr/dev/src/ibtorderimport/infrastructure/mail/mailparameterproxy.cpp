#include "mailparameterproxy.h"
#include "mailparameterkeys.h"
#include <infrastructure/parameter/iparametergateway.h> // libutil
#include <loggerpool/ibtorderimport_loggerpool.h>
#include <libbasarlogin.h>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace infrastructure {
namespace mail {

//-------------------------------------------------------------------------------------------------//

MailParameterProxy::~MailParameterProxy()
{
}

//-------------------------------------------------------------------------------------------------//

MailParameterProxy::MailParameterProxy() :
	m_MailServer(),
	m_MailPort(0),
	m_MailSender(),
	m_Recipients()
{
}

//-------------------------------------------------------------------------------------------------//

void MailParameterProxy::injectParameterGateway(libutil::infrastructure::parameter::IParameterGatewayPtr paramGateway)
{
	m_ParamGateway = paramGateway;
}

//-------------------------------------------------------------------------------------------------//

const basar::VarString& MailParameterProxy::getMailServer() const
{
	if (m_MailServer.empty() )
	{
		basar::I18nString areaID;
		areaID.itos(basar::login::Manager::getInstance().getAreaID());
		if (!m_ParamGateway->getParameterValue(areaID, constants::UADM_MAIL_SERVER_KEY, m_MailServer))
		{
			m_ParamGateway->getParameterValue(constants::UADM_MAIL_SERVER_KEY, m_MailServer);
		}
	}
	return m_MailServer;
}

//-------------------------------------------------------------------------------------------------//

basar::Int32 MailParameterProxy::getMailPort() const
{
	if (0 == m_MailPort)
	{
		basar::I18nString val;
		basar::I18nString areaID;
		areaID.itos(basar::login::Manager::getInstance().getAreaID());
		if (!m_ParamGateway->getParameterValue(areaID, constants::UADM_MAIL_PORT_KEY, val))
		{
			m_ParamGateway->getParameterValue(constants::UADM_MAIL_PORT_KEY, val);
		}
		m_MailPort = val.stoi();
	}
	return m_MailPort;
}

//-------------------------------------------------------------------------------------------------//

const basar::VarString& MailParameterProxy::getMailSender() const
{
	if (m_MailSender.empty() )
	{
		basar::I18nString areaID;
		areaID.itos(basar::login::Manager::getInstance().getAreaID());
		if (!m_ParamGateway->getParameterValue(areaID, constants::UADM_MAIL_SENDER_KEY, m_MailSender))
		{
			m_ParamGateway->getParameterValue(constants::UADM_MAIL_SENDER_KEY, m_MailSender);
		}
	}
	return m_MailSender;
}

//-------------------------------------------------------------------------------------------------//

basar::cmnutil::CollBString& MailParameterProxy::getMailRecipients() const
{
	if (m_Recipients.empty())
	{
		readGlobalRecipients();
		readRegionalRecipients();
	}
	return m_Recipients;
}

//-------------------------------------------------------------------------------------------------//

void MailParameterProxy::readRegionalRecipients() const
{
	basar::I18nString	key;
	basar::I18nString	value;
	basar::Int16		index = 1;
	bool				found = false;
	basar::I18nString areaID;

	areaID.itos(basar::login::Manager::getInstance().getAreaID());

	do
	{
		key.format("%s_%d", constants::UADM_MAIL_RECIPIENT_KEY, index);
		found = m_ParamGateway->getParameterValue(areaID, key, value);
		if (true == found)
		{
			m_Recipients.push_back(value);
		}
		index++;
	} while (found == true);
}

//-------------------------------------------------------------------------------------------------//

void MailParameterProxy::readGlobalRecipients() const
{
	basar::I18nString	key;
	basar::I18nString	value;
	basar::Int16		index = 1;
	bool				found = false;

	do
	{
		key.format("%s_%d", constants::UADM_MAIL_RECIPIENT_KEY, index);
		found = m_ParamGateway->getParameterValue(key, value);
		if (true == found)
		{
			m_Recipients.push_back(value);
		}
		index++;
	} while (found == true);
}

//-------------------------------------------------------------------------------------------------//

} // namespace mail
} // namespace infrastructure
} // namespace tenderordercreator

//-------------------------------------------------------------------------------------------------//
