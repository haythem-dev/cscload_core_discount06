//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "mainwarehousearticlesrelevantcalculatorinfo/mainwarehousearticlesrelevantcalculator_info.h"
#include "mainwarehousearticlesrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/setup/imainwarehousearticlesrelevantcalculatorlogingetter.h"
#include "infrastructure/cmdline/mainwarehousearticlesrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/mainwarehousearticlesrelevantcalculatorcmdlineevaluatorptr.h"
#include "infrastructure/login/login_definitions.h"

#include <libutil/applcomponent.h>
#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <libutil/dbconnection.h>
#include <libutil/login.h>
#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace setup
{
    MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup()
    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
    {
        METHODNAME_DEF( MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup, MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::~MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup()
    {
        METHODNAME_DEF( MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup, ~MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup)
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::doInit()
    {
        evaluateCmdline();
        login();
        //loadTranslators();
        establishDBConnection();
    }

    void MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::login()
    {
        prepareLogin();
        initLogin();
    }

    void MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::prepareLogin()
    {
        // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
        boost::shared_ptr< infrastructure::cmdLine::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator const > mainwarehousearticlesrelevantcalculatorCmdLine
        (
            boost::static_pointer_cast< infrastructure::cmdLine::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator >( getCmdLineEvaluator() )
        );

        const infrastructure::cmdLine::AppArgs& appArgs = mainwarehousearticlesrelevantcalculatorCmdLine->getAppArgs();
        const libutil::infrastructure::login::UserLoginData userLoginData( infrastructure::login::USER, infrastructure::login::PASSWD, 
                                                                           getMainwarehousearticlesrelevantcalculatorName(), appArgs.m_BranchNo );
        
        // BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
        // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
        injectLogin( m_MAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter->getNonInteractiveLogin( userLoginData ) );
    }

    void MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::doShutdown()
    {
        shutdownDefaultImpl();
    }

    void MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup::injectLoginGetter( IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetterConstPtr loginGetter )
    {
        m_MAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter = loginGetter;
    }
} // end namespace setup
} // end namespace infrastructure
} // end namespace libutil
