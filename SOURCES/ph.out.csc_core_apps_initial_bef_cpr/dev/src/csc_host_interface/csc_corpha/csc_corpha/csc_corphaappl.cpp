//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      application controller
 *  \author
 *  \date       01.07.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_corphaappl.h"

#include "csc_corphacmdlineevaluatorptr.h"
#include "csc_corphacmdlineevaluator.h"
#include "csc_corphaappinitializer.h"
#include "csc_corphauc.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include <imailptr.h>
#include <imail.h>
#include <mail.h>

#include <loggerpool.h>
#include "csc_corpha_definitions.h"
#include "appsession.h"
#include <tcaconnection.h>

#include <iapplconfiguration.h>

// Exceptions
#include <setupsignalhandlingexception.h>
#include <softkillexception.h>
#include <appinitializerexception.h>
#include <xmlreaderexception.h>
#include <missingdependencyinjectionexception.h>
#include <cmdlineexception.h>
#include <mailexception.h>

#include <libbasarappl.h>
#include <libbasarcmnutil_logging.h>
#include <cmdlineoption_definitions.h>
#include <cmdlineparser.h>
#include <remoteprocedureresult.h>
#include <remoteprocedurecaller.h>
#include "property_definitions.h"

#include <signal.h>

#include <libbasardbaspect.h>

#include "ipxvbservicelocator.h"
#include "pxvbcomponentmanager.h"

#include "ipxvbordercollection.h"
#include "pxvbordercollectiondm.h"

#include "ipxvbtaskcontrol.h"
#include "pxvbtaskcontrol.h"

#include "icicsorderdm.h"
#include "cicsorderdm.h"

#include "remoteprocedurecomponentmanager.h"
#include "iremoteprocedureservicelocator.h"

#include "csc_corphacmdlineoption_definitions.h"
#include "stringtransformer.h"

//--------------------------------------------------------------------------------------------------//
// extern definition section
//--------------------------------------------------------------------------------------------------//
//#ifdef _AIX
namespace basar {
    namespace cmnutil {
        using csc_corpha::CSC_CorphaApplBase;

