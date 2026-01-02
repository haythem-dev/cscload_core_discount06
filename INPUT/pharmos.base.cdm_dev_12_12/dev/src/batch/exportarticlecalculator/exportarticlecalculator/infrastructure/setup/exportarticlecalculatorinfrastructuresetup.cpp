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
#include "exportarticlecalculatorinfrastructuresetup.h"
#include "infrastructure/setup/iexportarticlecalculatorlogingetter.h"
#include "infrastructure/cmdline/exportarticlecalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/exportarticlecalculatorcmdlineevaluatorptr.h"

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

static const char* const    UADM_APPLICATION	= "EXPORTARTICLECALCULATOR";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
	namespace infrastructure
	{
        namespace setup
        {
	        EXPORTARTICLECALCULATORInfrastructureSetup::EXPORTARTICLECALCULATORInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( EXPORTARTICLECALCULATORInfrastructureSetup, EXPORTARTICLECALCULATORInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    EXPORTARTICLECALCULATORInfrastructureSetup::~EXPORTARTICLECALCULATORInfrastructureSetup()
		    {
			    METHODNAME_DEF( EXPORTARTICLECALCULATORInfrastructureSetup, ~EXPORTARTICLECALCULATORInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    void EXPORTARTICLECALCULATORInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
                login();
                //loadTranslators();
			    establishDBConnection();
		    }
    	
            void EXPORTARTICLECALCULATORInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void EXPORTARTICLECALCULATORInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<exportarticlecalculator::infrastructure::cmdLine::EXPORTARTICLECALCULATORCmdLineEvaluator const> exportarticlecalculatorCmdLine
                ( 
                    boost::static_pointer_cast<exportarticlecalculator::infrastructure::cmdLine::EXPORTARTICLECALCULATORCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

                const exportarticlecalculator::infrastructure::cmdLine::AppArgs& appArgs = exportarticlecalculatorCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, UADM_APPLICATION, appArgs.m_BranchNo );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_EXPORTARTICLECALCULATORLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void EXPORTARTICLECALCULATORInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
	        }

            void EXPORTARTICLECALCULATORInfrastructureSetup::injectLoginGetter( IEXPORTARTICLECALCULATORLoginGetterConstPtr loginGetter )
            {
                m_EXPORTARTICLECALCULATORLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
