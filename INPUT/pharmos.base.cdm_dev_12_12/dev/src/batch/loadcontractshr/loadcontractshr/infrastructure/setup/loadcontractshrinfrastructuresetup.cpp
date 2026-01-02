//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "loadcontractshrinfrastructuresetup.h"
#include "infrastructure/setup/iloadcontractshrlogingetter.h"
#include "infrastructure/cmdline/loadcontractshrcmdlineevaluator.h"
#include "infrastructure/cmdline/loadcontractshrcmdlineevaluatorptr.h"

#include <libutil/applcomponent.h>
#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <libutil/dbconnection.h>
#include <libutil/login.h>
#include <libutil/exception.h>
#include <libutil/login.h>
#include <libutil/parameter.h>
#include <libutil/languagefileloader.h>

#include <libbasarcmnutil.h>

static const char* const    UADM_APPLICATION	= "LOADCONTRACTSHR";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
	namespace infrastructure
	{
        namespace setup
        {
	        LoadContractsHrInfrastructureSetup::LoadContractsHrInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF(LoadContractsHrInfrastructureSetup, LoadContractsHrInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    LoadContractsHrInfrastructureSetup::~LoadContractsHrInfrastructureSetup()
		    {
			    METHODNAME_DEF( LoadContractsHrInfrastructureSetup, ~LoadContractsHrInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    void LoadContractsHrInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
                login();
                //loadTranslators();
			    establishDBConnection();
		    }
    	
            void LoadContractsHrInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void LoadContractsHrInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<loadcontractshr::infrastructure::cmdLine::LoadContractsHrCmdLineEvaluator const> LoadContractsHrCmdLine
                ( 
                    boost::static_pointer_cast<loadcontractshr::infrastructure::cmdLine::LoadContractsHrCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

                const loadcontractshr::infrastructure::cmdLine::AppArgs& appArgs = LoadContractsHrCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, UADM_APPLICATION, 79/* appArgs.m_BranchNo*/ );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_LoadContractsHrLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void LoadContractsHrInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
	        }

            void LoadContractsHrInfrastructureSetup::injectLoginGetter( ILoadContractsHrLoginGetterConstPtr loginGetter )
            {
                m_LoadContractsHrLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
