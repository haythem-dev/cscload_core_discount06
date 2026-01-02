//-------------------------------------------------------------------------------------------------------------------//
/*! \file		pxverbund.cpp
*  \brief		representation of config pxverbund
*  \author
*  \date
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "pxverbund.h"

namespace libcsc_utils
{
	namespace config
	{
		PxVerbund::PxVerbund(void) : 			
	m_MessageFile(""), m_LogFile(""), m_SystemLogFile(""), m_LogMode(0), m_Computer(""), m_DataSource(""), 
		m_DeviceName(""), m_DeviceType(0), m_IsSetMessageFile(false), m_IsSetLogFile(false), m_IsSetSystemLogFile(false),
		m_IsSetLogMode(false), m_IsSetComputer(false), m_IsSetDataSource(false), m_IsSetDeviceName(false), 
		m_IsSetDeviceType(false)
	{
	}

	PxVerbund::PxVerbund(const basar::VarString& messageFile, const basar::VarString& logFile, 
		const basar::VarString& systemLogFile, basar::Int32 logMode, const basar::VarString& computer, 
		const basar::VarString& dataSource, const basar::VarString& deviceName, basar::Int32 deviceType) :
	m_MessageFile(messageFile), m_LogFile(logFile), m_SystemLogFile(systemLogFile), m_LogMode(logMode), 
		m_Computer(computer), m_DataSource(dataSource), m_DeviceName(deviceName), m_DeviceType(deviceType), 
		m_IsSetMessageFile(true), m_IsSetLogFile(true), m_IsSetSystemLogFile(true),
		m_IsSetLogMode(true), m_IsSetComputer(true), m_IsSetDataSource(true), m_IsSetDeviceName(true), 
		m_IsSetDeviceType(true)
	{
	}

	PxVerbund::~PxVerbund(void)
	{
	}

	void PxVerbund::setMessageFile (const basar::VarString& messageFile)
	{
		m_MessageFile = messageFile;
		m_IsSetMessageFile = true;
	}

	void PxVerbund::setLogFile (const basar::VarString& logFile)
	{
		m_LogFile = logFile;
		m_IsSetLogFile = true;
	}

	void PxVerbund::setSystemLogFile (const basar::VarString& systemLogFile)
	{
		m_SystemLogFile = systemLogFile;
		m_IsSetSystemLogFile = true;
	}

	void PxVerbund::setLogMode (basar::Int32 logMode)
	{
		m_LogMode = logMode;
		m_IsSetLogMode = true;
	}

	void PxVerbund::setComputer (const basar::VarString& computer)
	{
		m_Computer = computer;
		m_IsSetComputer = true;
	}

	void PxVerbund::setDataSource (const basar::VarString& dataSource)
	{
		m_DataSource = dataSource;
		m_IsSetDataSource = true;
	}

	void PxVerbund::setDeviceName (const basar::VarString& deviceName)
	{
		m_DeviceName = deviceName;
		m_IsSetDeviceName = true;
	}

	void PxVerbund::setDeviceType (basar::Int32 deviceType)
	{
		m_DeviceType = deviceType;
		m_IsSetDeviceType = true;
	}

	// Getter
	const basar::VarString&	PxVerbund::getMessageFile          (void) const
	{
		return m_MessageFile;
	}

	const basar::VarString&	PxVerbund::getLogFile				(void) const
	{
		return m_LogFile;
	}

	const basar::VarString&	PxVerbund::getSystemLogFile		(void) const
	{
		return m_SystemLogFile;
	}

	basar::Int32		PxVerbund::getLogMode				(void) const
	{
		return m_LogMode;
	}

	const basar::VarString&	PxVerbund::getComputer				(void) const
	{
		return m_Computer;
	}

	const basar::VarString&	PxVerbund::getDataSource			(void) const
	{
		return m_DataSource;
	}

	const basar::VarString&	PxVerbund::getDeviceName			(void) const
	{
		return m_DeviceName;
	}

	basar::Int32  	PxVerbund::getDeviceType			(void) const
	{
		return m_DeviceType;
	}

	// 
	bool PxVerbund::isSetMessageFile(void) const
	{
		return m_IsSetMessageFile;
	}

	bool PxVerbund::isSetLogFile(void) const
	{
		return m_IsSetLogFile;
	}

	bool PxVerbund::isSetSystemLogFile(void) const
	{
		return m_IsSetSystemLogFile;
	}

	bool PxVerbund::isSetLogMode(void) const
	{
		return m_IsSetLogMode;
	}

	bool PxVerbund::isSetComputer(void) const
	{
		return m_IsSetComputer;
	}

	bool PxVerbund::isSetDataSource(void) const
	{
		return m_IsSetDataSource;
	}

	bool PxVerbund::isSetDeviceName(void) const
	{
		return m_IsSetDeviceName;
	}

	bool PxVerbund::isSetDeviceType(void) const
	{
		return m_IsSetDeviceType;
	}

	}
}
