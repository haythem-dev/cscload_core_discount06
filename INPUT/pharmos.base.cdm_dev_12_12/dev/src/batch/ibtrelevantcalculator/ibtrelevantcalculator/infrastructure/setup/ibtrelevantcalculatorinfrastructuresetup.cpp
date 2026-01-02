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
#include "ibtrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/setup/iibtrelevantcalculatorlogingetter.h"
#include "infrastructure/cmdline/ibtrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/ibtrelevantcalculatorcmdlineevaluatorptr.h"

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

static const char* const    UADM_APPLICATION	= "IBTRELEVANTCALCULATOR";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
	namespace infrastructure
	{
        namespace setup
        {
	        IBTRELEVANTCALCULATORInfrastructureSetup::IBTRELEVANTCALCULATORInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( IBTRELEVANTCALCULATORInfrastructureSetup, IBTRELEVANTCALCULATORInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    IBTRELEVANTCALCULATORInfrastructureSetup::~IBTRELEVANTCALCULATORInfrastructureSetup()
		    {
			    METHODNAME_DEF( IBTRELEVANTCALCULATORInfrastructureSetup, ~IBTRELEVANTCALCULATORInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    void IBTRELEVANTCALCULATORInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
                login();
                //loadTranslators();
			    establishDBConnection();
		    }
    	
            void IBTRELEVANTCALCULATORInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void IBTRELEVANTCALCULATORInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<ibtrelevantcalculator::infrastructure::cmdLine::IBTRELEVANTCALCULATORCmdLineEvaluator const> ibtrelevantcalculatorCmdLine
                ( 
                    boost::static_pointer_cast<ibtrelevantcalculator::infrastructure::cmdLine::IBTRELEVANTCALCULATORCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

                const ibtrelevantcalculator::infrastructure::cmdLine::AppArgs& appArgs = ibtrelevantcalculatorCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, UADM_APPLICATION, appArgs.m_BranchNo );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_IBTRELEVANTCALCULATORLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void IBTRELEVANTCALCULATORInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
	        }

            void IBTRELEVANTCALCULATORInfrastructureSetup::injectLoginGetter( IIBTRELEVANTCALCULATORLoginGetterConstPtr loginGetter )
            {
                m_IBTRELEVANTCALCULATORLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
