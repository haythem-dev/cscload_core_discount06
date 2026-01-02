//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "mainwarehousearticlesrelevantcalculatorinfrastructurecompmgr.h"
#include "mainwarehousearticlesrelevantcalculatorinfrastructurecompmgrptr.h"
#include "infrastructure/cmdline/mainwarehousearticlesrelevantcalculatorcmdlineoptioncollection.h"
#include "mainwarehousearticlesrelevantcalculatorinfo/mainwarehousearticlesrelevantcalculator_info.h"

#include <libutil/cmdline.h>
#include <boost/make_shared.hpp>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    //----------------------------------------------------------------------------//
    // class definition section
    //----------------------------------------------------------------------------//
    InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
    : libutil::componentManager::InfrastructureCompMgrBase  < componentManager::ApplCompMgr,
                                                              infrastructure::cmdLine::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator,
                                                              infrastructure::setup::MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup
                                                            > ( argc, argv, LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator() )
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

        return boost::make_shared< libutil::infrastructure::QApplication >(getCmdLineConfiguration().m_Argc, getCmdLineConfiguration().m_Argv);
    }

    boost::shared_ptr< const libutil::misc::ClassInfo > InfrastructureCompMgr::createClassInfo() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, createClassInfo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return boost::make_shared< const libutil::misc::ClassInfo >( getMainwarehousearticlesrelevantcalculatorName(), getMainwarehousearticlesrelevantcalculatorVersion() );
    }

    void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
    {
        METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getInfrastructureSetup()->injectLoginGetter( shared_from_this() );
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

        return boost::make_shared< libutil::infrastructure::login::NullLogin >();
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
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
