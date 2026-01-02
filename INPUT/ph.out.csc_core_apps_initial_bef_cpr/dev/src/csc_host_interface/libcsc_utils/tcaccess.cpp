//-------------------------------------------------------------------------------------------------------------------//
/*! \file		tcaccess.cpp
*  \brief		representation of config tcaccess
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "tcaccess.h"

namespace libcsc_utils
{
namespace config
{

	TCAccess::TCAccess(void)
	{
		m_TcaHost = "";
		m_IpAddress = "";
		m_Port = 0;
		m_TcaTransaction = "";
		m_Username = "";
		m_Password = "";
		m_CicsLinkProgram = "";
		m_ComareaLength = 0;
		m_Activate = true;

		// default values
		m_ConnectionRetries = 5;
		m_ConnectionWaitBeforeRetry = 5000;

		m_IsSetTcaHost = false;
		m_IsSetIpAddress = false;
		m_IsSetPort = false;
		m_IsSetTcaTransaction = false;
		m_IsSetUsername = false;
		m_IsSetPassword = false;
		m_IsSetCicsLinkProgram = false;
		m_IsSetComareaLength = false;
		m_IsSetConnectionRetries = false;
		m_IsSetConnectionWaitBeforeRetry = false;
		m_IsSetActivate = false;
	}

	TCAccess::TCAccess(basar::VarString const& tcaHost, basar::VarString const& ipAddress, basar::Int32 port, basar::VarString const& tcaTransaction,
			basar::VarString const& username, basar::VarString const& password, basar::VarString const& cicsLinkProgram, basar::Int32 comareaLength)
	{
		m_TcaHost = tcaHost;
		m_IpAddress = ipAddress;
		m_Port = port;
		m_TcaTransaction = tcaTransaction;
		m_Username = username;
		m_Password = password;
		m_CicsLinkProgram = cicsLinkProgram;
		m_ComareaLength = comareaLength;
		m_Activate = true;

		m_IsSetTcaHost = true;
		m_IsSetIpAddress = true;
		m_IsSetPort = true;
		m_IsSetTcaTransaction = true;
		m_IsSetUsername = true;
		m_IsSetPassword = true;
		m_IsSetCicsLinkProgram = true;
		m_IsSetComareaLength = true;
		m_IsSetActivate = false;
	}

	TCAccess::~TCAccess(void)
	{
	}

	void TCAccess::setTcaHost (basar::VarString const& value)
	{
		m_TcaHost = value;
		m_IsSetTcaHost = true;
	}

	void TCAccess::setIpAddress (basar::VarString const& value)
	{
		m_IpAddress = value;
		m_IsSetIpAddress = true;
	}

	void TCAccess::setPort (basar::Int32 value)
	{
		m_Port = value;
		m_IsSetPort = true;
	}

	void TCAccess::setTcaTransaction (basar::VarString const& value)
	{
		m_TcaTransaction = value;
		m_IsSetTcaTransaction = true;
	}

	void TCAccess::setUsername (basar::VarString const& value)
	{
		m_Username = value;
		m_IsSetUsername = true;
	}

	void TCAccess::setPassword (basar::VarString const& value)
	{
		m_Password = value;
		m_IsSetPassword = true;
	}

	void TCAccess::setCicsLinkProgram (basar::VarString const& value)
	{
		m_CicsLinkProgram = value;
		m_IsSetCicsLinkProgram = true;
	}

	void TCAccess::setComareaLength (basar::Int32 value)
	{
		m_ComareaLength = value;
		m_IsSetComareaLength = true;
	}

	void TCAccess::setConnectionRetries(basar::Int32 value)
	{
		m_ConnectionRetries = value;
		m_IsSetConnectionRetries = true;
	}

	void TCAccess::setConnWaitBeforeRetry(basar::Int32 value)
	{
		m_ConnectionWaitBeforeRetry = value;
		m_IsSetConnectionWaitBeforeRetry = true;
	}

	void TCAccess::setActivate(bool value)
	{
		m_Activate = value;
		m_IsSetActivate = true;
	}

	basar::VarString TCAccess::getTcaHost (void) const
	{
		return m_TcaHost;
	}

	basar::VarString TCAccess::getIpAddress (void) const
	{
		return m_IpAddress;
	}

	basar::Int32 TCAccess::getPort (void) const
	{
		return m_Port;
	}

	basar::VarString TCAccess::getTcaTransaction (void) const
	{
		return m_TcaTransaction;
	}

	basar::VarString TCAccess::getUsername (void) const
	{
		return m_Username;
	}

	basar::VarString TCAccess::getPassword (void) const
	{
		return m_Password;
	}

	basar::VarString TCAccess::getCicsLinkProgram (void) const
	{
		return m_CicsLinkProgram;
	}

	basar::Int32 TCAccess::getComareaLength (void) const
	{
		return m_ComareaLength;
	}

	basar::Int32 TCAccess::getConnectionRetries(void) const
	{
		return m_ConnectionRetries;
	}

	basar::Int32 TCAccess::getConnWaitBeforeRetry(void) const
	{
		return m_ConnectionWaitBeforeRetry;
	}

	bool TCAccess::getActivate(void) const
	{
		return m_Activate;
	}

	bool TCAccess::isSetTcaHost (void) const
	{
		return m_IsSetTcaHost;
	}

	bool TCAccess::isSetIpAddress (void) const
	{
		return m_IsSetIpAddress;
	}

	bool TCAccess::isSetPort (void) const
	{
		return m_IsSetPort;
	}

	bool TCAccess::isSetTcaTransaction (void) const
	{
		return m_IsSetTcaTransaction;
	}

	bool TCAccess::isSetUsername (void) const
	{
		return m_IsSetUsername;
	}

	bool TCAccess::isSetPassword (void) const
	{
		return m_IsSetPassword;
	}

	bool TCAccess::isSetCicsLinkProgram (void) const
	{
		return m_IsSetCicsLinkProgram;
	}

	bool TCAccess::isSetComareaLength (void) const
	{
		return m_IsSetComareaLength;
	}

	bool TCAccess::isSetConnectionRetries(void) const
	{
		return m_IsSetConnectionRetries;
	}

	bool TCAccess::isSetConnWaitBeforeRetry(void) const
	{
		return m_IsSetConnectionWaitBeforeRetry;
	}

	bool TCAccess::isSetActivate(void) const
	{
		return m_IsSetActivate;
	}
}
}
