//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "csc_phadexinfrastructurecompmgr.h"
#include "csc_phadexinfrastructurecompmgrptr.h"
#include "infrastructure/cmdline/csc_phadexcmdlineoptioncollection.h"
#include "infrastructure/parameter/dbparameterptr.h"
#include "infrastructure/parameter/dbparameter.h"

#include <libutil/cmdline.h>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class definition section
        //----------------------------------------------------------------------------//
        InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
        : libutil::componentManager::InfrastructureCompMgrBase  <   csc_phadex::componentManager::ApplCompMgr,
                                                                    csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator,
                                                                    csc_phadex::infrastructure::setup::CscPhadexInfrastructureSetup
                                                                >   ( argc, argv, csc_phadex::LoggerPool::getLoggerCsc_phadex() )
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

            return libutil::infrastructure::IQApplicationPtr( new libutil::infrastructure::QApplication(getCmdLineConfiguration().m_Argc, getCmdLineConfiguration().m_Argv) );
            //return libutil::infrastructure::IQApplicationPtr( new libutil::infrastructure::NullQApplication() );
        }

        void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );
    
            getInfrastructureSetup()->injectLoginGetter( shared_from_this() );
        }

        libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::doGetDBParameterGateway() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doGetDBParameterGateway )
            BLOG_TRACE_METHOD( getLogger(), fun );
    
            csc_phadex::infrastructure::parameter::DBParameterPtr parameterDBParameter( new csc_phadex::infrastructure::parameter::DBParameter );
            parameterDBParameter->injectParameterGateway( 
                libutil::infrastructure::parameter::IParameterGatewayPtr(new libutil::infrastructure::parameter::UserAdminParameter) );

            return parameterDBParameter;
        }

        //libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& userLoginData ) const
        //{
        //    METHODNAME_DEF( InfrastructureCompMgr, getNonInteractiveLogin )
        //    BLOG_TRACE_METHOD( getLogger(), fun );

        //    return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::BatchUserAdminLogin(userLoginData) );
        //}

        libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::createLogin() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createLogin )
            BLOG_TRACE_METHOD( getLogger(), fun );

            //return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::OnlineUserAdminLogin(getLoginData()) );
            return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::NullLogin() );
        }

        libutil::infrastructure::user::IUserPtr InfrastructureCompMgr::createUser() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createUser )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::user::IUserPtr( new libutil::infrastructure::user::UserAdminUser() );
        }

        libutil::infrastructure::i18n::ILanguageFileLoaderPtr InfrastructureCompMgr::createLanguageFileLoader() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createLanguageFileLoader )
            BLOG_TRACE_METHOD( getLogger(), fun );

//            libutil::infrastructure::i18n::LanguageFileLoaderPtr loader = libutil::infrastructure::i18n::LanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader(getLanguageCode(), getLanguageDirs()) );
            //libutil::infrastructure::i18n::LanguageFileLoaderPtr loader = libutil::infrastructure::i18n::LanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader() );
            //loader->injectQApplication( getQApplication() );
            //return loader;
            return libutil::infrastructure::i18n::ILanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader() );

        }

        libutil::infrastructure::db::dbConnection::DBConnectionBasePtr InfrastructureCompMgr::createDBConnection() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createDBConnection )
            BLOG_TRACE_METHOD( getLogger(), fun );
            
            //libutil::infrastructure::db::dbConnection::DBServerInfo dbServerInfo( m_DBName, m_DBSrvName );

			//TODO
            return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::DBIfxConnection( /*dbServerInfo*/ ) );
            //return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::NullDBConnection() );
        }

        libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::createParameterGateway() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createParameterGateway )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::parameter::IParameterGatewayPtr( new libutil::infrastructure::parameter::UserAdminParameter() );
        }

        //libutil::infrastructure::login::UserLoginData InfrastructureCompMgr::getLoginData() const
        //{
        //    METHODNAME_DEF( InfrastructureCompMgr, getLoginData )
        //    BLOG_TRACE_METHOD( getLogger(), fun );

        //    // batch
        //    return libutil::infrastructure::login::UserLoginData(
        //                csc_phadex::infrastructure::login::USER, csc_phadex::infrastructure::login::PASSWD, csc_phadex::APPLICATION_INFO.getClassName(),
        //                csc_phadex::infrastructure::login::AREA_ID, csc_phadex::infrastructure::login::LANGUAGE_ID
        //            );

        //    // online
        //    //return libutil::infrastructure::login::UserLoginData( csc_phadex::infrastructure::login::USER, libutil::STRING_UNSET, csc_phadex::APPLICATION_INFO.getClassName() );
        //    //return libutil::infrastructure::login::UserLoginData( libutil::STRING_UNSET, libutil::STRING_UNSET, csc_phadex::APPLICATION_INFO.getClassName() );
        //    
        //}


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
} // namespace csc_phadex
