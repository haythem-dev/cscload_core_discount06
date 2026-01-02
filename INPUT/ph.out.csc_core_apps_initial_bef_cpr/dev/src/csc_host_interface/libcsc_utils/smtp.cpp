//-------------------------------------------------------------------------------------------------------------------//
/*! \file		smtp.cpp
*  \brief		representation of config smtp
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "smtp.h"

namespace libcsc_utils
{
namespace config
{
	SMTP::SMTP(void)
	{
		m_Host = "";
		m_Port = 0;
		m_Username = "";
		m_Password = "";
		m_SendMailFrom = "";

		m_IsSetSmtpTypeInformation = false;
		m_IsSetSmtpTypeWarnings = false;
		m_IsSetSmtpTypeErrors = false;
		m_IsSetHost = false;
		m_IsSetPort = false;
		m_IsSetUsername = false;
		m_IsSetPassword = false;
		m_IsSetSendMailFrom = false;
	}


	SMTP::SMTP(basar::VarString const& host, basar::Int32 port, basar::VarString const& username, basar::VarString const& password,
			basar::VarString const& sendMailFrom, basar::VarString const& smtTypeInformation, basar::VarString const& smtTypeWarnings, 
			basar::VarString const& smtTypeErrors)
	{
		m_SmtpTypeList[Information] = smtTypeInformation;
		m_SmtpTypeList[Warnings] = smtTypeWarnings;
		m_SmtpTypeList[Errors] = smtTypeErrors;

		m_Host = host;
		m_Port = port;
		m_Username = username;
		m_Password = password;
		m_SendMailFrom = sendMailFrom;

		m_IsSetSmtpTypeInformation = true;
		m_IsSetSmtpTypeWarnings = true;
		m_IsSetSmtpTypeErrors = true;
		m_IsSetHost = true;
		m_IsSetPort = true;
		m_IsSetUsername = true;
		m_IsSetPassword = true;
		m_IsSetSendMailFrom = true;
	}

	SMTP::~SMTP(void)
	{
	}
		
	void SMTP::setHost(basar::VarString const& value)
	{
		m_Host = value;
		m_IsSetHost = true;
	}

	void SMTP::setPort(basar::Int32 value)
	{
		m_Port = value;
		m_IsSetPort = true;
	}

	void SMTP::setUsername(basar::VarString const& value)
	{
		m_Username = value;
		m_IsSetUsername = true;
	}

	void SMTP::setPassword(basar::VarString const& value)
	{
		m_Password = value;
		m_IsSetPassword = true;
	}

	void SMTP::setSendMailFrom(basar::VarString const& value)
	{
		m_SendMailFrom = value;
		m_IsSetSendMailFrom = true;
	}

	void SMTP::setSmtpTypeInformation(basar::VarString const& value)
	{
		m_SmtpTypeList[Information] = value;
		m_IsSetSmtpTypeInformation = true;
	}

	void SMTP::setSmtpTypeWarnings(basar::VarString const& value)
	{
		m_SmtpTypeList[Warnings] = value;
		m_IsSetSmtpTypeWarnings = true;
	}

	void SMTP::setSmtpTypeErrors(basar::VarString const& value)
	{
		m_SmtpTypeList[Errors] = value;
		m_IsSetSmtpTypeErrors = true;
	}

		
	basar::VarString SMTP::getHost(void) const
	{
		return m_Host;
	}

	basar::Int32 SMTP::getPort(void) const
	{
		return m_Port;
	}

	basar::VarString SMTP::getUsername(void) const
	{
		return m_Username;
	}

	basar::VarString SMTP::getPassword(void) const
	{
		return m_Password;
	}

	basar::VarString SMTP::getSendMailFrom(void) const
	{
		return m_SendMailFrom;
	}

	basar::VarString SMTP::getSmtpTypeInformation(void)
	{
		if (m_SmtpTypeList.find(Information) == m_SmtpTypeList.end())
		{
			return "";
		}
		return m_SmtpTypeList[Information];
	}

	basar::VarString SMTP::getSmtpTypeWarnings(void)
	{
		if (m_SmtpTypeList.find(Warnings) == m_SmtpTypeList.end())
		{
			return "";
		}
		return m_SmtpTypeList[Warnings];
	}

	basar::VarString SMTP::getSmtpTypeErrors(void)
	{
		if (m_SmtpTypeList.find(Errors) == m_SmtpTypeList.end())
		{
			return "";
		}
		return m_SmtpTypeList[Errors];
	}

	bool SMTP::isSetHost(void) const
	{
		return m_IsSetHost;
	}

	bool SMTP::isSetPort(void) const
	{
		return m_IsSetPort;
	}

	bool SMTP::isSetUsername(void) const
	{
		return m_IsSetUsername;
	}

	bool SMTP::isSetPassword(void) const
	{
		return m_IsSetPassword;
	}

	bool SMTP::isSetSendMailFrom(void) const
	{
		return m_IsSetSendMailFrom;
	}

	bool SMTP::isSetSmtpTypeInformation(void) const
	{
		return m_IsSetSmtpTypeInformation;
	}

	bool SMTP::isSetSmtpTypeWarnings(void) const
	{
		return m_IsSetSmtpTypeWarnings;
	}

	bool SMTP::isSetSmtpTypeErrors(void) const
	{
		return m_IsSetSmtpTypeErrors;
	}
}
}
