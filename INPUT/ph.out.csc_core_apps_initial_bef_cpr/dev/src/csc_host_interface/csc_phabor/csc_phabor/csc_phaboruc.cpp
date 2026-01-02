//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief csc_phabor's sole usecase
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

//lib includes
#include "cmndm.h"
#include "csc_phaboruc.h"
#include <libbasarappl.h>
#include <libbasarcmnutil_logging.h>
#include <icsc_logger.h>
#include <iremoteprocedurecallerptr.h>
#include <iremoteprocedurecaller.h>
#include <iapplconfiguration.h>
#include <remoteprocedurecaller.h>
#include <remoteprocedureresult.h>
#include <dbconnectionbase.h>
#include <dbconnectionbaseptr.h>
#include <accessorexecutionexception.h>


//exceptions
#include <invalidstatuschangeexception.h>
#include <missingdependencyinjectionexception.h>

// project includes
#include "cicsbatchorderdm.h"
#include "pdx050remoteprocedure.h"
#include "pdx050remoteprocedure_definitions.h"
#include "batchordertransformer.h"
#include "property_definitions.h"
#include "batchorderdm.h"
#include "itransferkeygetterptr.h"
#include "itransferkeygetter.h"
#include "dkbazkacc_definitions.h"
#include "dkbazpacc_definitions.h"
#include "cscbatchorderdm.h"
#include "orderprocessingexception.h"
#include "icsc_heartbeat.h"

namespace csc_phabor
{
namespace useCase
{

//-------------------------------------------------------------------------------------------------------------------//
CSC_PhaborUC::CSC_PhaborUC() 
: m_ExitGracefull(false), m_IsTesting(false), m_Transfer(false), m_Process(false)
{
}

//-------------------------------------------------------------------------------------------------------------------//
CSC_PhaborUC::~CSC_PhaborUC()
{
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::flagExitGracefull()
{
	m_ExitGracefull = true;
}

void CSC_PhaborUC::flagTesting()
{
	m_IsTesting = true;
}

void CSC_PhaborUC::flagTransfer()
{
	m_Transfer = true;
}

void CSC_PhaborUC::flagProcess()
{
	m_Process = true;
}

void CSC_PhaborUC::receiveSignal(int signal)
{
    basar::VarString msg;
    msg.format("CSC_PhaborUC got signal %d", signal);

    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
    
    if (SIGTERM == signal || SIGINT == signal)
    {
        flagExitGracefull();
    }
}

//-------------------------------------------------------------------------------------------------------------------//
basar::appl::EventReturnStruct CSC_PhaborUC::run()
{
	METHODNAME_DEF( CSC_PhaborUC, run );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	checkInjections();

	m_HeartBeat->emitHeartBeat();

	if (!m_ExitGracefull && m_Transfer)
	{
		basar::Int32 processedDatasets = 0;
		do
		{
			processedDatasets = callRemoteProcedure();
		}
		while (processedDatasets > 0 && !m_IsTesting);

		transferCICSBatchOrders();
	}


	if (!m_ExitGracefull && m_Process)
	{
		processCICSBatchOrders();
	}

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "UC exiting");

	return basar::appl::EventReturnStruct();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSC_PhaborUC::callRemoteProcedure()
{	
	METHODNAME_DEF( CSC_PhaborUC, callRemoteProcedure );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	basar::Int32 datasetsProcessed = 0;
	try
	{
		m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "calling remote procedure");

		libcsc_utils::RemoteProcedureResult rpRes = m_pdx050caller->call();
		if (!rpRes.m_Success)
		{
			m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "pdx050call failed", rpRes.m_InfoMessage);
		}

		datasetsProcessed = rpRes.m_DatasetsProcessed;

		std::stringstream s;
		s << datasetsProcessed << " datasets processed";
		BLOG_INFO(m_CSC_Logger->getLogger(), s.str());
	}
	catch(libcsc_utils::MissingDependencyInjectionException& ex)
	{
		m_CSC_Logger->logBasarException("text missing remote ex", ex);
	}
	catch(basar::Exception& ex)
	{
		m_CSC_Logger->logBasarException("text caught basar exception during RPC", ex);
	}
	catch(...)
	{
		m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "text caught generic exception during RPC");
	}

	return datasetsProcessed;
}

