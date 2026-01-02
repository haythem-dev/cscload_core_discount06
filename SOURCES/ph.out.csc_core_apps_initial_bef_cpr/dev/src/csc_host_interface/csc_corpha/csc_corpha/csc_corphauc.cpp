//-------------------------------------------------------------------------------------------//
/*! \file
*   \brief csc_corpha's sole usecase
*   \author
*   \date
*/
//-------------------------------------------------------------------------------------------//

#include "csc_corphauc.h"

#include <libbasarappl.h>
#include <libbasarcmnutil_logging.h>
#include <classinfo_macros.h>
#include <icsc_logger.h>
#include <invalidstatuschangeexception.h>
#include <missingdependencyinjectionexception.h>
#include <iremoteprocedurecaller.h>
#include <remoteprocedureresult.h>
#include <iapplconfiguration.h>

#include "ipxvbordercollection.h"
#include "pxvbordercollectiondm.h"
#include "pxvborderdm.h"
#include "pxvborderdmptr.h"
#include "pxvborderheader.h"
#include "pxvborderheaderptr.h"
#include "icicsorderdm.h"
#include "cicsorderdm.h"
#include "ordertransformer.h"
#include "recordtypecollectionptr.h"
#include "recordtypecollection.h"
#include "ipxvbservicelocator.h"
#include "iremoteprocedureservicelocator.h"
#include "pvhx04_includes.h"
#include "csc_corphacmdlineoption_definitions.h"
#include "ipxvbtaskcontrol.h"

#include "pxttype.hpp"
#include "pxvbsession.h"

