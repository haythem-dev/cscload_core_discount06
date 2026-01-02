//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "subsequentdeliveryrelevantcalculatorinfrastructurecompmgr.h"
#include "subsequentdeliveryrelevantcalculatorinfrastructurecompmgrptr.h"

#include <libutil/cmdline.h>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class definition section
        //----------------------------------------------------------------------------//
        InfrastructureCompMgr::InfrastructureCompMgr( int argc, char** argv )
        : libutil::componentManager::InfrastructureCompMgrBase  <   subsequentdeliveryrelevantcalculator::componentManager::ApplCompMgr,
			                                                        subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator,
			                                                        subsequentdeliveryrelevantcalculator::infrastructure::setup::SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup
																>   ( argc, argv, subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerSubsequentdeliveryrelevantcalculator() )
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
        }

		 void InfrastructureCompMgr::doInjectApplComponentManagerComponents() const
        {
            METHODNAME_DEF( InfrastructureCompMgr, doInjectApplComponentManagerComponents )
            BLOG_TRACE_METHOD( getLogger(), fun );

			boost::shared_ptr<subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator const> subsequentdeliveryrelevantcalculatorCmdLine
            ( 
                boost::static_pointer_cast<subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator>( getCmdLineEvaluator())
            );

            getApplComponentManager()->setCmdLineArguments( subsequentdeliveryrelevantcalculatorCmdLine->getAppArgs() );
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

			return libutil::infrastructure::db::dbConnection::DBConnectionBasePtr( new libutil::infrastructure::db::dbConnection::DBIfxConnection( /*dbServerInfo*/ ) );
			// da Login erst nach dem Auslesen der CommandLine erfolgt, hier nur eine Pseudo-Connection - diese wird erst nach dem Login automatisch mit DBSRV und DB befüllt !!!
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
    } // namespace infrastructure
} // namespace subsequentdeliveryrelevantcalculator
