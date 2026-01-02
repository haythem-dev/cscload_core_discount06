//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_deliinfo/csc_deli_info.h"
#include "csc_deliinfrastructuresetup.h"
#include "infrastructure/setup/icsc_delilogingetter.h"
#include "infrastructure/cmdline/csc_delicmdlineevaluator.h"
#include "infrastructure/cmdline/csc_delicmdlineevaluatorptr.h"
#include <infrastructure/connectionpool/iconnectionpool.h>

#include "infrastructure/login/login_definitions.h"
#include <infrastructure/parameter/areamapper.h>

#include <libutil/applcomponent.h>
#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <libutil/dbconnection.h>
#include <libutil/login.h>

#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace setup
{
    CSC_DELIInfrastructureSetup::CSC_DELIInfrastructureSetup()
    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
    {
        METHODNAME_DEF( CSC_DELIInfrastructureSetup, CSC_DELIInfrastructureSetup )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CSC_DELIInfrastructureSetup::~CSC_DELIInfrastructureSetup()
    {
        METHODNAME_DEF( CSC_DELIInfrastructureSetup, ~CSC_DELIInfrastructureSetup)
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CSC_DELIInfrastructureSetup::doInit()
    {
        evaluateCmdline();
        login();
        prepareDBConnections();
        establishDBConnections();
    }
        
    void CSC_DELIInfrastructureSetup::login()
    {
        prepareLogin();
        initLogin();
    }

    void CSC_DELIInfrastructureSetup::prepareLogin()
    {
        const csc_deli::infrastructure::cmdLine::AppArgs& appArgs = getCscDeliCmdLineEvaluator()->getAppArgs();
        const libcsc_deli::infrastructure::parameter::AreaMapper areaMapper = libcsc_deli::infrastructure::parameter::AreaMapper::fromCountryCode( appArgs.m_CountryCode );

        const libutil::infrastructure::login::UserLoginData userLoginData( login::USER, login::PASSWD, csc_deli::getCsc_deliName(), 
                                                                           static_cast< basar::Int16 >( areaMapper.getId() ) );
        
        // BB: Bad Hack 2: no set available (emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
        // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
        injectLogin( m_CSC_DELILoginGetter->getNonInteractiveLogin( userLoginData ) );
    }

    void CSC_DELIInfrastructureSetup::prepareDBConnections()
    {
        const csc_deli::infrastructure::cmdLine::AppArgs& appArgs = getCscDeliCmdLineEvaluator()->getAppArgs();
        const basar::Int16 areaId = static_cast< basar::Int16 >( libcsc_deli::infrastructure::parameter::AreaMapper::fromCountryCode( appArgs.m_CountryCode ).getId() );

        // create default connection
        getDBConnectionPool()->createConnection( "default", areaId );

        // look for additional connections to be created
        basar::I18nString connectionNames;
        if( getParameterGateway()->getParameterValue( areaId, "ADD_CONNECTIONS", connectionNames ) )
        {
            basar::cmnutil::CollBString connectionStrings = connectionNames.tokenize( "," );
            for( basar::cmnutil::CollBString::const_iterator it = connectionStrings.begin(); it != connectionStrings.end(); ++it )
            {
                const basar::I18nString& connectionName = *it;
                basar::I18nString connectionAreaId;

                getParameterGateway()->getParameterValue( areaId, connectionName, connectionAreaId );
                getDBConnectionPool()->createConnection( connectionName, static_cast< basar::Int16 >( connectionAreaId.stoi() ) );
            }
        }
    }

    void CSC_DELIInfrastructureSetup::establishDBConnections()
    {
        getDBConnectionPool()->connect();
    }

    void CSC_DELIInfrastructureSetup::releaseDBConnections()
    {
        getDBConnectionPool()->disconnect();
    }

    void CSC_DELIInfrastructureSetup::doShutdown()
    {
        releaseDBConnections();
    }

    void CSC_DELIInfrastructureSetup::injectLoginGetter( ICSC_DELILoginGetterConstPtr loginGetter )
    {
        m_CSC_DELILoginGetter = loginGetter;
    }

    void CSC_DELIInfrastructureSetup::injectDBConnectionPool( libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr connectionPool )
    {
        m_DBConnectionPool = connectionPool;
    }

    libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr CSC_DELIInfrastructureSetup::getDBConnectionPool() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DBConnectionPool.get() );
        return m_DBConnectionPool;
    }

    csc_deli::infrastructure::cmdLine::CSC_DELICmdLineEvaluatorConstPtr CSC_DELIInfrastructureSetup::getCscDeliCmdLineEvaluator()
    {
        // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
        boost::shared_ptr<csc_deli::infrastructure::cmdLine::CSC_DELICmdLineEvaluator const> csc_deliCmdLine
        ( 
            boost::static_pointer_cast< csc_deli::infrastructure::cmdLine::CSC_DELICmdLineEvaluator >( getCmdLineEvaluator() ) 
        );

        return csc_deliCmdLine;
    }

    void CSC_DELIInfrastructureSetup::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr paramGateway )
    {
        m_ParameterGateway = paramGateway;
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr CSC_DELIInfrastructureSetup::getParameterGateway() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ParameterGateway.get() );
        return m_ParameterGateway;
    }

} // end namespace setup
} // end namespace infrastructure
} // end namespace csc_deli
