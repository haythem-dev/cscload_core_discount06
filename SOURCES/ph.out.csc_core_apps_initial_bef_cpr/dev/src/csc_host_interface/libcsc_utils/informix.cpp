//-------------------------------------------------------------------------------------------------------------------//
/*! \file		informix.cpp
*  \brief		representation of config informix
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "informix.h"

namespace libcsc_utils
{
namespace config
{
	Informix::Informix(void)
	{
		m_IfxDataBase = "";
		m_IfxHost = "";
		m_IfxServiceName = "";

		// default values
		m_ConnectionRetries   = 5;
		m_ConnWaitBeforeRetry = 5000;
		m_Activate = true;

		m_IsSetIfxHost = false;
		m_IsSetIfxDataBase = false;
		m_IsSetIfxServiceName = false;
		m_IsSetConnectionRetries = false;
		m_IsSetConnWaitBeforeRetry = false;
		m_IsSetActivate = false;
	}

	Informix::Informix(basar::VarString const& ifxHost, basar::VarString const& ifxDataBase, basar::VarString const& ifxServiceName)
	{
		m_IfxDataBase = ifxDataBase;
		m_IfxHost = ifxHost;
		m_IfxServiceName = ifxServiceName;
		m_Activate = true;

		m_IsSetIfxHost = true;
		m_IsSetIfxDataBase = true;
		m_IsSetIfxServiceName = true;
		m_IsSetActivate = false;
	}

	Informix::~Informix(void)
	{
	}

	void Informix::setIfxHost(basar::VarString const& value) 
	{
		m_IfxHost = value;
		m_IsSetIfxHost = true;
	}

	void Informix::setIfxDataBase(basar::VarString const& value)  
	{
		m_IfxDataBase = value;
		m_IsSetIfxDataBase = true;
	}

	void Informix::setIfxServiceName(basar::VarString const& value) 
	{
		m_IfxServiceName = value;
		m_IsSetIfxServiceName = true;
	}
	
	void Informix::setConnectionRetries (basar::Int32 value)
	{
		m_ConnectionRetries = value;
		m_IsSetConnectionRetries = true;
	}

	void Informix::setConnWaitBeforeRetry  (basar::Int32 value)
	{
		m_ConnWaitBeforeRetry = value;
		m_IsSetConnWaitBeforeRetry = true;
	}

	void Informix::setActivate(bool value)
	{
		m_Activate = value;
		m_IsSetActivate = true;
	}

	basar::VarString Informix::getIfxHost(void) const 
	{
		return m_IfxHost;
	}

	basar::VarString Informix::getIfxDataBase(void) const 
	{
		return m_IfxDataBase;
	}

	basar::VarString Informix::getIfxServiceName(void) const 
	{
		return m_IfxServiceName;
	}

	basar::Int32 Informix::getConnectionRetries (void) const
	{
		return m_ConnectionRetries;
	}

	basar::Int32 Informix::getConnWaitBeforeRetry(void) const
	{
		return m_ConnWaitBeforeRetry;
	}

	bool Informix::getActivate(void) const
	{
		return m_Activate;
	}

	bool Informix::isSetIfxHost(void) const
	{
		return m_IsSetIfxHost;
	}

	bool Informix::isSetIfxDataBase(void) const
	{
		return m_IsSetIfxDataBase;
	}

	bool Informix::isSetIfxServiceName(void) const
	{
		return m_IsSetIfxServiceName;
	}

	bool  Informix::isSetConnectionRetries (void) const
	{
		return m_IsSetConnectionRetries;
	}

	bool Informix::isSetConnWaitBeforeRetry (void) const
	{
		return m_IsSetConnWaitBeforeRetry;
	}

	bool Informix::isSetActivate(void) const
	{
		return m_IsSetActivate;
	}
}
}