//-------------------------------------------------------------------------------------------------------------------//
void  CSC_PhaborUC::logAccessors( const basar::VarString& logMsg )
{
	METHODNAME_DEF( CSC_PhaborUC, logAccessors );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, 
		"head acc " + logMsg + ": ", 
		basar::db::aspect::Manager::getInstance().getAccessorDefinition(lit::acc_dkbazk::ACC_DKBAZK).getAccessorName().c_str()
		) ;
	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, 
		"pos acc " + logMsg + ": ", 
		basar::db::aspect::Manager::getInstance().getAccessorDefinition(lit::acc_dkbazk::ACC_DKBAZK).getAccessorName().c_str()
		) ;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::checkInjections() const
{	
	METHODNAME_DEF( CSC_PhaborUC, checkInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if( NULL == m_pdx050caller.get() ){		
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "PDX050Caller missing! Inject PDX050Caller first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_CicsBatchOrderDMPtr.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CICSBatchOrderDMPtr missing! Inject CICSBatchOrderDM first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_IfxBatchOrderDMPtr.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "BatchOrderDMPtr missing! Inject (IFX) BatchOrderDM first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_CscBatchOrderDMPtr.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CSCBatchOrderDMPtr missing! Inject CSCBatchOrderDMPtr first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_BatchOrderTransformer.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "BatchOrderTransformer missing! Inject BatchOrderTransformer first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_CSC_Logger.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CSC_Logger missing! Inject CSC_Logger first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_HeartBeat.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "ICSC_HeartBeatPtr missing! Inject ICSC_HeartBeatPtr first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_AppSession.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "AppSession missing! Inject AppSession first!", __FILE__, __LINE__) );
	}
	if ( NULL == m_ApplConfiguration.get() ){
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "AppConfig missing! Inject AppConfig first!", __FILE__, __LINE__) );
	}
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectPDX050Caller(libcsc_utils::IRemoteProcedureCallerPtr pdx050caller)
{
	m_pdx050caller = pdx050caller;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectCICSBatchOrderDMPtr(domMod::batchOrder::preparation::CICSBatchOrderDMPtr cicsBatchOrderDMPtr)
{
	m_CicsBatchOrderDMPtr = cicsBatchOrderDMPtr;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectIFXBatchOrderDMPtr (domMod::batchOrder::processing::BatchOrderDMPtr ifxBatchOrderDMPtr )
{
	m_IfxBatchOrderDMPtr = ifxBatchOrderDMPtr;
}
//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectCSCBatchOrderDMPtr ( domMod::batchOrder::processing::CSCBatchOrderDMPtr cscBatchOrderDMPtr )
{
	m_CscBatchOrderDMPtr = cscBatchOrderDMPtr;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectTransferKeyGetterPtr(domMod::batchOrder::util::ITransferKeyGetterPtr transferKeyGetter )
{
	m_TransferKeyGetter = transferKeyGetter;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectInitParamsDMPtr(domMod::InitParamsDMPtr initParamsDM )
{
	m_InitParamsDM = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectBatchOrderTransformer (domMod::batchOrder::core::BatchOrderTransformerPtr batchOrderTransformer)
{
	m_BatchOrderTransformer = batchOrderTransformer;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger)
{
	m_CSC_Logger = csc_logger;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectHeartBeat(csc_phabor::ICSC_HeartBeatPtr heartBeat)
{
	m_HeartBeat = heartBeat;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectAppSession(csc_phabor::AppSessionPtr appSession)
{
	m_AppSession = appSession;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::injectAppConfig(libcsc_utils::IApplConfigurationPtr appConfig)
{
	m_ApplConfiguration = appConfig;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::transferCICSBatchOrders()
{
	METHODNAME_DEF( CSC_PhaborUC, transferCICSBatchOrders );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "transfering CICS batchorders");

	domMod::batchOrder::core::BatchOrderCollectionPtr cicsOrdColl;
	domMod::batchOrder::core::BatchOrderPtr	cicsOrder;

	try {
		cicsOrdColl = findOpenCicsOrders();
		cicsOrder   = cicsOrdColl->getFirst();
	} catch (::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("text accessor exec exception", ex);
	}
	
	for ( ; !cicsOrder->getOrderHead().isEnd(); cicsOrder = cicsOrdColl->getNext() ) {

		try	{
			domMod::batchOrder::core::BatchOrderPtr ifxOrder = getEmptyIfxOrder();

			m_BatchOrderTransformer->transformCics2Ifx( cicsOrder, ifxOrder );
			m_IfxBatchOrderDMPtr->saveBatchOrder( ifxOrder );

			// set cics order status to transfered so it wont be selected anymore
			setCicsStatusTransfered( cicsOrder );

		} catch(...) {
			m_CSC_Logger->logGenericException("error while transfering cics order to ifx", cicsOrder);		
		} // try

	} // for

	m_CicsBatchOrderDMPtr->clearTables(); 
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::processCICSBatchOrders()
{
	METHODNAME_DEF( CSC_PhaborUC, transferCICSBatchOrders );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "processing CICS batchorders");

	domMod::batchOrder::core::BatchOrderCollectionPtr ifxOrdColl;
	try
	{
		ifxOrdColl = findOpenIfxOrders();
	}
	catch(::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("text accessor exec exception", ex);
		throw; // leave this method because ifxOrdColl is uninitialized
	}

	domMod::batchOrder::core::BatchOrderPtr	ifxOrder   = ifxOrdColl->getFirst();
	for ( ; !ifxOrder->getOrderHead().isEnd(); ifxOrder = ifxOrdColl->getNext() )
	{		
		try	
		{
			if ( m_CscBatchOrderDMPtr->isProcessable( ifxOrder ) )
			{
				m_CscBatchOrderDMPtr->saveBatchOrder( ifxOrder );
			}
		} 
		catch ( csc_phabor::exception::OrderProcessingException& ex ) 
		{
			m_CSC_Logger->logBasarException("error while processing ifx order", ex, ifxOrder);	
		} 
		catch(libcsc_utils::InvalidStatusChangeException& ex) 
		{
			m_CSC_Logger->logBasarException("text invalid status change exception", ex);
		} 
		catch(...) 
		{
			m_CSC_Logger->logGenericException("error while processing ifx order", ifxOrder);		
		} // try

	} // for

}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr CSC_PhaborUC::getEmptyIfxOrder()
{
	METHODNAME_DEF( CSC_PhaborUC, getEmptyIfxOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_IfxBatchOrderDMPtr->getEmptyBatchOrder();
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderPtr CSC_PhaborUC::getEmptyPxvbOrder()
{
	METHODNAME_DEF( CSC_PhaborUC, getEmptyPxvbOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_IfxBatchOrderDMPtr->getEmptyBatchOrder(); // replace with pxvb dm
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderCollectionPtr CSC_PhaborUC::findOpenCicsOrders()
{
	METHODNAME_DEF( CSC_PhaborUC, findOpenCicsOrders );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_CicsBatchOrderDMPtr->findOpenOrders( getLastKey(), m_InitParamsDM->m_Branchno ); 
}

//-------------------------------------------------------------------------------------------------------------------//
domMod::batchOrder::core::BatchOrderCollectionPtr CSC_PhaborUC::findOpenIfxOrders()
{
	METHODNAME_DEF( CSC_PhaborUC, findOpenIfxOrders );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_IfxBatchOrderDMPtr->findOpenOrders( 0, m_InitParamsDM->m_Branchno ); 
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSC_PhaborUC::getLastKey()
{
	METHODNAME_DEF( CSC_PhaborUC, getLastKey );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::Int32 key = 0;

	try
	{
        key = m_TransferKeyGetter->getLastKey( m_InitParamsDM->m_Branchno );
	}
	catch(::util::AccessorExecutionException& ex)
	{
		m_CSC_Logger->logBasarException("text accessor exec exception", ex);
	}

	return key;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSC_PhaborUC::setCicsStatusTransfered( domMod::batchOrder::core::BatchOrderPtr cicsOrder )
{
	METHODNAME_DEF( CSC_PhaborUC, setCicsStatusTransfered );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	// not done by dm anymore, status will be set by remoteprocedure pdx050
	//m_CicsBatchOrderDMPtr->setStatusTransfered( cicsOrder->getOrderHead()  ); 

	// function could be better but time is running out :( sorry steffen

	basar::Date updateDate = cicsOrder->getOrderHead().getInt32( properties::dkbazk::KBAZKDX05DATE );;
	basar::Int32 updateOffsetOrder = cicsOrder->getOrderHead().getInt32( properties::dkbazk::RECORDOFFSET );

	// get remoteprocedure
	libcsc_utils::IRemoteProcedureCallerPtr	pdx050CallerPtr ( new libcsc_utils::RemoteProcedureCaller(
																	m_AppSession->m_TCAConnection2->getCurrentConnection(),
																	m_CSC_Logger
															   ));

	libcsc_utils::IRemoteProcedurePtr pdx050 ( new domMod::batchOrder::preparation::PDX050RemoteProcedure( 
													m_ApplConfiguration->getBranchNo(), 
													m_ApplConfiguration->getApplicationName(), 
													domMod::batchOrder::preparation::PDX050UPDATEYES, 
													updateDate,
													updateOffsetOrder 
													) );

	pdx050CallerPtr->injectRemoteProcedure(pdx050);
	//test
	cicsOrder->getOrderPositions().clear();
	pdx050CallerPtr->call();
}

} //namespace useCase
}//namespace csc_phabor
