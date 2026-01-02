//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "csc_deliinfrastructurecompmgr.h"
#include "csc_deliinfrastructurecompmgrptr.h"
#include "infrastructure/cmdline/csc_delicmdlineoptioncollection.h"
#include "infrastructure/login/login_definitions.h"
#include "infrastructure/parameter/dbparametergateway.h"
#include "infrastructure/parameter/dbparametergatewayptr.h"
#include "infrastructure/connectionpool/connectionpool.h"
#include "infrastructure/connectionpool/connectionpoolptr.h"
#include "infrastructure/connectionpool/idbconnectionfactoryconstptr.h"
#include "csc_deliinfo/csc_deli_info.h"

#include <libutil/cmdline.h>
#include <boost/make_shared.hpp>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace csc_deli
{
namespace componentManager
{
    //----------------------------------------------------------------------------//
    // class definition section
    //----------------------------------------------------------------------------//
    InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
    : libutil::componentManager::InfrastructureCompMgrBase  < ApplCompMgr,
                                                              infrastructure::cmdLine::CSC_DELICmdLineEvaluator,
                                                              infrastructure::setup::CSC_DELIInfrastructureSetup
                                                            > ( argc, argv, libcsc_deli::LoggerPool::getLoggerCsc_deli() )
    {
        METHODNAME_DEF( InfrastructureCompMgr, InfrastructureCompMgr)
        BLOG_TRACE_METHOD( getLogger(), fun );

    }

    InfrastructureCompMgr::~InfrastructureCompMgr()
    {
        METHODNAME_DEF( InfrastructureCompMgr, ~InfrastructureCompMgr )
        BLOG_TRACE_METHOD( getLogger(), fun );

    }

    libutil::infrastructure::IQApplicationPtr InfrastructureCompMgr::createQApplication() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createQApplication )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::QApplication >( getCmdLineConfiguration().m_Argc, getCmdLineConfiguration().m_Argv );
    }

    boost::shared_ptr< const libutil::misc::ClassInfo > InfrastructureCompMgr::createClassInfo() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createClassInfo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::misc::ClassInfo >( csc_deli::getCsc_deliName(), csc_deli::getCsc_deliVersion() );
    }

    void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
        BLOG_TRACE_METHOD( getLogger(), fun );
    
        getInfrastructureSetup()->injectLoginGetter( shared_from_this() );
        getInfrastructureSetup()->injectDBConnectionPool( getDBConnectionPool() );
        getInfrastructureSetup()->injectParameterGateway( getParameterGateway() );
    }

    void InfrastructureCompMgr::doInjectApplComponentManagerComponents() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, doInjectApplComponentManagerComponents )
        BLOG_TRACE_METHOD( getLogger(), fun );

        //getApplComponentManager()->injectParameterGateway( getParameterGateway() );
        getApplComponentManager()->injectDBConnectionPool( getDBConnectionPool() );
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::getDBParameterGateway( basar::Int16 areaId ) const
    {
        infrastructure::parameter::DBParameterGatewayPtr parameterGW = boost::make_shared< infrastructure::parameter::DBParameterGateway >( createParameterGateway() );
        parameterGW->setAreaId( areaId );

        return parameterGW;
    }

    libutil::infrastructure::db::dbConnection::IDBConnectionPtr InfrastructureCompMgr::getDBConnection( basar::Int16 areaId ) const
    {
        libutil::infrastructure::db::dbConnection::DBConnectionBasePtr dbConnection = createDBConnection();
        libutil::infrastructure::db::dbConnection::IDBConnectionPtr conn = dbConnection;

        if( ! dbConnection->isDBServerInfoValid() )
        {
            libutil::infrastructure::db::dbConnection::DBConnectionProxyPtr dbConnectionProxy = boost::make_shared< libutil::infrastructure::db::dbConnection::DBConnectionProxy >( dbConnection );
			dbConnectionProxy->injectParameterGateway( getDBParameterGateway( areaId ) );
            dbConnectionProxy->injectSession( getSession() );
            conn = dbConnectionProxy;
        }

        return conn;
    }

    libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr InfrastructureCompMgr::getDBConnectionPool() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, getDBConnectionPool )
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( ! m_DBConnectionPool.get() )
        {
            libcsc_deli::infrastructure::connectionPool::ConnectionPoolPtr connectionPool = boost::make_shared< libcsc_deli::infrastructure::connectionPool::ConnectionPool >();
            connectionPool->injectDBConnectionFactory( shared_from_this() );

            m_DBConnectionPool = connectionPool;
        }

        return m_DBConnectionPool;
    }

    libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& userLoginData ) const
    {
        METHODNAME_DEF( InfrastructureCompMgr, getNonInteractiveLogin )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::login::BatchUserAdminLogin >( userLoginData );
    }

    libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::createLogin() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createLogin )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::login::BatchUserAdminLogin >( getLoginData() );
    }

    libutil::infrastructure::user::IUserPtr InfrastructureCompMgr::createUser() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createUser )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::user::UserAdminUser >();
    }

    libutil::infrastructure::i18n::ILanguageFileLoaderPtr InfrastructureCompMgr::createLanguageFileLoader() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createLanguageFileLoader )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::i18n::NullLanguageFileLoader >();
    }

    libutil::infrastructure::db::dbConnection::DBConnectionBasePtr InfrastructureCompMgr::createDBConnection() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createDBConnection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::db::dbConnection::DBIfxConnection >( /*dbServerInfo*/ );
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::createParameterGateway() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createParameterGateway )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< libutil::infrastructure::parameter::UserAdminParameter >();
    }

    libutil::infrastructure::login::UserLoginData InfrastructureCompMgr::getLoginData() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, getLoginData )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return libutil::infrastructure::login::UserLoginData(
                    csc_deli::infrastructure::login::USER, csc_deli::infrastructure::login::PASSWD, 
                    csc_deli::APPLICATION_INFO.getClassName(), csc_deli::infrastructure::login::AREA_ID, 
                    csc_deli::infrastructure::login::LANGUAGE_ID
                );
    }

    basar::I18nString InfrastructureCompMgr::getLanguageCode() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, getLanguageCode )
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::I18nString languageID = getLogin()->getUserLoginData().getLanguageID();
        languageID.lower();

        return languageID;
    }

    libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection InfrastructureCompMgr::getLanguageDirs() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, getLanguageDirs )
        BLOG_TRACE_METHOD( getLogger(), fun );

        QString multiLanguageDir = "multilang";
        libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection dirs;
        dirs.push_back( getQApplication()->applicationDirPath() + "/" + multiLanguageDir );
        dirs.push_back( QDir::currentPath() + "/../" + multiLanguageDir );

        return dirs;
    }
} // namespace infrastructure
} // namespace csc_deli
