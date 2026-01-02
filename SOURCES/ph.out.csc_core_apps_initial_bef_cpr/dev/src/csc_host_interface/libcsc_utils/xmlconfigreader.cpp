#include "xmlconfigreader.h"
#include "xmlreaderexception.h"

#include <QtCore/QFile>
#include <sstream>

#include "loggerpool.h"
#include <classinfo_macros.h>

#include "general.h"
#include "informix.h"
#include "kscserver.h"
#include "smtp.h"
#include "tcaccess.h"
#include "settings.h"
#include "pxverbund.h"

namespace libcsc_utils
{

XmlConfigReader::XmlConfigReader( const basar::Int16 branchno, const basar::VarString& context ) :
		m_Logger( libcsc_utils::LoggerPool::LoggerCSC ), m_IfaceName(context), m_Branchno(branchno), m_VisitLevel(1)
{
	METHODNAME_DEF( XmlConfigReader, XmlConfigReader );
	BLOG_TRACE_METHOD( m_Logger, fun );

	// ensure interface name is written in lower letters
	m_IfaceName.lower();

	// initialize ptr
	m_ConfigGeneralPtr   = config::GeneralPtr(   new config::General() );
	m_ConfigInformixCSCPtr  = config::InformixPtr(  new config::Informix() );
	m_ConfigInformixZDPPtr  = config::InformixPtr(  new config::Informix() );
	m_ConfigKSCServerPtr = config::KSCServerPtr( new config::KSCServer() );
	m_ConfigPxVerbundPtr = config::PxVerbundPtr( new config::PxVerbund() );
	m_ConfigSmtpPtr      = config::SMTPPtr(      new config::SMTP() );
	m_ConfigTCAccessPtr  = config::TCAccessPtr(  new config::TCAccess() );
}

XmlConfigReader::~XmlConfigReader()
{
	METHODNAME_DEF( XmlConfigReader, ~XmlConfigReader );
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void XmlConfigReader::parseXml()
{
	METHODNAME_DEF( XmlConfigReader, parseXml );
	BLOG_TRACE_METHOD( m_Logger, fun );

	QFile* xmlFile = static_cast<QFile*>(m_XmlStreamReader.device());
	m_XmlStreamReader.clear();
	xmlFile->seek(0);
	m_XmlStreamReader.setDevice(xmlFile);

	m_XmlStreamReader.readNext();				// read next token
	while ( !m_XmlStreamReader.atEnd() && !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() )
		{
			if (m_XmlStreamReader.name() == "KSCRefreshSettings") {
				readKSCRefreshSettingsSection();
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		} else {
			m_XmlStreamReader.readNext();
		}
	}
}

void XmlConfigReader::readFile( const basar::VarString& fileName )
{
	METHODNAME_DEF( XmlConfigReader, readFile );
	BLOG_TRACE_METHOD( m_Logger, fun );

	QFile xmlFile( fileName.c_str() );
	if ( !xmlFile.open( QFile::ReadOnly | QFile::Text ) ) {
		std::ostringstream msg;
		msg << "Cannot read xml file " << fileName << ": " << qPrintable( xmlFile.errorString() );
		m_Logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, msg.str(), __FILE__, __LINE__ );

		throw XmlReaderException( basar::ExceptInfo(fun, msg.str(), __FILE__, __LINE__ ) );
	}

	m_XmlStreamReader.setDevice( &xmlFile );

	// three step parsing to avoid hierarchie errors (value overridden by value in lower hierarchie)
	m_VisitLevel = 1;
	parseXml();
	m_VisitLevel = 2;
	parseXml();
	m_VisitLevel = 3;
	parseXml();
	xmlFile.close();

	if ( m_XmlStreamReader.hasError() ) {
		std::ostringstream msg;
		msg << "Failed to parse file " << fileName << ": " <<
				qPrintable( m_XmlStreamReader.errorString() );

		m_Logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, msg.str(), __FILE__, __LINE__ );
		throw XmlReaderException( basar::ExceptInfo( fun, msg.str(), __FILE__, __LINE__ ) );
	} else if ( xmlFile.error() != QFile::NoError )
	{
		std::ostringstream msg;
		msg << "Cannot read file " << fileName << ": " << qPrintable(xmlFile.errorString());

		m_Logger.forcedLog( log4cplus::ERROR_LOG_LEVEL, msg.str(), __FILE__, __LINE__ );
		throw XmlReaderException( basar::ExceptInfo(fun, msg.str(), __FILE__, __LINE__ ) );
	}
}

