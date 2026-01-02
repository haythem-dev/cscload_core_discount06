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
#include "fmdrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/setup/ifmdrelevantcalculatorlogingetter.h"
#include "infrastructure/cmdline/fmdrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/fmdrelevantcalculatorcmdlineevaluatorptr.h"

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

static const char* const    UADM_APPLICATION	= "FMDRELEVANTCALCULATOR";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
	namespace infrastructure
	{
        namespace setup
        {
	        FMDRELEVANTCALCULATORInfrastructureSetup::FMDRELEVANTCALCULATORInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( FMDRELEVANTCALCULATORInfrastructureSetup, FMDRELEVANTCALCULATORInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    FMDRELEVANTCALCULATORInfrastructureSetup::~FMDRELEVANTCALCULATORInfrastructureSetup()
		    {
			    METHODNAME_DEF( FMDRELEVANTCALCULATORInfrastructureSetup, ~FMDRELEVANTCALCULATORInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    void FMDRELEVANTCALCULATORInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
                login();
                //loadTranslators();
			    establishDBConnection();
		    }
    	
            void FMDRELEVANTCALCULATORInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void FMDRELEVANTCALCULATORInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<fmdrelevantcalculator::infrastructure::cmdLine::FMDRELEVANTCALCULATORCmdLineEvaluator const> fmdrelevantcalculatorCmdLine
                ( 
                    boost::static_pointer_cast<fmdrelevantcalculator::infrastructure::cmdLine::FMDRELEVANTCALCULATORCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

                const fmdrelevantcalculator::infrastructure::cmdLine::AppArgs& appArgs = fmdrelevantcalculatorCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, UADM_APPLICATION, appArgs.m_BranchNo );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_FMDRELEVANTCALCULATORLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void FMDRELEVANTCALCULATORInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
	        }

            void FMDRELEVANTCALCULATORInfrastructureSetup::injectLoginGetter( IFMDRELEVANTCALCULATORLoginGetterConstPtr loginGetter )
            {
                m_FMDRELEVANTCALCULATORLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
