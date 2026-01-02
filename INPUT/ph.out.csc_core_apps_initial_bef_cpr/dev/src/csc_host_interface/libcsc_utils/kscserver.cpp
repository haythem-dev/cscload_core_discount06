//-------------------------------------------------------------------------------------------------------------------//
/*! \file		kscserver.cpp
*  \brief		representation of config kscserver
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "kscserver.h"

namespace libcsc_utils
{
namespace config
{
	KSCServer::KSCServer(void)
	{
		m_KscHost = "";
		m_Port = 0;
		m_TerminalName = "";

		// default value
		m_FinishOrderType = "CL";

		m_IsSetKscHost = false;
		m_IsSetPort = false;
		m_IsSetTerminalName = false;
		m_IsSetFinishOrderType = false;
	}

	KSCServer::KSCServer(basar::VarString const& kscHost, basar::Int32 port, basar::VarString const& terminalName, basar::VarString const& finishOrderType)
	{
		m_KscHost = kscHost;
		m_Port = port;
		m_TerminalName = terminalName;
		m_FinishOrderType = finishOrderType;

		m_IsSetKscHost = true;
		m_IsSetPort = true;
		m_IsSetTerminalName = true;
		m_IsSetFinishOrderType = true;
	}

	KSCServer::~KSCServer(void)
	{
	}

	void KSCServer::setKscHost(basar::VarString const& value)
	{
		m_KscHost = value;
		m_IsSetKscHost = true;
	}

	void KSCServer::setPort(basar::Int32 value)
	{
		m_Port = value;
		m_IsSetPort = true;
	}

	void KSCServer::setTerminalName(basar::VarString const& value)
	{
		m_TerminalName = value;
		m_IsSetTerminalName = true;
	}

	void KSCServer::setFinishOrderType(basar::VarString const& value)
	{
		m_FinishOrderType = value;
		m_IsSetFinishOrderType = true;
	}

	basar::VarString KSCServer::getKscHost(void) const
	{
		return m_KscHost;
	}

	basar::Int32 KSCServer::getPort(void) const
	{
		return m_Port;
	}

	basar::VarString KSCServer::getTerminalName(void) const
	{
		return m_TerminalName;
	}

	basar::VarString KSCServer::getFinishOrderType(void) const
	{
		return m_FinishOrderType;
	}

	bool KSCServer::isSetKscHost(void) const
	{
		return m_IsSetKscHost;
	}

	bool KSCServer::isSetPort(void) const
	{
		return m_IsSetPort;
	}

	bool KSCServer::isSetTerminalName(void) const
	{
		return m_IsSetTerminalName;
	}

	bool KSCServer::isSetFinishOrderType(void) const
	{
		return m_IsSetFinishOrderType;
	}
}
}
