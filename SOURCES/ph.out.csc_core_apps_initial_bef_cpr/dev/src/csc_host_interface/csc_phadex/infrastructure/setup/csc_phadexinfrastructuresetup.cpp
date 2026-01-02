#include "csc_phadexinfrastructuresetup.h"
#include "infrastructure/setup/icsc_phadexlogingetter.h"
#include "infrastructure/cmdline/csc_phadexcmdlineevaluator.h"
#include "infrastructure/cmdline/csc_phadexcmdlineevaluatorptr.h"
#include "infrastructure/config/phadexxmlconfigreader.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <exceptions/invalidparameterexception.h>
#include <libbasardbaspect.h>

#include <libutil/applcomponent.h>
#include <libutil/util.h>
#include <libutil/log4cplus.h>
//#include <libutil/dbconnection.h>
#include <libutil/login.h>
#include <libutil/exception.h>
#include <libutil/login.h>
#include <libutil/parameter.h>
#include <libutil/languagefileloader.h>

#include <libbasarcmnutil.h>

namespace csc_phadex
{
namespace infrastructure
{
namespace setup
{
CscPhadexInfrastructureSetup::CscPhadexInfrastructureSetup()
: InfrastructureSetupBase( LoggerPool::getLoggerCsc_phadex() )
{
	METHODNAME_DEF( CscPhadexInfrastructureSetup, CscPhadexInfrastructureSetup )
	BLOG_TRACE_METHOD( getLogger(), fun );
}

CscPhadexInfrastructureSetup::~CscPhadexInfrastructureSetup()
{
	METHODNAME_DEF( CscPhadexInfrastructureSetup, ~CscPhadexInfrastructureSetup)
	BLOG_TRACE_METHOD( getLogger(), fun );
}

void CscPhadexInfrastructureSetup::doInit()
{
    evaluateCmdline();
	readXMLConfig();
    loadTranslators();

	injectDBConnection( libutil::infrastructure::db::dbConnection::IDBConnectionPtr(
		new libutil::infrastructure::db::dbConnection::DBIfxConnection( getDBServerInfo() )
			)  );

	establishDBConnection();
	establishTCAConnection();
}

const libutil::infrastructure::db::dbConnection::DBServerInfo CscPhadexInfrastructureSetup::getDBServerInfo() const
{
	return libutil::infrastructure::db::dbConnection::DBServerInfo( m_Config.ifxDatabase, m_Config.ifxHost );
}

basar::db::aspect::ConnectionRef CscPhadexInfrastructureSetup::getCICSConnection()
{
	return m_CICSConnection;
}

libutil::infrastructure::db::dbConnection::IDBConnectionPtr CscPhadexInfrastructureSetup::getDBConnection()
{
	return InfrastructureSetupBase::getDBConnection();
}

const PhadexConfigStruct & CscPhadexInfrastructureSetup::getConfig() const
{
	return m_Config;
}

void CscPhadexInfrastructureSetup::readXMLConfig()
{
	METHODNAME_DEF( CscPhadexInfrastructureSetup, ~readXMLConfig )
	BLOG_TRACE_METHOD( getLogger(), fun );

    // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
    boost::shared_ptr<csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator const> csc_phadexCmdLine
    ( 
        boost::static_pointer_cast<csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator>( getCmdLineEvaluator()) 
    );
	const csc_phadex::infrastructure::cmdLine::AppArgs & appArgs = csc_phadexCmdLine->getAppArgs();

	csc_phadex::infrastructure::PhadexXMLConfigReader xml;
	xml.readConfig( appArgs.configFile );
	
	if( getLogger().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		xml.toStream( ss );
		getLogger().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	try
	{
		m_Config = xml.getBranchConfig( appArgs.branchNo );

		if( getLogger().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
		{
			std::stringstream ss;
			ss << m_Config;
			getLogger().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
		}
	}
	catch( const libcsc::exceptions::InvalidParameterException & e )
	{
		BLOG_ERROR( getLogger(), e.what().c_str() );
		throw;
	}
}
    	
//void CscPhadexInfrastructureSetup::prepareLogin()
//{
//    // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
//    boost::shared_ptr<csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator const> csc_phadexCmdLine
//    ( 
//        boost::static_pointer_cast<csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator>( getCmdLineEvaluator()) 
//    );
//
//    const csc_phadex::infrastructure::cmdLine::AppArgs& appArgs = csc_phadexCmdLine->getAppArgs();
//    const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, csc_phadex::getCsc_phadexName(), appArgs.m_BranchNo );
//                
//    // BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
//    // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
//    injectLogin( m_CscPhadexLoginGetter->getNonInteractiveLogin(userLoginData) );
//}

void CscPhadexInfrastructureSetup::doShutdown()
{
	releaseTCAConnection();
	shutdownDefaultImpl();
}

void CscPhadexInfrastructureSetup::injectLoginGetter( ICscPhadexLoginGetterConstPtr loginGetter )
{
    m_CscPhadexLoginGetter = loginGetter;
}

//void CscPhadexInfrastructureSetup::injectTCAConnection( libutil::infrastructure::db::dbConnection::IDBConnectionPtr tcaConnection )
//{
//	m_TCAConnection = tcaConnection;
//}

void CscPhadexInfrastructureSetup::establishTCAConnection()
{
	METHODNAME_DEF( CscPhadexInfrastructureSetup, establishTCAConnection )
	BLOG_TRACE_METHOD( getLogger(), fun );

	std::stringstream sTcaPort;
	sTcaPort << m_Config.tcaPort;
	basar::db::sql::DatabaseInfo cicsDatabaseInfo;
	cicsDatabaseInfo.setCICS( m_Config.tcaHost, m_Config.tcaIPAddress, sTcaPort.str().c_str(), m_Config.tcaTransaction, m_Config.tcaUsername, m_Config.tcaPassword );
	m_CICSConnection = basar::db::aspect::Manager::getInstance().createConnect( cicsDatabaseInfo );
}

void CscPhadexInfrastructureSetup::releaseTCAConnection()
{
	METHODNAME_DEF( CscPhadexInfrastructureSetup, releaseTCAConnection )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_CICSConnection.close();
}


}
} // end namespace infrastructure
} // end namespace libutil
