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
#include "ibtorderimportinfrastructurecompmgr.h"
#include "ibtorderimportinfrastructurecompmgrptr.h"

#include "infrastructure/mail/mailalertptr.h"
#include "infrastructure/mail/mailalert.h"
#include "infrastructure/mail/mailparameterproxyptr.h"
#include "infrastructure/mail/mailparameterproxy.h"

#include <libutil/cmdline.h>
#include <persistence/connection.h>

#include "infrastructure/parameterkeys.h"

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class definition section
        //----------------------------------------------------------------------------//
        InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
        : libutil::componentManager::InfrastructureCompMgrBase  <   ibtorderimport::componentManager::ApplCompMgr,
                                                                    ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator,
                                                                    ibtorderimport::infrastructure::setup::IBTORDERIMPORTInfrastructureSetup
																>   ( argc, argv, ibtorderimport::LoggerPool::getLoggerIbtorderimport() )
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
        }

        void InfrastructureCompMgr::doInjectInfrastructureSetupComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectInfrastructureSetupComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );
    
            getInfrastructureSetup()->injectLoginGetter( shared_from_this() );
			getInfrastructureSetup()->injectCscDbConnection( getCscDbConnection() );
			getInfrastructureSetup()->injectDbParameterGateway( getParameterGateway() );
        }

		libcsc::persistence::ConnectionPtr	InfrastructureCompMgr::getCscDbConnection() const
		{
			if (0 == m_DbConnection.get())
			{
				m_DbConnection = libcsc::persistence::ConnectionPtr (new libcsc::persistence::Connection());
			}
			
			return m_DbConnection;
		}

		 void InfrastructureCompMgr::doInjectApplComponentManagerComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectApplComponentManagerComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );

			boost::shared_ptr<ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator const> ibtorderimportCmdLine
            ( 
                boost::static_pointer_cast<ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator>( getCmdLineEvaluator()) 
            );

            getApplComponentManager()->setCmdLineArguments( ibtorderimportCmdLine->getAppArgs() );
			getApplComponentManager()->injectMailAlert( getMailAlert() );
			getApplComponentManager()->injectCscDbConnection( getCscDbConnection() );
        }

        libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& userLoginData ) const
        {
            METHODNAME_DEF( InfrastructureCompMgr, getNonInteractiveLogin )
            BLOG_TRACE_METHOD( getLogger(), fun );

			return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::BatchUserAdminLogin(userLoginData) );
        }

        libutil::infrastructure::login::ILoginPtr InfrastructureCompMgr::createLogin() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createLogin )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::login::ILoginPtr( new libutil::infrastructure::login::NullLogin() ); // --> wenn username / password / branchno über CommandLine kommen, dann so!
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

            return libutil::infrastructure::i18n::ILanguageFileLoaderPtr( new libutil::infrastructure::i18n::NullLanguageFileLoader() );

        }

        libutil::infrastructure::db::dbConnection::DBConnectionBasePtr InfrastructureCompMgr::createDBConnection() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createDBConnection )
            BLOG_TRACE_METHOD( getLogger(), fun );

			return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::NullDBConnection( ) );
        }

        libutil::infrastructure::parameter::IParameterGatewayPtr InfrastructureCompMgr::createParameterGateway() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, createParameterGateway )
            BLOG_TRACE_METHOD( getLogger(), fun );

            return libutil::infrastructure::parameter::IParameterGatewayPtr( new libutil::infrastructure::parameter::UserAdminParameter() );
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

		infrastructure::mail::IMailAlertPtr	InfrastructureCompMgr::getMailAlert() const
		{
			infrastructure::mail::MailAlertPtr p = infrastructure::mail::MailAlertPtr(new infrastructure::mail::MailAlert(LoggerPool::getLoggerIbtorderimport()));
			p->injectParameterProxy(getMailParameterProxy());
			return p;
		}

		infrastructure::mail::IMailParameterProxyPtr InfrastructureCompMgr::getMailParameterProxy() const
		{
			METHODNAME_DEF( InfrastructureCompMgr, getMailParameterProxy )
			BLOG_TRACE_METHOD( getLogger(), fun );

			if ( NULL == m_MailParameterProxy.get() )
			{
				using infrastructure::mail::MailParameterProxyPtr;
				using infrastructure::mail::MailParameterProxy;

				MailParameterProxyPtr paraProxy = MailParameterProxyPtr( new MailParameterProxy() );

				paraProxy->injectParameterGateway( getParameterGateway() );
				m_MailParameterProxy = paraProxy;
			}

			return m_MailParameterProxy;
		}

		basar::Int32		InfrastructureCompMgr::getSleepInterval()    const
		{
			basar::I18nString paraVal;

			getParameterGateway()->getParameterValue(constants::UADM_SLEEP_INTERVAL, paraVal);
				
			return paraVal.stoi();
		}

    } // namespace infrastructure
} // namespace ibtorderimport
