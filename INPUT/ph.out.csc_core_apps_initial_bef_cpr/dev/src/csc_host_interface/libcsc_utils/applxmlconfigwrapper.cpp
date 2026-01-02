//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      wrapper for xml config
 *  \author     
 *  \date       
 *  \version    
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <libbasardbsql_databaseinfo.h>


#include "xmlconfigreader.h"

#include "iapplconfiguration.h"

#include "config_definitions.h"
#include "settings.h"
#include "general.h"
#include "informix.h"
#include "kscserver.h"
#include "smtp.h"
#include "tcaccess.h"
#include "pxverbund.h"

#include "applxmlconfigwrapper.h"

#include "configdatainconsistantexception.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

    ApplXMLConfigWrapper::ApplXMLConfigWrapper(const basar::Int16 branchno, const basar::VarString& context, const basar::VarString& xmlFileName) 
		: m_Branchno(branchno)
		, m_Context(context)
		, m_XmlFileName(xmlFileName)
		, m_OrderFilter( "" )
		, m_XmlFileRead(false)
		, m_IsTestingSet(false)
		, m_IsNoMailSet(false)
		, m_ExtendedLogging(false)
	{
	}

	void ApplXMLConfigWrapper::init()
	{
		m_XmlConfigReader = XmlConfigReaderPtr(new XmlConfigReader(m_Branchno, m_Context));
		
		readXmlFile();

        checkConfigData();
		
		m_IFXConfiguration.setInfxConcurrent(
			m_XmlConfigReader->getSettings()->getInformix()->getIfxHost(),
			m_XmlConfigReader->getSettings()->getInformix()->getIfxDataBase() );

		basar::VarString port;
		port.format("%d", m_XmlConfigReader->getSettings()->getTCAccess()->getPort());

		m_TCAConfiguration.setCICS(	m_XmlConfigReader->getSettings()->getTCAccess()->getTcaHost()
									, m_XmlConfigReader->getSettings()->getTCAccess()->getIpAddress()
									, port
									, m_XmlConfigReader->getSettings()->getTCAccess()->getTcaTransaction() 
									, m_XmlConfigReader->getSettings()->getTCAccess()->getUsername()
									, m_XmlConfigReader->getSettings()->getTCAccess()->getPassword() );

	}

    void ApplXMLConfigWrapper::checkConfigData()
    {        
        basar::VarString pxVBDataSource = m_XmlConfigReader->getSettings()->getPxVerbund()->getDataSource();
        basar::VarString ifxDataBase = m_XmlConfigReader->getSettings()->getInformix()->getIfxDataBase();
        
        if( ifxDataBase != pxVBDataSource.substr(0, ifxDataBase.length() ) )
        {
            throw ConfigDataInconsistantException(basar::ExceptInfo("ApplXMLConfigWrapper::checkConfigData()", "Informix-Database and pxVerbund-Database differ", __FILE__, __LINE__ ) );
        }


    }

	void ApplXMLConfigWrapper::readXmlFile()
	{
		m_XmlConfigReader->readFile(m_XmlFileName);

		m_XmlFileRead = true;
	}

	basar::VarString ApplXMLConfigWrapper::getKSCHost() const
	{
		return m_XmlConfigReader->getSettings()->getKSCServer()->getKscHost();
	}

	basar::VarString ApplXMLConfigWrapper::getFinishOrderType() const
	{
		return m_XmlConfigReader->getSettings()->getKSCServer()->getFinishOrderType();
	}

	basar::VarString ApplXMLConfigWrapper::getTerminalName() const
	{
		return m_XmlConfigReader->getSettings()->getKSCServer()->getTerminalName();
	}
	
	basar::Int16 ApplXMLConfigWrapper::getKSCServerPort() const
	{
		return static_cast<basar::Int16>(m_XmlConfigReader->getSettings()->getKSCServer()->getPort());
	}

	const basar::db::sql::DatabaseInfo&	ApplXMLConfigWrapper::getIFXConfiguration()
	{		
		return m_IFXConfiguration;
	}


	basar::Int32	ApplXMLConfigWrapper::getIFXConnectionRetries()
	{
		return m_XmlConfigReader->getSettings()->getInformix()->getConnectionRetries();
	}

	basar::Int32	ApplXMLConfigWrapper::getIFXConnectionWaitBeforeRetry()
	{
		return m_XmlConfigReader->getSettings()->getInformix()->getConnWaitBeforeRetry();
	}

	const basar::db::sql::DatabaseInfo&	ApplXMLConfigWrapper::getTCAConfiguration()
	{
		return m_TCAConfiguration;
	}

	basar::Int32 ApplXMLConfigWrapper::getTCAConnectionRetries()
	{
		return m_XmlConfigReader->getSettings()->getTCAccess()->getConnectionRetries();
	}

	basar::Int32 ApplXMLConfigWrapper::getTCAConnectionWaitBeforeRetry()
	{
		return m_XmlConfigReader->getSettings()->getTCAccess()->getConnWaitBeforeRetry();
	}

	bool ApplXMLConfigWrapper::isTCAActivated() const
	{
		return m_XmlConfigReader->getSettings()->getTCAccess()->getActivate();
	}

	basar::VarString	ApplXMLConfigWrapper::getMessageFile() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getMessageFile();
	}

	basar::VarString ApplXMLConfigWrapper::getSystemLogFile() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getSystemLogFile();
	}

	basar::Int32 ApplXMLConfigWrapper::getLogMode() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getLogMode();
	}

	basar::VarString ApplXMLConfigWrapper::getComputer() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getComputer();
	}

	basar::VarString ApplXMLConfigWrapper::getLogFile() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getLogFile();
	}

	basar::VarString ApplXMLConfigWrapper::getDeviceName() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getDeviceName();
	}

	basar::Int32 ApplXMLConfigWrapper::getDeviceType() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getDeviceType();
	}

	basar::VarString ApplXMLConfigWrapper::getDataSource() const
	{
		return m_XmlConfigReader->getSettings()->getPxVerbund()->getDataSource();
	}

	basar::VarString ApplXMLConfigWrapper::getCountryCode() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->getCountry();
	}

	basar::Int16	ApplXMLConfigWrapper::getBranchNo() const
	{
		return m_Branchno;
	}

	basar::Int32 ApplXMLConfigWrapper::getPollingInterval() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->getPollInterval();
	}

	basar::Int32 ApplXMLConfigWrapper::getMaxSelectOrders() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->getMaxSelectOrders();
	}

	bool ApplXMLConfigWrapper::getBulkInsert() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->getBulkInsert();
	}

	bool ApplXMLConfigWrapper::isBulkInsertSet() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->isSetBulkInsert();
	}

	basar::VarString ApplXMLConfigWrapper::getSmtpHost() const
	{
		return m_XmlConfigReader->getSettings()->getSMTP()->getHost();
	}

	basar::Int16 ApplXMLConfigWrapper::getSmtpPort() const
	{
		return static_cast<basar::Int16>(m_XmlConfigReader->getSettings()->getSMTP()->getPort());
	}

	basar::VarString ApplXMLConfigWrapper::getSmtpFromAddress() const
	{
		return m_XmlConfigReader->getSettings()->getSMTP()->getSendMailFrom();
	}

	basar::VarString ApplXMLConfigWrapper::getInformationSmtpRecipients() const
	{
		return m_XmlConfigReader->getSettings()->getSMTP()->getSmtpTypeInformation();
	}
	basar::VarString ApplXMLConfigWrapper::getWarningSmtpRecipients() const
	{
		return  m_XmlConfigReader->getSettings()->getSMTP()->getSmtpTypeWarnings();
	}
	basar::VarString ApplXMLConfigWrapper::getErrorSmtpRecipients() const
	{
		return  m_XmlConfigReader->getSettings()->getSMTP()->getSmtpTypeErrors();
	}

	basar::VarString ApplXMLConfigWrapper::getMailThreshold() const
	{
		return m_XmlConfigReader->getSettings()->getGeneral()->getLogLevel();
	}

	basar::VarString ApplXMLConfigWrapper::getApplicationName() const
	{
		return m_Context;
	}

	basar::VarString ApplXMLConfigWrapper::getZDPHost() const
	{
		return m_XmlConfigReader->getSettings()->getInformixZDP()->getIfxHost();
	}

	basar::VarString ApplXMLConfigWrapper::getZDPDatabase() const
	{
		return m_XmlConfigReader->getSettings()->getInformixZDP()->getIfxDataBase();
	}

	bool ApplXMLConfigWrapper::isZDPActivated() const
	{
		return (
			m_XmlConfigReader->getSettings()->getInformixZDP()->getActivate() &&
			!getZDPHost().empty() &&
			!getZDPDatabase().empty()
		);
	}

    bool ApplXMLConfigWrapper::isTestingSet() const
    {
        return m_IsTestingSet;
    }

    bool ApplXMLConfigWrapper::isNoMailSet() const
    {
        return m_IsNoMailSet;
    }

	bool ApplXMLConfigWrapper::isExtendedLoggingSet() const
	{
		return m_ExtendedLogging;
	}

    void ApplXMLConfigWrapper::setTesting(bool isTesting)
    {
        m_IsTestingSet = isTesting;
    }

    void ApplXMLConfigWrapper::setNoMail(bool isNoMail)
    {
        m_IsNoMailSet = isNoMail;
    }

	basar::VarString ApplXMLConfigWrapper::getOrderFilter() const
	{
		return m_OrderFilter;
	}

	void ApplXMLConfigWrapper::setOrderFilter(const basar::VarString orderfilter)
	{
		m_OrderFilter = orderfilter;
	}	

	void ApplXMLConfigWrapper::setExtendedLogging( bool extlogging )
	{
		m_ExtendedLogging = extlogging;
	}

	//iloggable
	basar::VarString ApplXMLConfigWrapper::getLogMessage() const
	{
		basar::VarString logMessage;

		logMessage.format
		(
			"\nConfig for %s (country %s, branchno %d, pollinterval %d)\n"
			"Informix database CSC: %s@%s\n"
			"Informix retry count/wait CSC: %d/%d\n"
			"Informix database ZDP: %s@%s, activated %s \n"
			"TCAccess (host, ip, port, starttransaction): %s, %s, %s, %s\n"
			"TCAccess retry count/wait: %d/%d\n"
			"TCAccess activated: %s\n"
			"SMTP server/port: %s:%d\n"
			"KSC host/port: %s:%d\n"
			"Terminal Name: %s\n"
			"Finish order type: %s\n"
			"pxVerbund settings:\n"
			"computer: %s\n"
			"data source: %s\n"
			"Logmode: %d\n"
			"Logfiles (Log ~ Systemlog ~ Message): %s ~ %s ~ %s\n"
			"Device Type / Name: %d / %s\n"
            "Misc Flags: testing %d, nomail %d, orderfilter %s \n"
			"MaxSelectOrders: %d\n"
			"BulkInsert: %s\n",
			m_Context.c_str(), m_XmlConfigReader->getSettings()->getGeneral()->getCountry().c_str(), m_Branchno, m_XmlConfigReader->getSettings()->getGeneral()->getPollInterval(),
			m_IFXConfiguration.database.c_str(), m_IFXConfiguration.dbServer.c_str(),
			m_XmlConfigReader->getSettings()->getInformix()->getConnectionRetries(), m_XmlConfigReader->getSettings()->getInformix()->getConnWaitBeforeRetry(),
			getZDPDatabase().c_str(), getZDPHost().c_str(), isZDPActivated() ? "true" : "false",
			m_TCAConfiguration.dbServer.c_str(), m_TCAConfiguration.cicsCustom.ipAddr.c_str(), m_TCAConfiguration.cicsCustom.port.c_str(), m_TCAConfiguration.cicsCustom.startTransact.c_str(),
			m_XmlConfigReader->getSettings()->getTCAccess()->getConnectionRetries(), m_XmlConfigReader->getSettings()->getTCAccess()->getConnWaitBeforeRetry(),
			isTCAActivated() ? "true" : "false",
			m_XmlConfigReader->getSettings()->getSMTP()->getHost().c_str(), m_XmlConfigReader->getSettings()->getSMTP()->getPort(),
			m_XmlConfigReader->getSettings()->getKSCServer()->getKscHost().c_str(), m_XmlConfigReader->getSettings()->getKSCServer()->getPort(),
			m_XmlConfigReader->getSettings()->getKSCServer()->getTerminalName().c_str(),
			m_XmlConfigReader->getSettings()->getKSCServer()->getFinishOrderType().c_str(),
			m_XmlConfigReader->getSettings()->getPxVerbund()->getComputer().c_str(),
			m_XmlConfigReader->getSettings()->getPxVerbund()->getDataSource().c_str(),
			m_XmlConfigReader->getSettings()->getPxVerbund()->getLogMode(),
			getLogFile().c_str(), getSystemLogFile().c_str(), getMessageFile().c_str(),
			getDeviceType(), getDeviceName().c_str(),
			isTestingSet(), isNoMailSet(), getOrderFilter().c_str(),
			getMaxSelectOrders(),
			getBulkInsert() ? "true" : "false"

		);

		return logMessage;

	}

}//namespace util