namespace csc_corpha
{
namespace useCase
{

//-------------------------------------------------------------------------------------------//
CSC_CorphaUC::CSC_CorphaUC()
    : m_CurrentOrder(0), m_ExitGracefull(false)
{
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
CSC_CorphaUC::~CSC_CorphaUC()
{
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
basar::appl::EventReturnStruct CSC_CorphaUC::run()
{
    METHODNAME_DEF( CSC_CorphaUC, run );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    basar::VarString logmessage("");
    int ordersprocessed = 0;

    checkInjections();
    domMod::corpha::pxVerbund::IPXVBSessionPtr ipxVBSessionPtr = m_PXVBServiceLocator->getPXVBSession();
    pxSession* session = ipxVBSessionPtr->get();

    nString key("");
    pxTimeTypeList *timelist = NULL;
    timelist = new pxTimeTypeList(session);

    while( true )
    {
        m_PXVBTaskControl->setHeartBeat();

        nDate today;
        timelist->Select(TYPE_ADS_TIME_TRANSFER_ORDER, key, m_ApplConfiguration->getBranchNo());
        if ( timelist->Entries() )
        {
            if ( timelist->FindDayOfWeek( today.GetDayOfWeek() ) )
            {
                if (timelist->TimeInWindow() == false)
                {
                    continue;
                }
            }
        }

        m_PXVBOrderCollection->findOrders2BeTransferred( getOrderSelectionMode() );

        domMod::corpha::pxVerbund::PXVBOrderDMPtr order = m_PXVBOrderCollection->getFirst();
        ordersprocessed = 0;

        for( ; !m_PXVBOrderCollection->isEnd(); order = m_PXVBOrderCollection->getNext() )
        {
            ++ordersprocessed;
            m_PXVBTaskControl->setHeartBeat();
            m_CurrentOrder = order->getOrderHeader()->getOrder()->KdAuftragNr();

            if( !this->lockOrder4Transfer( order ) ) { continue; } // LockManager lock

            if( !hasToBeTransferred( order ) )
            {
                finishOrderWithoutTransfer( order );
            }
            else
            {
                startOrderTransfer( order );
                callRemoteOrderProcessing( order->getOrderHeader()->getOrder()->KdAuftragNr(), order->getTime() );
                finishOrderTransfer( order );
            }

            this->unlockOrder4Transfer( order ); // LockManager unlock

            if( m_ExitGracefull )
            {
                if(timelist != NULL)
                    delete timelist;
                timelist = NULL;

                return basar::appl::EventReturnStruct();
            }
        }

        if( 0 == ordersprocessed )
        {
            break;
        }
    }
    if (timelist != NULL)
        delete timelist;

    return basar::appl::EventReturnStruct();
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
bool CSC_CorphaUC::lockOrder4Transfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, lockOrder4Transfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString logmessage("");
    if( !order->getOrderHeader()->getOrder()->lock4Corpha() )
    {
        logmessage.format( "%s -> order still locked - no order transfer", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
        return false;
    }

    logmessage.format( "%s -> order locked for CORPHA processing", getInstanceDetails().c_str() );
    m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
    return true;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::unlockOrder4Transfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, unlockOrder4Transfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString logmessage("");
    order->getOrderHeader()->getOrder()->unlock4Corpha();
    logmessage.format( "%s -> order unlocked for CORPHA processing", getInstanceDetails().c_str() );
    m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
bool CSC_CorphaUC::hasToBeTransferred( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, startOrderTransfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    if( !order->hasToBeTransferred() )
    {
        basar::VarString logmessage("");
        logmessage.format( "%s -> no order transfer", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::startOrderTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, startOrderTransfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    try
    {
        order->setEventOrderTransferStarted();
        m_CICSOrderDM->init( order->getOrderHeader()->getOrder()->KdAuftragNr() );
        sendOrder2Pharmos( order );
    }
    catch(...)
    {
        basar::VarString logmessage("");
        logmessage.format( "%s -> unexpected exception in CSC_CorphaUC::startOrderTransfer", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );
        throw;
    }
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::sendOrder2Pharmos( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, sendOrder2Pharmos );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    domMod::corpha::ProcessOrderDM::OrderTransformer transformer( m_CSC_Logger, m_ApplConfiguration );
    m_CICSOrderDM->send( transformer.transform( order ) );
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::callRemoteOrderProcessing( basar::Long64 orderno, basar::Long64 time )
{
    METHODNAME_DEF( CSC_CorphaUC, callRemoteOrderProcessing );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString logmessage("");
    try
    {
        libcsc_utils::IRemoteProcedureCallerPtr caller = m_RemoteProcedureServiceLocator->getRemoteProcedureCaller( orderno, time );

        logmessage.format( "%s   -> started PDX041", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage );

        libcsc_utils::RemoteProcedureResult result = caller->call();

        logmessage.format( "%s   -> finished PDX041", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage );

        m_PDX040Result = result.m_Success;
        if( !m_PDX040Result )
        {
            logmessage.format( "%s   -> PDX041 Error: %s", getInstanceDetails().c_str(), result.m_InfoMessage.c_str() );
            m_CSC_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );
        }
    }
    catch( ... )
    {
        logmessage.format( "%s   -> unexpected exception in CSC_CorphaUC::callRemoteOrderProcessing", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );
        throw;
    }
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::finishOrderWithoutTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, finishOrderWithoutTransfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    order->finishWithoutTransfer();
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::finishOrderTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr order )
{
    METHODNAME_DEF( CSC_CorphaUC, finishOrderTransfer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString logmessage("");
    logmessage.format( "%s -> finishOrderTransfer done", getInstanceDetails().c_str() );

    try
    {
        if( m_PDX040Result )
        {
            m_CICSOrderDM->retrieve();

            domMod::corpha::ProcessOrderDM::OrderTransformer transformer( m_CSC_Logger, m_ApplConfiguration );
            domMod::corpha::recordtypes::RecordTypeCollectionPtr coll = transformer.transform( m_CICSOrderDM );

            order->finishTransfer( coll );
            m_CICSOrderDM->shutdown();

            m_CSC_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage );
        }
    }
    catch( ... )
    {
        logmessage.format( "%s -> unexpected exception in CSC_CorphaUC::finishOrderTransfer", getInstanceDetails().c_str() );
        m_CSC_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );
        throw;
    }
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
domMod::corpha::pxVerbund::OrderSelectionMode CSC_CorphaUC::getOrderSelectionMode() const
{
    METHODNAME_DEF( CSC_CorphaUC, getOrderSelectionMode );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    if( cmdLine::ORDERFILTER_ALL == m_ApplConfiguration->getOrderFilter() )
    {
        return domMod::corpha::pxVerbund::ALLORDERNUMBERS;
    }
    else if( cmdLine::ORDERFILTER_ODD == m_ApplConfiguration->getOrderFilter() )
    {
        return domMod::corpha::pxVerbund::ODDORDERNUMBERS;
    }
    else if( cmdLine::ORDERFILTER_EVEN == m_ApplConfiguration->getOrderFilter() )
    {
        return domMod::corpha::pxVerbund::EVENORDERNUMBERS;
    }
    else
    {
        return domMod::corpha::pxVerbund::ALLORDERNUMBERS;
    }
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::checkInjections() const
{
    METHODNAME_DEF( CSC_CorphaUC, checkInjections );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    if ( NULL == m_CSC_Logger.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "Logger missing! Inject Logger first!", __FILE__, __LINE__) );

    if ( NULL == m_ApplConfiguration.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "ApplConfiguration missing! Inject ApplConfiguration first!", __FILE__, __LINE__) );

    if ( NULL == m_PXVBOrderCollection.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PXVBOrderCollection missing! Inject PXVBOrderCollection first!", __FILE__, __LINE__) );

    if ( NULL == m_PXVBServiceLocator.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PXVBServiceLocator missing! Inject PXVBServiceLocator first!", __FILE__, __LINE__) );

    if( NULL == m_RemoteProcedureServiceLocator.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "RemoteProcedureServiceLocator missing! Inject RemoteProcedureServiceLocator first!", __FILE__, __LINE__) );

    if( NULL == m_PXVBTaskControl.get() )
        throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PXVBTaskControl missing! Inject PXVBTaskControl first!", __FILE__, __LINE__) );
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectPXVBServiceLocatorPtr( domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr svclocator )
{
    m_PXVBServiceLocator = svclocator;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectPXVBTaskControl( domMod::corpha::pxVerbund::IPXVBTaskControlPtr tc )
{
    m_PXVBTaskControl = tc;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectPXVBOrderCollectionPtr( domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr ordercoll )
{
    m_PXVBOrderCollection = ordercoll;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectCICSOrderDM( domMod::corpha::processOrder::ICICSOrderDMPtr cicsorder )
{
    m_CICSOrderDM = cicsorder;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectApplConfiguration( libcsc_utils::IApplConfigurationPtr applconfig )
{
    m_ApplConfiguration = applconfig;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger)
{
    m_CSC_Logger = csc_logger;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::injectRemoteProcedureServiceLocatorPtr( domMod::corpha::IRemoteProcedureServiceLocatorPtr rpsl )
{
    m_RemoteProcedureServiceLocator = rpsl;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void CSC_CorphaUC::flagExitGracefull()
{
    m_ExitGracefull = true;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
basar::VarString CSC_CorphaUC::getInstanceDetails() const
{
    METHODNAME_DEF( CSC_CorphaUC, getInstanceDetails );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString retval("");
    retval.format( "<%d>|<%d>|", m_ApplConfiguration->getBranchNo(), m_CurrentOrder );
    return retval;
}
//-------------------------------------------------------------------------------------------//


} //namespace useCase
} //namespace csc_corpha