        template <>
        typename Singleton< CSC_CorphaApplBase >::InstancePtr &
            Singleton< CSC_CorphaApplBase >::inst()
        {
            // the one and only instance
            static InstancePtr s_Inst;

            return s_Inst;
        }
    }
}
//#endif
namespace csc_corpha
{
#ifndef WIN32
#include <unistd.h>
static unsigned int Sleep( unsigned int milliseconds )
{
    return usleep( milliseconds * 1000 );
}
#else
#include <windows.h>
#endif


//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
CSC_CorphaApplBase::CSC_CorphaApplBase() :
    m_AppInitializer (cmdLine::CSC_CorphaAppInitializerPtr(new cmdLine::CSC_CorphaAppInitializer())),
    m_Logger( libcsc_utils::LoggerPool::LoggerCSC ),
    m_ExitGracefull(false)
{
    METHODNAME_DEF( CSC_CorphaApplBase, CSC_CorphaApplBase )
    BLOG_TRACE_METHOD( m_Logger, fun );
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
CSC_CorphaApplBase::~CSC_CorphaApplBase()
{
    shutdown();
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::init( int argc, char *argv[] )
{
    METHODNAME_DEF( CSC_CorphaApplBase, init )
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
        cmdLine::CSC_CorphaCmdLineEvaluatorPtr cmdEvalPtr = cmdLine::CSC_CorphaCmdLineEvaluatorPtr( new cmdLine::CSC_CorphaCmdLineEvaluator( ::libBatch::cmdLine::CmdLineConfiguration( argc, argv ) ) );
        cmdEvalPtr->evaluate();

        m_AppInitializer->setAppArgs( cmdEvalPtr );
        m_AppInitializer->init();

        initSession( m_AppInitializer );

        m_TestingMode = m_ApplConfiguration->isTestingSet();
    }
    catch( libcsc_utils::AppInitializerException& ex )
    {
        libcsc_utils::LoggerPool::LoggerCSC.forcedLog( log4cplus::ERROR_LOG_LEVEL, ex.what(), __FILE__, __LINE__ );
        throw ex;
    }
    catch(::libBatch::cmdLine::CmdLineException& e)
    {
        libcsc_utils::LoggerPool::LoggerCSC.forcedLog( log4cplus::ERROR_LOG_LEVEL, e.what(), __FILE__, __LINE__ );
        throw e;
    }
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
basar::appl::EventReturnStruct CSC_CorphaApplBase::run()
{
    METHODNAME_DEF( CSC_CorphaApplBase, run )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    try
    {
        m_SignalHandler.setupSignalHandling();
        m_SignalHandler.registerSignalReceiver(*this);
    }
    catch( libcsc_utils::SetupSignalHandlingException& ex )
    {
        m_CSC_LoggerPtr->logBasarException( "error setting up signal handling", ex );
        throw ex;
    }
    catch( ... )
    {
        m_CSC_LoggerPtr->log( log4cplus::ERROR_LOG_LEVEL, "generic error setting up signal handling" );
    }

    try
    {
        if( !checkConnections() )
        {
            connect();
        }
        createComponents();

        while( !m_ExitGracefull )
        {
            // check if TCA connections are not OK, reconnect
            if( !checkConnections() ){
                reconnect();
            }

            m_CSC_CorphaUC.run();

            processingSleep();

            if( m_ExitGracefull )
            {
                m_CSC_LoggerPtr->log( log4cplus::INFO_LOG_LEVEL, "exit - got signal" );
                break;
            }

            if( m_TestingMode )
            {
                m_CSC_LoggerPtr->log( log4cplus::INFO_LOG_LEVEL, "exit - only one cycle due to test mode" );
                break;
            }

            if( !checkConnections() )
            {
                m_CSC_LoggerPtr->log( log4cplus::INFO_LOG_LEVEL, "checkConnections failed - try to connect" );
                connect();
            }
        }
    }
    catch( libcsc_utils::MissingDependencyInjectionException & e )
    {
        m_CSC_LoggerPtr->logBasarException("", e);
    }
    catch( libcsc_utils::AppInitializerException & e )
    {
        m_CSC_LoggerPtr->logBasarException("", e);
    }
    catch( libcsc_utils::XmlReaderException& e )
    {
        m_CSC_LoggerPtr->logBasarException("", e);
    }
    catch( libcsc_utils::SoftKillException & e )
    {
        m_CSC_LoggerPtr->logBasarException("", e);
    }

    return basar::appl::EventReturnType();
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr CSC_CorphaApplBase::getPXVBServiceLocator()
{
    METHODNAME_DEF( CSC_CorphaApplBase, getPXVBServiceLocator )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace domMod::corpha::pxVerbund;

    if( 0 == m_PXVBServiceLocator.get() )
    {
        m_PXVBServiceLocator = IPXVBServiceLocatorPtr( new PXVBComponentManager(m_ApplConfiguration, m_CSC_LoggerPtr) );
    }

    return m_PXVBServiceLocator;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
domMod::corpha::pxVerbund::IPXVBTaskControlPtr CSC_CorphaApplBase::getPXVBTaskControl()
{
    METHODNAME_DEF( CSC_CorphaApplBase, getPXVBTaskControl )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace domMod::corpha::pxVerbund;

    if( 0 == m_PXVBTaskControl.get() )
    {
        m_PXVBTaskControl = IPXVBTaskControlPtr( new PXVBTaskControl( getPXVBServiceLocator(), m_ApplConfiguration, m_CSC_LoggerPtr ) );
    }

    return m_PXVBTaskControl;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr CSC_CorphaApplBase::getPXVBOrderCollection()
{
    METHODNAME_DEF( CSC_CorphaApplBase, getPXVBOrderCollection )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace domMod::corpha::pxVerbund;

    if( 0 == m_PXVBOrderCollection.get() )
    {
        m_PXVBOrderCollection = IPXVBOrderCollectionPtr( new PXVBOrderCollectionDM( m_CSC_LoggerPtr, getPXVBServiceLocator(), m_ApplConfiguration ) );
    }

    return m_PXVBOrderCollection;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
domMod::corpha::processOrder::ICICSOrderDMPtr CSC_CorphaApplBase::getCICSOrderDM()
{
    METHODNAME_DEF( CSC_CorphaApplBase, getCICSOrderDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
    using namespace domMod::corpha::processOrder;
    if( 0 == m_CICSOrderDM.get() )
    {
        m_CICSOrderDM = ICICSOrderDMPtr( new CICSOrderDM( m_AppSession->m_TCAConnection->getCurrentConnection(), m_CSC_LoggerPtr, m_ApplConfiguration ) );
    }
    return m_CICSOrderDM;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries )
{
    METHODNAME_DEF( CSC_CorphaApplBase, establishConnection )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    basar::Int32 currentTries(0);
    (void) maxRetries;
    (void) secBetweenRetries;

    // establish connection
    currentTries = 0;
    //while( !dbconn->isOpen() && !m_ExitGracefull)
    while( !dbconn->isValid() && !m_ExitGracefull)
    {
        // try to connect to connection
        try
        {
            m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "trying to connect" );
            dbconn->connect();
        }
        catch(basar::Exception& ex)
        {
            m_CSC_LoggerPtr->logBasarException("text exception during dbConnect", ex, m_ApplConfiguration);
        }

        if( dbconn->isValid() )
        {
            m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "connected" );
            break;
        }

        // count connection tries
        ++currentTries;

        // send warning if connect fails only for the first trial
        if( 1 == currentTries )
        {
            m_CSC_LoggerPtr->log(log4cplus::WARN_LOG_LEVEL, "connection to tca database could not be established on the first try" );
        }

        if( maxRetries == currentTries )
        {
            basar::VarString logmessage = "";
            logmessage.format( "connection to tca database could not be established after %d retries", maxRetries);
            m_CSC_LoggerPtr->log(log4cplus::ERROR_LOG_LEVEL, logmessage);

            currentTries = 0;
        }

        waitRetries(secBetweenRetries);
    }
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::disconnect()
{
    METHODNAME_DEF( CSC_CorphaApplBase, disconnect )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    m_AppSession->m_TCAConnection->disconnect();
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
bool CSC_CorphaApplBase::checkConnections()
{
    METHODNAME_DEF( CSC_CorphaApplBase, checkConnections )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    //return m_AppSession->m_TCAConnection->isOpen();
    return m_AppSession->m_TCAConnection->isValid();
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::connect()
{
    METHODNAME_DEF( CSC_CorphaApplBase, connect )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    establishConnection( m_AppSession->m_TCAConnection, m_ApplConfiguration->getTCAConnectionRetries(), m_ApplConfiguration->getTCAConnectionWaitBeforeRetry() );
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::reconnect()
{
    METHODNAME_DEF( CSC_CorphaApplBase, reconnect )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    //1) tear down old components
    resetDMs();
    //2) kill old db connections
    resetConnections();

    logConnectionStatus();
    m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text starting reconnect...");

    try
    {
        //3) re-initialize app-session
        initSession( m_AppInitializer );
        //4) re-establish db connections
        connect();
        //5) create components anew
        createComponents();
    }
    catch(...)
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text reconnect: got exception during connect / createComponents, ignored");
    }
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::resetDMs()
{
    METHODNAME_DEF( CSC_CorphaApplBase, resetDMs )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    try {
        if (0 != m_CICSOrderDM.get()){
            m_CICSOrderDM.reset();
        }
    }
    catch(...){
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during resetting dm");
    }
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::resetConnections()
{
    METHODNAME_DEF( CSC_CorphaApplBase, resetConnections )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    try
    {
        m_AppSession->m_TCAConnection->disconnect();
    }
    catch(...)
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
    }

    try
    {
        m_AppSession->m_TCAConnection.reset();
    }
    catch(...)
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during reset of tca connection, ignored");
    }

}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::logConnectionStatus()
{
    METHODNAME_DEF( CSC_CorphaApplBase, logConnectionStatus )
    BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

    //get status of components
    bool statusCICSOrderDM   = (0 == m_CICSOrderDM.get());
    bool statusTCAConnection = (0 == m_AppSession->m_TCAConnection.get());

    std::ostringstream os;

    os << "status of components:\n";
    os << "CICSOrderDM: " << std::boolalpha << statusCICSOrderDM << "\n";
    os << "TCAConnection: " << std::boolalpha << statusTCAConnection << "\n";


    m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, os.str().c_str());
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::createComponents()
{
    m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components...");

    try
    {
        // Logger
            m_CSC_CorphaUC.injectICSC_LoggerPtr(m_CSC_LoggerPtr);

        // ApplConfiguration
            m_CSC_CorphaUC.injectApplConfiguration( m_ApplConfiguration );

        // RemoteProcedureServiceLocator
            domMod::corpha::IRemoteProcedureServiceLocatorPtr rpsvclocator =
                domMod::corpha::IRemoteProcedureServiceLocatorPtr(
                    new domMod::corpha::RemoteProcedureComponentManager(
                        m_AppSession->m_TCAConnection->getCurrentConnection(),
                        m_ApplConfiguration,
                        m_CSC_LoggerPtr ) );
            m_CSC_CorphaUC.injectRemoteProcedureServiceLocatorPtr( rpsvclocator );

        // PXVBServiceLocator
            m_CSC_CorphaUC.injectPXVBServiceLocatorPtr( getPXVBServiceLocator() );

        // PXVBOrderCollection
            m_CSC_CorphaUC.injectPXVBOrderCollectionPtr( getPXVBOrderCollection() );

        // CICSOrderDM
            m_CSC_CorphaUC.injectCICSOrderDM( getCICSOrderDM() );

        // TaskControl
            m_CSC_CorphaUC.injectPXVBTaskControl( getPXVBTaskControl() );

    }
    catch(basar::Exception& ex)
    {
        m_CSC_LoggerPtr->logBasarException("exception during createComponents", ex);
        throw ex;
    }

    m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components finished");
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
const basar::VarString CSC_CorphaApplBase::getTCAStartTransaction() const
{
    METHODNAME_DEF( CSC_CorphaApplBase, getTCAStartTransaction )
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString retval("TCAX");

    if( cmdLine::ORDERFILTER_ALL == m_ApplConfiguration->getOrderFilter() )
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "TCAcces startTransaction set to TCAX");
        retval = "TCAX";
    }
    if( cmdLine::ORDERFILTER_EVEN == m_ApplConfiguration->getOrderFilter() )
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "TCAcces startTransaction set to TCAE");
        retval = "TCAE";
    }
    if( cmdLine::ORDERFILTER_ODD == m_ApplConfiguration->getOrderFilter() )
    {
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "TCAcces startTransaction set to TCAO");
        retval = "TCAO";
    }

    return retval;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
const basar::db::sql::DatabaseInfo CSC_CorphaApplBase::getTCAConfiguration( const cmdLine::CSC_CorphaAppInitializerPtr appInitializer )
{
    METHODNAME_DEF( CSC_CorphaApplBase, getTCAConnfiguration )
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::db::sql::DatabaseInfo tcadatabaseinfo = appInitializer->getTCAConnConfiguration();
    tcadatabaseinfo.cicsCustom.startTransact = getTCAStartTransaction();

    return tcadatabaseinfo;
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::initSession( const cmdLine::CSC_CorphaAppInitializerPtr appInitializer )
{
    METHODNAME_DEF( CSC_CorphaApplBase, initSession )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_ApplConfiguration = appInitializer->getAppConfiguration();
    m_CSC_LoggerPtr = appInitializer->getCSCLogger();

    m_AppSession = AppSessionPtr( new AppSession(
                                libBatch::dbConnection::DBConnectionBasePtr(
                                        new libcsc_utils::dbConnection::TCAConnection( getTCAConfiguration( appInitializer ) ) ) ) );

    domMod::corpha::ProcessOrderDM::StringTransformer::setCountry( appInitializer->getAppConfiguration()->getCountryCode() );
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::shutdown()
{
    METHODNAME_DEF( CSC_CorphaApplBase, shutdown )
    BLOG_TRACE_METHOD( m_Logger, fun );
    disconnect();
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::processingSleep()
{
    //if( m_ApplConfiguration->isExtendedLoggingSet() )
    //{
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "sleeping in ApplBase ...");
    //}

    Sleep(m_ApplConfiguration->getPollingInterval());

    //if( m_ApplConfiguration->isExtendedLoggingSet() )
    //{
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... wake up again!" );
    //}
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::waitRetries(basar::Int32 time)
{
    Sleep(time);
}
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
void CSC_CorphaApplBase::receiveSignal(int signal)
{
    if (SIGTERM == signal || SIGINT == signal)
    {
        m_ExitGracefull = true;
        m_CSC_CorphaUC.flagExitGracefull();
        if( 0 != m_CSC_LoggerPtr.get() )
        {
            m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "received SIGTERM / SIGINT" );
        }
    }
}
//--------------------------------------------------------------------------------------------------//

} // end namespace csc_corpha
