//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "subsequentdeliveryrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/login/login_definitions.h"
#include "infrastructure/setup/isubsequentdeliveryrelevantcalculatorlogingetter.h"
#include "infrastructure/cmdline/subsequentdeliveryrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/subsequentdeliveryrelevantcalculatorcmdlineevaluatorptr.h"

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

// name of applcation to be used in UADM login
// tbd: define application SUBSEQUENTDELIVERYRELEVANTCALCULATOR in UADM and use this name here
static const char* const    UADM_APPLICATION	= "IMPORTPRICELIST";
static const basar::Int16   LOGIN_BRANCHNO      = 5;

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace infrastructure
	{
        namespace setup
        {
			SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup, SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
			}

		    SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::~SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup()
		    {
			    METHODNAME_DEF( SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup, ~SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

			void SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
				login();
				//loadTranslators();
			    establishDBConnection();
			}
    	
            void SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::login()
            {
				prepareLogin();
				initLogin();
			}

            void SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator const> subsequentdeliveryrelevantcalculatorCmdLine
                ( 
                    boost::static_pointer_cast<subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

				//currently we don't use the AppArgs
                //const subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::AppArgs& appArgs = subsequentdeliveryrelevantcalculatorCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( infrastructure::login::USER, 
					                                                               infrastructure::login::PASSWD, 
					                                                               UADM_APPLICATION, 
																				   // for testing use fixed branch 5
					                                                               //appArgs.m_BranchNo 
					                                                               LOGIN_BRANCHNO
				                                                                 );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_SUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
			}

            void SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup::injectLoginGetter( ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetterConstPtr loginGetter )
            {
                m_SUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
