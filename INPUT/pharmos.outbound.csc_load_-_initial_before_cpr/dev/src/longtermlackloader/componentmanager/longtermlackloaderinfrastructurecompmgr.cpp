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
#include "longtermlackloaderinfrastructurecompmgr.h"
#include "longtermlackloaderinfrastructurecompmgrptr.h"
#include "cmdline/longtermlackloadercmdlineoptioncollection.h"
#include "longtermlackloaderversion/longtermlackloader_version.h"
#include "parameter/dbparameterptr.h"
#include "parameter/dbparameter.h"

#include <libutil/cmdline.h>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class definition section
        //----------------------------------------------------------------------------//
        InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
        : libutil::componentManager::InfrastructureCompMgrBase  <   longtermlackloader::componentManager::ApplCompMgr,
                                                                    longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator,
                                                                    longtermlackloader::infrastructure::setup::LONGTERMLACKLOADERInfrastructureSetup
                                                                >   ( argc, argv, infrastructure::LoggerPool::getLoggerLongTermLackLoader() )
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

        /*libutil::misc::ConstClassInfoPtr InfrastructureCompMgr::createClassInfo() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createClassInfo )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::misc::ConstClassInfoPtr( new libutil::misc::ClassInfo(longtermlackloader::getLongtermlackloaderName(), longtermlackloader::getLongtermlackloaderVersion()) );
        }*/
                        
        libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::createLogin() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createLogin )
            BLOG_TRACE_METHOD( getLogger(), fun );

            //return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::OnlineUserAdminLogin(getLoginData()) );
            //return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::BatchUserAdminLogin( getLoginData() ));
            return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::NullLogin() );
        }
        
        void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );

            getInfrastructureSetup()->injectLoginGetter( shared_from_this() );
        }

        libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& userLoginData ) const
        {
            METHODNAME_DEF(InfrastructureCompMgr, getNonInteractiveLogin)
            BLOG_TRACE_METHOD( getLogger(), fun) ;

            return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::BatchUserAdminLogin(userLoginData)) ;
        }

        libutil::infrastructure::login::UserLoginData InfrastructureCompMgr::getLoginData() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, getLoginData )
            BLOG_TRACE_METHOD( getLogger(), fun );

            // batch
            return libutil::infrastructure::login::UserLoginData(
                        longtermlackloader::infrastructure::login::USER, longtermlackloader::infrastructure::login::PASSWD, longtermlackloader::APPLICATION_INFO.getClassName(),
                        longtermlackloader::infrastructure::login::AREA_ID, longtermlackloader::infrastructure::login::LANGUAGE_ID
                    );

            // online
            //return libutil::infrastructure::login::UserLoginData( longtermlackloader::infrastructure::login::USER, libutil::STRING_UNSET, longtermlackloader::APPLICATION_INFO.getClassName() );
            //return libutil::infrastructure::login::UserLoginData( libutil::STRING_UNSET, libutil::STRING_UNSET, longtermlackloader::APPLICATION_INFO.getClassName() );
        }

        libutil::infrastructure::user::IUserPtr InfrastructureCompMgr::createUser() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createUser )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::user::IUserPtr( new libutil::infrastructure::user::UserAdminUser() );
        }

        /*libutil::infrastructure::db::dbConnection::IDBConnectionPtr InfrastructureCompMgr::getDBConnection( libutil::infrastructure::db::dbConnection::DBServerInfo& dbServerInfo ) const
        {
            METHODNAME_DEF( InfrastructureCompMgr, getDBConnection )
            BLOG_TRACE_METHOD( getLogger(), fun );
            
            if( 0 == m_DBConnection.get() )
            {
                m_DBConnection = libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::DBIfxConnection(dbServerInfo) );
            }

            return m_DBConnection;
        }*/

        libutil::infrastructure::db::dbConnection::DBConnectionBasePtr InfrastructureCompMgr::createDBConnection() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createDBConnection )
            BLOG_TRACE_METHOD( getLogger(), fun );
            
            //libutil::infrastructure::db::dbConnection::DBServerInfo dbServerInfo;
            //dbServerInfo.setInfx( "zdev21_tcp", "ide21" );
            return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::DBIfxConnection() );

            //return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::NullDBConnection() );
        }

        libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::createParameterGateway() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createParameterGateway )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::parameter::IParameterGatewayPtr( new libutil::infrastructure::parameter::UserAdminParameter() );
        }

        /*void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );
    
            getInfrastructureSetup()->injectDBConnectionGetter( shared_from_this() );
        }*/

        libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::doGetDBParameterGateway() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doGetDBParameterGateway )
            BLOG_TRACE_METHOD( getLogger(), fun );
    
            longtermlackloader::infrastructure::parameter::DBParameterPtr parameterDBParameter( new longtermlackloader::infrastructure::parameter::DBParameter );
            parameterDBParameter->injectParameterGateway( 
                libutil::infrastructure::parameter::IParameterGatewayPtr(new libutil::infrastructure::parameter::UserAdminParameter) );

            return parameterDBParameter;
        }
 
        basar::I18nString InfrastructureCompMgr::getLanguageCode() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, getLanguageCode )
            BLOG_TRACE_METHOD( getLogger(), fun );

            basar::I18nString languageID = getLogin()->getUserLoginData().getLanguageID();
            languageID.lower();

            return languageID;
        }

        libutil::infrastructure::i18n::ILanguageFileLoaderPtr InfrastructureCompMgr::createLanguageFileLoader() const
        {
            METHODNAME_DEF(InfrastructureCompMgr, createLanguageFileLoader)
                BLOG_TRACE_METHOD(getLogger(), fun);

            //            libutil::infrastructure::i18n::LanguageFileLoaderPtr loader = libutil::infrastructure::i18n::LanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader(getLanguageCode(), getLanguageDirs()) );
            //libutil::infrastructure::i18n::LanguageFileLoaderPtr loader = libutil::infrastructure::i18n::LanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader() );
            //loader->injectQApplication( getQApplication() );
            //return loader;
            return libutil::infrastructure::i18n::ILanguageFileLoaderPtr(new libutil::infrastructure::i18n::NullLanguageFileLoader());

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
} // namespace longtermlackloader