void XmlConfigReader::readKSCRefreshSettingsSection()
{
	METHODNAME_DEF( XmlConfigReader, readKSCRefreshSettingsSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();			// jump over <KSCRefreshSettings> begin tag
	while ( !( m_XmlStreamReader.isEndElement() &&
			   m_XmlStreamReader.name() == "KSCRefreshSettings") &&
			   !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name() == "Country" ) {
				readCountrySection();
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

   if ( m_XmlStreamReader.isEndElement() )
		m_XmlStreamReader.readNext();          // jump over <KSCRefreshSettings> end tag
}

void XmlConfigReader::readCountrySection()
{
	METHODNAME_DEF( XmlConfigReader, readCountrySection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool branchFound = false;
	//read country attribute first
	basar::VarString country = m_XmlStreamReader.attributes().value("Country").toString().toLocal8Bit().constData();
	if (!country.empty())
	{
		m_ConfigGeneralPtr->setCountry(country);
	}
	else
	{
		m_XmlStreamReader.raiseError("Couldn't read attribute country of " + m_XmlStreamReader.name().toString());
	}

	m_XmlStreamReader.readNext();         // jump over <Country> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Country")
            && !m_XmlStreamReader.hasError() ) {
		if ( m_XmlStreamReader.isStartElement() ) {
			
			switch ( m_VisitLevel )
			{
			case 1:
				if ( m_XmlStreamReader.name()     == "Settings" ) {
					m_VisitLevel = 0;

					readSettingsSection();
				}
				break;

			case 2:
				if ( m_XmlStreamReader.name() == "Interfaces" ) {
					m_VisitLevel = 0;

					readInterfacesSection();
				}
				break;

			case 3:
				if ( m_XmlStreamReader.name() == "Branches" )   {
					m_VisitLevel = -1;

					branchFound = true;
					readBranchesSection();

					// finished here
				}
			default:
				break;
			}
		}

		m_XmlStreamReader.readNext();
	}

	// branches are not optional
	if ( m_VisitLevel == -1 && !branchFound && !m_XmlStreamReader.hasError() ) {
		m_XmlStreamReader.raiseError("No section \"Branches\"!");
	}

	m_XmlStreamReader.readNext();          // jump over <Country> end tag
}

void XmlConfigReader::readSettingsSection()
{
	METHODNAME_DEF( XmlConfigReader, readSettingsSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <Settings> begin tag

	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Settings")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name()        == "General" )   {
				fillGeneral();
			} else if ( m_XmlStreamReader.name() == "Informix" )  {
				fillInformix(m_ConfigInformixCSCPtr);
			} else if ( m_XmlStreamReader.name() == "ZDP" )  {
				fillInformix(m_ConfigInformixZDPPtr);
			} else if ( m_XmlStreamReader.name() == "KSCServer" ) {
				fillKSCServer();
			} else if ( m_XmlStreamReader.name() == "SMTP" )      {
				fillSmtp();
				readSmtpSection();
			} else if ( m_XmlStreamReader.name() == "TCAccess" )  {
				fillTCAccess();
			} else if ( m_XmlStreamReader.name() == "pxVerbund" )  {
				fillPxVerbund();
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

	m_XmlStreamReader.readNext();          // jump over <Settings> end tag
}

void XmlConfigReader::readInterfacesSection()
{
	METHODNAME_DEF( XmlConfigReader, readInterfacesSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <Interfaces> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Interfaces")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name()        == "Interface" )   {
				// read interface from interfaces section if InterfaceName equals application name
				if ( m_IfaceName.c_str()
						== m_XmlStreamReader.attributes().value("InterfaceName").toString() ) {
					readIfaceSection();
				} else {
					// jump over whole interface section to the next one (if any)
					while ( !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Interface") ) {
						m_XmlStreamReader.readNext();
					}
				}
			} else {
				m_XmlStreamReader.raiseError( "Unknown tag: " + m_XmlStreamReader.name().toString() );
			}
		}

		m_XmlStreamReader.readNext();
	}

	m_XmlStreamReader.readNext();          // jump over <Interfaces> end tag
}

void XmlConfigReader::readIfaceSection()
{
	METHODNAME_DEF( XmlConfigReader,  readIfaceSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <Interface> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Interface")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name()        == "Settings"  )   {
				// Interface can only contain settings section
				readSettingsSection();
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

	m_XmlStreamReader.readNext();          // jump over <Interface> end tag
}

void XmlConfigReader::readBranchesSection()
{
	METHODNAME_DEF( XmlConfigReader,  readBranchesSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <Branches> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Branches")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name()        == "Branch" )   {
				// read settings from branch section if branchno equals branchno from cmdline
				if ( m_Branchno ==  m_XmlStreamReader.attributes().value("BranchNo").toString().toInt() ) {
					// Branch can only contain settings section
					readBranchSection();
				} else {
					// jump over whole branch section to the next one (if any)
					while ( !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Branch") ) {
						m_XmlStreamReader.readNext();
					}
				}
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

	m_XmlStreamReader.readNext();          // jump over <Branches> end tag
}

void XmlConfigReader::readBranchSection()
{
	METHODNAME_DEF( XmlConfigReader,  readBranchSection );
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <Branch> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "Branch")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			if ( m_XmlStreamReader.name()        == "Settings"  )   {
				// Interface can only contain settings section
				readSettingsSection();
			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

	m_XmlStreamReader.readNext();          // jump over <Branch> end tag
}

void XmlConfigReader::readSmtpSection()
{
	METHODNAME_DEF( XmlConfigReader,  readSmtpSection);
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_XmlStreamReader.readNext();         // jump over <SMTP> begin tag
	while (    !(m_XmlStreamReader.isEndElement() && m_XmlStreamReader.name() == "SMTP")
			&& !m_XmlStreamReader.hasError() ) {

		if ( m_XmlStreamReader.isStartElement() ) {
			QXmlStreamAttributes attributes  = m_XmlStreamReader.attributes();
			if ( m_XmlStreamReader.name()        == "Information" )   {
				basar::VarString info = attributes.value("eMail").toString().toLocal8Bit().constData();
				if ( !info.empty() )
					m_ConfigSmtpPtr->setSmtpTypeInformation(info);

			} else if ( m_XmlStreamReader.name() == "Warnings" )      {
				basar::VarString warn = attributes.value("eMail").toString().toLocal8Bit().constData();
				if ( !warn.empty() )
					m_ConfigSmtpPtr->setSmtpTypeWarnings(warn);

			} else if ( m_XmlStreamReader.name() == "Errors" )        {
				basar::VarString err = attributes.value("eMail").toString().toLocal8Bit().constData();
				if ( !err.empty() )
					m_ConfigSmtpPtr->setSmtpTypeErrors(err);

			} else {
				m_XmlStreamReader.raiseError("Unknown tag: " + m_XmlStreamReader.name().toString());
			}
		}

		m_XmlStreamReader.readNext();
	}

	//m_XmlStreamReader.readNext();          // jump over <SMTP> end tag
}

void XmlConfigReader::fillGeneral()
{
	QXmlStreamAttributes attributes = m_XmlStreamReader.attributes();
	bool ok = false, maxselectOk = false;
	int pollInterval          = attributes.value("PollInterval").toString().toInt(&ok);
	basar::VarString logLevel = attributes.value("LogLevel").toString().toLocal8Bit().constData();
	int       maxSelectOrders = attributes.value("MaxSelectOrders").toString().toInt(&maxselectOk);

	QStringRef test           = attributes.value("Test");
	if ( test == "true" )
		m_ConfigGeneralPtr->setTest(true);
	else if (test == "false")
		m_ConfigGeneralPtr->setTest(false);
	else if (! test.isEmpty() )
		m_XmlStreamReader.raiseError("Settings section: Test argument can either be true or false!");

	// check mandatory values
	if ( !ok ) {
		//m_XmlStreamReader.raiseError("Settings section: PollInterval invalid or unset!");
	} else {
			m_ConfigGeneralPtr->setPollInterval(pollInterval);
	}

	if ( logLevel.empty() ) {
		//m_XmlStreamReader.raiseError("Settings section: Loglevel invalid or unset!");
	} else {
		m_ConfigGeneralPtr->setLogLevel(logLevel);
	}

	if ( !maxselectOk ) {
		//m_XmlStreamReader.raiseError("Settings section: MaxSelectOrders invalid!");
	} else {
		m_ConfigGeneralPtr->setMaxSelectOrders(maxSelectOrders);
	}

	test = attributes.value("BulkInsert");
	if ( test == "true" )
		m_ConfigGeneralPtr->setBulkInsert(true);
	else if (test == "false")
		m_ConfigGeneralPtr->setBulkInsert(false);
	else if (! test.isEmpty() )
		m_XmlStreamReader.raiseError("Settings section: BulkInsert argument can either be true or false!");
}

void XmlConfigReader::fillInformix(config::InformixPtr ifxptr)
{
	QXmlStreamAttributes attributes = m_XmlStreamReader.attributes();
	bool retriesOk = false, waitsOk = false;
	basar::VarString serviceName   = attributes.value("IfxServiceName").toString().toLocal8Bit().constData();
	basar::VarString host          = attributes.value("IfxHost").toString().toLocal8Bit().constData();
	basar::VarString database      = attributes.value("IfxDataBase").toString().toLocal8Bit().constData();
	int connectionRetries          = attributes.value("ConnectionRetries").toString().toInt(&retriesOk);
	int connectionWaitBeforeRetry  = attributes.value("ConnectionWaitBeforeRetry").toString().toInt(&waitsOk);
	QStringRef activate            = attributes.value("Activate");

	if ( !retriesOk ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionRetries invalid!");
	} else {
		ifxptr->setConnectionRetries(connectionRetries);
	}

	if ( !waitsOk ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionWaitBeforeRetry invalid!");
	} else {
		ifxptr->setConnWaitBeforeRetry(connectionWaitBeforeRetry);
	}

	if ( !database.empty() )
		ifxptr->setIfxDataBase(database);

	if ( !host.empty() )
		ifxptr->setIfxHost(host);

	if ( !serviceName.empty() )
		ifxptr->setIfxServiceName(serviceName);

	if ( activate == "false" )
		ifxptr->setActivate(false);
}

void XmlConfigReader::fillKSCServer()
{
	QXmlStreamAttributes attributes = m_XmlStreamReader.attributes();
	int port                       = attributes.value("Port").toString().toInt();
	basar::VarString host          = attributes.value("KSCHost").toString().toLocal8Bit().constData();
	basar::VarString fOrderType    = attributes.value("FinishOrderType").toString().toLocal8Bit().constData();
	basar::VarString termName      = attributes.value("TerminalName").toString().toLocal8Bit().constData();

	if ( 0 == port ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionWaitBeforeRetry invalid!");
	} else {
		m_ConfigKSCServerPtr->setPort(port);
	}

	if ( !host.empty() )
		m_ConfigKSCServerPtr->setKscHost(host);

	if ( !fOrderType.empty() )
		m_ConfigKSCServerPtr->setFinishOrderType(fOrderType);

	if ( !termName.empty() )
		m_ConfigKSCServerPtr->setTerminalName(termName);
}

void XmlConfigReader::fillSmtp()
{
	QXmlStreamAttributes attributes = m_XmlStreamReader.attributes();
	int port                       = attributes.value("Port").toString().toInt();
	basar::VarString host          = attributes.value("Host").toString().toLocal8Bit().constData();
	basar::VarString sendFrom      = attributes.value("SendMailFrom").toString().toLocal8Bit().constData();
	basar::VarString username      = attributes.value("Username").toString().toLocal8Bit().constData();
	basar::VarString password      = attributes.value("Password").toString().toLocal8Bit().constData();

	if ( 0 == port ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionWaitBeforeRetry invalid!");
	} else {
		m_ConfigSmtpPtr->setPort(port);
	}

	if ( !host.empty() )
		m_ConfigSmtpPtr->setHost(host);

	if ( !sendFrom.empty() )
		m_ConfigSmtpPtr->setSendMailFrom(sendFrom);

	if ( !username.empty() )
		m_ConfigSmtpPtr->setUsername(username);

	if ( !password.empty() )
		m_ConfigSmtpPtr->setPassword(password);
}

void XmlConfigReader::fillTCAccess()
{
	QXmlStreamAttributes attributes = m_XmlStreamReader.attributes();
	bool retriesOk = false, waitsOk = false, commareaOk = false;
	int port                       = attributes.value("Port").toString().toInt();
	basar::VarString transaction   = attributes.value("TCATransaction").toString().toLocal8Bit().constData();
	basar::VarString host          = attributes.value("TCAHost").toString().toLocal8Bit().constData();
	basar::VarString ipAddr        = attributes.value("IPAddress").toString().toLocal8Bit().constData();
	basar::VarString username      = attributes.value("Username").toString().toLocal8Bit().constData();
	basar::VarString password      = attributes.value("Password").toString().toLocal8Bit().constData();

	basar::VarString cicsLinkProg  = attributes.value("CICSLinkProgram").toString().toLocal8Bit().constData();
	int commareaLen                = attributes.value("CommareaLength").toString().toInt(&commareaOk);
	int connRetries                = attributes.value("ConnectionRetries").toString().toInt(&retriesOk);
	int connectionWaitBeforeRetry  = attributes.value("ConnectionWaitBeforeRetry").toString().toInt(&waitsOk);
	QStringRef activate            = attributes.value("Activate");

	if ( 0 == port ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionWaitBeforeRetry invalid!");
	} else {
		m_ConfigTCAccessPtr->setPort(port);
	}

	if ( !transaction.empty() )
		m_ConfigTCAccessPtr->setTcaTransaction(transaction);

	if ( !host.empty() )
		m_ConfigTCAccessPtr->setTcaHost(host);

	if ( !ipAddr.empty() )
		m_ConfigTCAccessPtr->setIpAddress(ipAddr);

	if ( !username.empty() )
		m_ConfigTCAccessPtr->setUsername(username);

	if ( !password.empty() )
		m_ConfigTCAccessPtr->setPassword(password);

	if ( !cicsLinkProg.empty() )
		m_ConfigTCAccessPtr->setCicsLinkProgram(cicsLinkProg);

	if ( !commareaOk ) {
		//m_XmlStreamReader.raiseError("Settings section: CommareaLength invalid!");
	} else {
		m_ConfigTCAccessPtr->setComareaLength(commareaLen);
	}

	if ( !retriesOk ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionRetries invalid!");
	} else {
		m_ConfigTCAccessPtr->setConnectionRetries(connRetries);
	}

	if ( !waitsOk ) {
		//m_XmlStreamReader.raiseError("Settings section: ConnectionWaitBeforeRetry invalid!");
	} else {
		m_ConfigTCAccessPtr->setConnWaitBeforeRetry(connectionWaitBeforeRetry);
	}

	if ( activate == "false" )
		m_ConfigTCAccessPtr->setActivate(false);
}

void XmlConfigReader::fillPxVerbund()
{
	QXmlStreamAttributes attributes  = m_XmlStreamReader.attributes();
	bool modeOk = false, deviceOk = false;
	basar::VarString messageFile     = attributes.value("MessageFile").toString().toLocal8Bit().constData();
	basar::VarString logFile         = attributes.value("LogFile").toString().toLocal8Bit().constData();
	basar::VarString systemLogFile   = attributes.value("SystemLogFile").toString().toLocal8Bit().constData();
	int              logMode         = attributes.value("LogMode").toString().toInt(&modeOk);
	basar::VarString computer        = attributes.value("Computer").toString().toLocal8Bit().constData();
	basar::VarString dataSource      = attributes.value("DataSource").toString().toLocal8Bit().constData();
	basar::VarString deviceName      = attributes.value("DeviceName").toString().toLocal8Bit().constData();
	int              deviceType      = attributes.value("DeviceType").toString().toInt(&deviceOk);

	if ( !messageFile.empty() )
		m_ConfigPxVerbundPtr->setMessageFile(messageFile);

	if ( !logFile.empty() )
		m_ConfigPxVerbundPtr->setLogFile(logFile);

	if ( !systemLogFile.empty() )
		m_ConfigPxVerbundPtr->setSystemLogFile(systemLogFile);

	if ( !modeOk ) {
		//m_XmlStreamReader.raiseError("Settings section: logMode invalid!");
	} else {
		m_ConfigPxVerbundPtr->setLogMode(logMode);
	}

	if ( !computer.empty() )
		m_ConfigPxVerbundPtr->setComputer(computer);

	if ( !dataSource.empty() )
		m_ConfigPxVerbundPtr->setDataSource(dataSource);

	if ( !deviceOk ) {
		//m_XmlStreamReader.raiseError("Settings section: DeviceType invalid!");
	} else {
		m_ConfigPxVerbundPtr->setDeviceType(deviceType);
	}

	if ( !deviceName.empty() )
		m_ConfigPxVerbundPtr->setDeviceName(deviceName);
}

const config::SettingsPtr   XmlConfigReader::getSettings()   const
{
	METHODNAME_DEF( XmlConfigReader,  getSettings );
	BLOG_TRACE_METHOD( m_Logger, fun );

	return config::SettingsPtr( new config::Settings ( m_ConfigGeneralPtr, m_ConfigInformixCSCPtr, m_ConfigInformixZDPPtr,
			m_ConfigKSCServerPtr, m_ConfigSmtpPtr, m_ConfigTCAccessPtr, m_ConfigPxVerbundPtr ) );
}

} /* namespace libcsc_utils */
