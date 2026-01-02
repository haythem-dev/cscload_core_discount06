//--------------------------------------------------------------------------------------------------//
/*! \file		csc_phaborappl.cpp
 *  \brief      application controller 
 *  \author     Julian Machata
 *  \date       20.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_phaborappl.h"
#include "csc_phaborcmdlineevaluatorptr.h"
#include "csc_phaborcmdlineevaluator.h"
#include "csc_phabor_definitions.h"
#include "csc_phaboruc.h"
#include "appsession.h"
#include "pdx050remoteprocedure.h"
#include "pdx050remoteprocedure_definitions.h"
#include "csc_phaborappinitializer.h"
#include "ipxvbservicelocator.h"

#include "pxvbcomponentmanager.h"

// lib includes
#include <iapplconfiguration.h>
#include <iremoteprocedurecaller.h>
#include <icsc_logger.h>
#include <csc_logger.h>
#include <ifxconnection.h>
#include <tcaconnection.h>
#include <dbconnectionbase.h>

// Exceptions
#include <softkillexception.h>
#include <appinitializerexception.h>
#include <xmlreaderexception.h>
#include <missingdependencyinjectionexception.h>
#include <cmdlineexception.h>
#include <remoteprocedurecaller.h>
#include <setupsignalhandlingexception.h>

#include <persistence/connectionptr.h>
#include <persistence/connection.h>
//--------------------------------------------------------------------------------------------------//
// extern definition section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace cmnutil
	{
		using csc_phabor::CSC_PhaborApplBase;

		template <>
		typename Singleton< CSC_PhaborApplBase >::InstancePtr &
			Singleton< CSC_PhaborApplBase >::inst()
		{
			// the one and only instance
			static InstancePtr s_Inst;

			return s_Inst;
		}
	}
}

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{

//--------------------------------------------------------------------------------------------------//
// static functions section
//--------------------------------------------------------------------------------------------------//

#ifndef WIN32
#include <unistd.h>

// there is no Sleep() function available in non windows systems
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

	//----------------------------------------------------------------------------------------------//
	CSC_PhaborApplBase::CSC_PhaborApplBase() :
		m_AppInitializer (cmdLine::CSC_PhaborAppInitializerPtr(new cmdLine::CSC_PhaborAppInitializer())),
		m_Logger( libcsc_utils::LoggerPool::LoggerCSC ),
		m_ExitGracefull(false), 
		m_TestingMode(false)
	{  
		METHODNAME_DEF( CSC_PhaborApplBase, CSC_PhaborApplBase ) 
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	//----------------------------------------------------------------------------------------------//
	/*!	\throw  no-throw */
	CSC_PhaborApplBase::~CSC_PhaborApplBase()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, ~CSC_PhaborApplBase ) 
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	//----------------------------------------------------------------------------------------------//
	/*!	\retval true if initialization was ok */
	void CSC_PhaborApplBase::init( int argc, char *argv[] )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, init ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		try
		{
			cmdLine::CSC_PhaborCmdLineEvaluatorPtr cmdEvalPtr (getNewCmdLineEvaluator( argc, argv ));
			cmdEvalPtr->evaluate();
			
			m_AppInitializer->setAppArgs( cmdEvalPtr );
			m_AppInitializer->init();
			       
			initSession( m_AppInitializer );

			m_TestingMode = m_ApplConfiguration->isTestingSet() | cmdEvalPtr->isTestingSet();
			if (m_TestingMode)
				m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "testing mode requested, stopping after one cycle");

			m_TransferMode = cmdEvalPtr->isTransferSet();
			m_ProcessMode  = cmdEvalPtr->isProcessSet();
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
	
	//----------------------------------------------------------------------------------------------//
	/*!	\throw  no-throw   */
	basar::appl::EventReturnStruct CSC_PhaborApplBase::run()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, run ) 
		BLOG_TRACE_METHOD( m_Logger, fun );
	    
		try
		{  
				m_SignalHandler.setupSignalHandling();
				m_SignalHandler.registerSignalReceiver(*this);
		}
		catch(libcsc_utils::SetupSignalHandlingException& ex)
		{
				m_CSC_LoggerPtr->logBasarException("error setting up signal handling", ex);
				throw ex;
		}
		catch(...)
		{
				m_CSC_LoggerPtr->log(log4cplus::ERROR_LOG_LEVEL, "generic error setting up signal handling");
		}

		try 
		{
			connect();
			createComponents();

			while( !m_ExitGracefull ){			
				
				// check if TCA & IFX connections are OK, connect if connections are not available
				if( !checkConnections() ){
					reconnect();
				}			

				runCscPhabor();
				processingSleep();
				
				if (m_TestingMode){
					m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text exiting - testing mode");
					break;
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

	//----------------------------------------------------------------------------------------------//
	basar::appl::EventReturnStruct CSC_PhaborApplBase::runCscPhabor()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, runCSC_PhaborUC ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text calling run of UC");
		return m_CSC_PhaborUC.run();
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, establishConnection ) 
		BLOG_TRACE_METHOD( m_Logger, fun );
		
		basar::Int32 currentTries(0);

		//while(!dbconn->isOpen() && !m_ExitGracefull)
		while(!dbconn->isValid() && !m_ExitGracefull)
		{
			// \TODO: Softkill behandeln -> throw SoftKillException();

			establishConnection(dbconn);

			if( dbconn->isValid() ){
				break;
			}

			// count connection tries
			++currentTries;

			// send warning if connect fails only for the first trial
			if( 1 == currentTries )	{
				logConnectionEstablishFail( dbconn, currentTries, log4cplus::WARN_LOG_LEVEL );
			}

			// send error if number of failed retries reached the max
			if( maxRetries == currentTries ) {
				logConnectionEstablishFail( dbconn, currentTries, log4cplus::ERROR_LOG_LEVEL );
				currentTries = 0;
			}

			waitRetries(secBetweenRetries);
		}
	}

	//----------------------------------------------------------------------------------------------//
	//!< \brief establish the given connection without any retry handling
	void CSC_PhaborApplBase::establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, establishConnection ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		// try to connect to connection
		try
		{
			dbconn->connect();
		}
		catch(basar::Exception& ex)
		{
			m_CSC_LoggerPtr->logBasarException("text exception during dbConnect", ex, m_ApplConfiguration);
		}
	}

	//----------------------------------------------------------------------------------------------//
	//!< \brief logging fail of establishing connection
	void CSC_PhaborApplBase::logConnectionEstablishFail( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 numberOfTrials, log4cplus::LogLevel logLevel )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, logConnectionEstablishFail ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		basar::VarString logmessage = "";
		logmessage.format( "connection to database %s %s could not be established after %d retries"
							, dbconn->getCurrentConnection().getDbInfo().dbServer.c_str()
							, dbconn->getCurrentConnection().getDbInfo().database.c_str()
							, numberOfTrials);
		m_CSC_LoggerPtr->log(logLevel, logmessage);

		// \TODO: ERR email
	}

	//----------------------------------------------------------------------------------------------//
	bool CSC_PhaborApplBase::checkConnections()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, checkConnections )
		BLOG_TRACE_METHOD( m_Logger, fun );

		bool retval = m_AppSession->m_IFXConnection->isOpen();

		if (!m_TransferMode){
			return retval;
		}

		retval = m_AppSession->m_TCAConnection1->isValid() && retval;
		retval = m_AppSession->m_TCAConnection2->isValid() && retval;

		return retval;
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::connect()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, connect )
		BLOG_TRACE_METHOD( m_Logger, fun );
		
		// connect to IFX
		if( !m_AppSession->m_IFXConnection->isValid() )
		{
			establishConnection( m_AppSession->m_IFXConnection,
								 m_ApplConfiguration->getIFXConnectionRetries(),
								 m_ApplConfiguration->getIFXConnectionWaitBeforeRetry()
							   );
		}

		if (!m_TransferMode){
			return;
		}

		// connect to TCA1
		if( !m_AppSession->m_TCAConnection1->isValid() )
		{
			establishConnection( m_AppSession->m_TCAConnection1, 
								 m_ApplConfiguration->getTCAConnectionRetries(),
								 m_ApplConfiguration->getTCAConnectionWaitBeforeRetry()
							   );
		}
		// connect to TCA2
		if( !m_AppSession->m_TCAConnection2->isValid() )
		{
			establishConnection( m_AppSession->m_TCAConnection2,
								 m_ApplConfiguration->getTCAConnectionRetries(),
								 m_ApplConfiguration->getTCAConnectionWaitBeforeRetry()
							   );
		}
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::reconnect()
	{
		METHODNAME_DEF( CSC_PhatraApplBase, reconnect ) 
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

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::logConnectionStatus()
	{
		METHODNAME_DEF( CSC_PhatraApplBase, logConnectionStatus ) 
		BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

		//get status of components
		bool statusCICSBatchOrderDM			= (0 == m_CICSBatchOrderDM.get());
		bool statusCICSBatchOrderHeadDM		= (0 == m_CICSBatchOrderHeadDM.get());
		bool statusCICSBatchOrderPosDM		= (0 == m_CICSBatchOrderPosDM.get());
		bool statusBatchOrderDM				= (0 == m_BatchOrderDM.get());
		bool statusBatchOrderHeadDM			= (0 == m_BatchOrderHeadDM.get());
		bool statusBatchOrderPosDM			= (0 == m_BatchOrderPosDM.get());
		bool statusCSCBatchOrderPosDM		= (0 == m_CSCBatchOrderPosDM.get());
		bool statusCSCBatchOrderHeadDM		= (0 == m_CSCBatchOrderHeadDM.get());

		bool statusTCAConnection = (0 ==  m_AppSession->m_TCAConnection1.get());
		bool statusTCAConnection2 = (0 ==  m_AppSession->m_TCAConnection2.get());
		bool statusIFXConnection = (0 == m_AppSession->m_IFXConnection.get());

		std::ostringstream os;

		os << "status of components:\n";
		os << "CICSBatchOrderDM: " << std::boolalpha <<		statusCICSBatchOrderDM			<< "\n";
		os << "CICSBatchOrderHeadDM: " << std::boolalpha <<	statusCICSBatchOrderHeadDM	 << "\n";
		os << "CICSBatchOrderPosDM: " << std::boolalpha <<	statusCICSBatchOrderPosDM			<< "\n";
		os << "BatchOrderDM: " << std::boolalpha <<			statusBatchOrderDM				 << "\n";
		os << "BatchOrderHeadDM: " << std::boolalpha <<		statusBatchOrderHeadDM				<< "\n";
		os << "BatchOrderPosDM: " << std::boolalpha <<		statusBatchOrderPosDM			 << "\n";
		os << "CSCBatchOrderPosDM: " << std::boolalpha <<		statusCSCBatchOrderPosDM			 << "\n";
		os << "CSCBatchOrderHeadDM: " << std::boolalpha <<	statusCSCBatchOrderHeadDM			 << "\n";
		os << "TCAConnection 1: " << std::boolalpha << statusTCAConnection << "\n";
		os << "TCAConnection 2: " << std::boolalpha << statusTCAConnection2 << "\n";
		os << "IFXConnection: " << std::boolalpha << statusIFXConnection << "\n";

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, os.str().c_str());
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::resetConnections()
	{
		METHODNAME_DEF( CSC_PhatraApplBase, resetConnections ) 
		BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

		try
		{
			m_AppSession->m_TCAConnection1->disconnect();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}
		
		try
		{
			m_AppSession->m_TCAConnection1.reset();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during reset of tca connection, ignored");
		}

		try
		{
			m_AppSession->m_TCAConnection2->disconnect();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}
		
		try
		{
			m_AppSession->m_TCAConnection2.reset();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during reset of tca connection, ignored");
		}

		try
		{
			m_AppSession->m_IFXConnection->disconnect();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of ifx connection, ignored");
		}

		try
		{
			m_AppSession->m_IFXConnection.reset();
		}
		catch(...)
		{
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during reset of ifx connection, ignored");
		}

	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::resetDMs()
	{
		METHODNAME_DEF( CSC_PhatraApplBase, resetDMs ) 
		BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

		try {
			if (0 != m_CICSBatchOrderDM.get()){
				m_CICSBatchOrderDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{
			if (0 != m_CICSBatchOrderHeadDM.get()){
				m_CICSBatchOrderHeadDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{
			if (0 != m_CICSBatchOrderPosDM.get()){
				m_CICSBatchOrderPosDM.reset();
			}

		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{
			if (0 != m_BatchOrderDM.get()){
				m_BatchOrderDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{

			if (0 != m_BatchOrderHeadDM.get()){
				m_BatchOrderHeadDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{
			if (0 != m_BatchOrderPosDM.get()){
				m_BatchOrderPosDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try	{
			if (0 != m_CSCBatchOrderPosDM.get()){
				m_CSCBatchOrderPosDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}

		try {

			if (0 != m_CSCBatchOrderHeadDM.get()){
				m_CSCBatchOrderHeadDM.reset();
			}
		}
		catch(...){
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
		}
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::disconnect()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, disconnect ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		// disconnect TCA
		if (m_AppSession->m_TCAConnection1->isOpen())
		{
			m_AppSession->m_TCAConnection1->disconnect();
		}

		// disconnect TCA 2
		if (m_AppSession->m_TCAConnection2->isOpen())
		{
			m_AppSession->m_TCAConnection2->disconnect();
		}

		// disconnect IFX
		if(m_AppSession->m_IFXConnection->isOpen())
		{
			m_AppSession->m_IFXConnection->disconnect();
		}
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::createComponents()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, createComponents ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components...");

		try
		{	

			m_PDX050												= getNewPDX050RemoteProcedure( getBranchNo(), getApplicationName() ) ;
			m_PDX050CallerPtr										= getNewRemoteProcedureCaller();
			m_CICSBatchOrderHeadDM									= getNewCICSBatchOrderHeadDM();
			m_CICSBatchOrderPosDM									= getNewCICSBatchOrderPosDM();
			m_CICSBatchOrderDM										= getNewCICSBatchOrderDM();
			m_BatchOrderHeadDM										= getNewBatchOrderHeadDM();
			m_BatchOrderPosDM										= getNewBatchOrderPosDM();
			m_BatchOrderDM											= getNewBatchOrderDM();
			m_InitParamsDM											= getNewInitParamsDM();
			m_BatchOrderTransformer									= getNewBatchOrderTransformer();
			m_CSCBatchOrderHeadDM									= getNewCSCBatchOrderHeadDM();
			m_CSCBatchOrderPosDM									= getNewCSCBatchOrderPosDM();
			m_CSCBatchOrderDM										= getNewCSCBatchOrderDM();
			
			doInits();
			doInjects();

			if (m_TestingMode)
				m_CSC_PhaborUC.flagTesting();
		
			if (m_ProcessMode)
				m_CSC_PhaborUC.flagProcess();

			if (m_TransferMode)
				m_CSC_PhaborUC.flagTransfer();
		}
		catch(basar::Exception& ex)
		{
			m_CSC_LoggerPtr->logBasarException("text exception during createComponents", ex);
			throw ex;
		}

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components finished");
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::initSession( const cmdLine::CSC_PhaborAppInitializerPtr appInitializer )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, initSession ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		const basar::db::sql::DatabaseInfo& ifxdatabaseinfo = appInitializer->getIFXConnConfiguration();
		const basar::db::sql::DatabaseInfo& tcadatabaseinfo = appInitializer->getTCAConnConfiguration();

		m_AppSession = AppSessionPtr( new AppSession(	
														//appInitializer.getAppArgs(),
														libBatch::dbConnection::DBConnectionBasePtr(new libcsc_utils::dbConnection::IfxConnection(ifxdatabaseinfo)),
														libBatch::dbConnection::DBConnectionBasePtr(new libcsc_utils::dbConnection::TCAConnection(tcadatabaseinfo)),
														libBatch::dbConnection::DBConnectionBasePtr(new libcsc_utils::dbConnection::TCAConnection(tcadatabaseinfo))
													) 
									);

		m_ApplConfiguration = appInitializer->getAppConfiguration();
		m_CSC_LoggerPtr = appInitializer->getCSCLogger();
	}

	//----------------------------------------------------------------------------------------------//
	/*!	\throw  no-throw */
	void CSC_PhaborApplBase::shutdown()
	{	
		METHODNAME_DEF( CSC_PhaborApplBase, shutdown )
		BLOG_TRACE_METHOD( m_Logger, fun );
		
		m_CICSBatchOrderDM->shutdown();
		m_CICSBatchOrderHeadDM->shutdown();
		m_CICSBatchOrderPosDM->shutdown();
		m_BatchOrderDM->shutdown();
		m_BatchOrderHeadDM->shutdown();
		m_BatchOrderPosDM->shutdown();
		m_CSCBatchOrderPosDM->shutdown(); 
		m_CSCBatchOrderHeadDM->shutdown(); 

		disconnect();
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::processingSleep()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, processingSleep ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text run of UC returned, going to sleep");

		Sleep(m_ApplConfiguration->getPollingInterval());

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text woke up");
	}

	void CSC_PhaborApplBase::receiveSignal(int signal)
	{
		basar::VarString msg;
		msg.format("csc_PhaborApplBase got signal %d", signal);

		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, msg);
		if (SIGTERM == signal || SIGINT == signal)
		{
			m_ExitGracefull = true;
		}
	}

	//----------------------------------------------------------------------------------------------//
	void CSC_PhaborApplBase::waitRetries(basar::Int32 time)
	{
		METHODNAME_DEF( CSC_PhaborApplBase, waitRetries ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		Sleep(time);
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new InitParamsDM
	domMod::InitParamsDMPtr CSC_PhaborApplBase::getNewInitParamsDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewInitParamsDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::InitParamsDMPtr( new domMod::InitParamsDM ( getBranchNo(), "" ));
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new cmdLineEvaluator with given args
	cmdLine::CSC_PhaborCmdLineEvaluatorPtr CSC_PhaborApplBase::getNewCmdLineEvaluator( int argc, char *argv[] )
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCmdLineEvaluator ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return cmdLine::CSC_PhaborCmdLineEvaluatorPtr( new cmdLine::CSC_PhaborCmdLineEvaluator( ::libBatch::cmdLine::CmdLineConfiguration( argc, argv ) ) );
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new PDX050RemoteProcedure with given args
	libcsc_utils::IRemoteProcedurePtr CSC_PhaborApplBase::getNewPDX050RemoteProcedure( basar::Int16 branchNo, basar::VarString applicationName )
	{
		METHODNAME_DEF( getNewPDX050RemoteProcedure, getNewPDX050RemoteProcedure ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return libcsc_utils::IRemoteProcedurePtr( new domMod::batchOrder::preparation::PDX050RemoteProcedure( branchNo, applicationName, domMod::batchOrder::preparation::PDX050UPDATENO, 0 ,0 ) );
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new RemoteProcedureCaller
	libcsc_utils::IRemoteProcedureCallerPtr CSC_PhaborApplBase::getNewRemoteProcedureCaller()
	{
		METHODNAME_DEF( getNewPDX050RemoteProcedure, getNewRemoteProcedureCaller ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return libcsc_utils::IRemoteProcedureCallerPtr( 
			new libcsc_utils::RemoteProcedureCaller(m_AppSession->m_TCAConnection1->getCurrentConnection(), m_CSC_LoggerPtr ));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new CICSBatchOrderHeadDM
	domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr CSC_PhaborApplBase::getNewCICSBatchOrderHeadDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCICSBatchOrderHeadDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr( 
			new domMod::batchOrder::preparation::CICSBatchOrderHeadDM(m_AppSession->m_TCAConnection1->getCurrentConnection(), m_CSC_LoggerPtr));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new CICSBatchOrderPosDM
	domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr CSC_PhaborApplBase::getNewCICSBatchOrderPosDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCICSBatchOrderPosDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr( 
			new domMod::batchOrder::preparation::CICSBatchOrderPosDM(m_AppSession->m_TCAConnection2->getCurrentConnection(), m_CSC_LoggerPtr));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new CICSBatchOrderPosDM
	domMod::batchOrder::preparation::CICSBatchOrderDMPtr CSC_PhaborApplBase::getNewCICSBatchOrderDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCICSBatchOrderDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::preparation::CICSBatchOrderDMPtr( 
			new domMod::batchOrder::preparation::CICSBatchOrderDM( m_CSC_LoggerPtr));
	}

		//----------------------------------------------------------------------------------------------//
	//!< creates new BatchOrderHeadDM
	domMod::batchOrder::processing::BatchOrderHeadDMPtr CSC_PhaborApplBase::getNewBatchOrderHeadDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewBatchOrderHeadDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::processing::BatchOrderHeadDMPtr( 
			new domMod::batchOrder::processing::BatchOrderHeadDM(m_AppSession->m_IFXConnection->getCurrentConnection(), m_CSC_LoggerPtr));
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new BatchOrderPosDM
	domMod::batchOrder::processing::BatchOrderPosDMPtr CSC_PhaborApplBase::getNewBatchOrderPosDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewBatchOrderPosDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::processing::BatchOrderPosDMPtr( 
			new domMod::batchOrder::processing::BatchOrderPosDM(m_AppSession->m_IFXConnection->getCurrentConnection(), m_CSC_LoggerPtr));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new BatchOrderPosDM
	domMod::batchOrder::processing::BatchOrderDMPtr CSC_PhaborApplBase::getNewBatchOrderDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewBatchOrderDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::processing::BatchOrderDMPtr( 
			new domMod::batchOrder::processing::BatchOrderDM( m_CSC_LoggerPtr, m_BatchOrderHeadDM, m_BatchOrderPosDM));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< creates new CSCBatchOrderHeadDM
	domMod::batchOrder::processing::CSCBatchOrderHeadDMPtr CSC_PhaborApplBase::getNewCSCBatchOrderHeadDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCSCBatchOrderHeadDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );
 
		return domMod::batchOrder::processing::CSCBatchOrderHeadDMPtr( 
			new domMod::batchOrder::processing::CSCBatchOrderHeadDM(m_CSC_LoggerPtr));
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new CSCBatchOrderPosDM
	domMod::batchOrder::processing::CSCBatchOrderPosDMPtr CSC_PhaborApplBase::getNewCSCBatchOrderPosDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCSCBatchOrderPosDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::processing::CSCBatchOrderPosDMPtr( 
			new domMod::batchOrder::processing::CSCBatchOrderPosDM(m_CSC_LoggerPtr));
	}

	//----------------------------------------------------------------------------------------------//
	//!< creates new CSCBatchOrderDM
	domMod::batchOrder::processing::CSCBatchOrderDMPtr CSC_PhaborApplBase::getNewCSCBatchOrderDM()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewCSCBatchOrderDM ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::processing::CSCBatchOrderDMPtr( 
					new domMod::batchOrder::processing::CSCBatchOrderDM( m_CSC_LoggerPtr ) );		
	}

	//----------------------------------------------------------------------------------------------//
	domMod::batchOrder::core::BatchOrderTransformerPtr CSC_PhaborApplBase::getNewBatchOrderTransformer()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getNewBatchOrderTransformer ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return domMod::batchOrder::core::BatchOrderTransformerPtr( 
			new domMod::batchOrder::core::BatchOrderTransformer( m_CSC_LoggerPtr));
	}	

	//----------------------------------------------------------------------------------------------//
	//!< \brief get branchno from ApplConfiguration
	basar::Int16 CSC_PhaborApplBase::getBranchNo() const 
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getBranchNo ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return m_ApplConfiguration->getBranchNo();
	}

	//----------------------------------------------------------------------------------------------//
	//!< \brief get ApplicationName from ApplConfiguration
	const basar::VarString CSC_PhaborApplBase::getApplicationName() const
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getApplicationName ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		return m_ApplConfiguration->getApplicationName();
	}

	//----------------------------------------------------------------------------------------------//
	//!< \brief initialize dms
	void CSC_PhaborApplBase::doInits() 
	{
		METHODNAME_DEF( CSC_PhaborApplBase, doInits ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		m_CICSBatchOrderHeadDM->init ( m_InitParamsDM ); 
		m_CICSBatchOrderPosDM->init  ( m_InitParamsDM ); 
		m_BatchOrderHeadDM->init	 ( m_InitParamsDM ); 
		m_BatchOrderPosDM->init		 ( m_InitParamsDM ); 
		m_CICSBatchOrderDM->init	 ( domMod::batchOrder::core::BatchOrderDMBaseInitStruct ( m_CICSBatchOrderHeadDM,
																								m_CICSBatchOrderPosDM,
																								m_CICSBatchOrderDM )); 
		m_BatchOrderDM->init	 ( domMod::batchOrder::core::BatchOrderDMBaseInitStruct		( m_BatchOrderHeadDM,
																								m_BatchOrderPosDM,
																								m_BatchOrderDM )); 
	}

	//----------------------------------------------------------------------------------------------//
	//!< \brief make injections for components
	void CSC_PhaborApplBase::doInjects() 
	{
		METHODNAME_DEF( CSC_PhaborApplBase, doInjects ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		m_PDX050CallerPtr->injectRemoteProcedure(m_PDX050);

		m_CSCBatchOrderDM->injectBatchOrderStatusUpdater( m_BatchOrderDM );
		m_CSCBatchOrderDM->injectCSCBatchOrderHeadDM	( m_CSCBatchOrderHeadDM );
		m_CSCBatchOrderDM->injectCSCBatchOrderPosDM		( m_CSCBatchOrderPosDM );
		m_CSCBatchOrderDM->injectPXVBSession			( getPXVBServiceLocator()->getPXVBSession()			);
		m_CSCBatchOrderDM->injectPXVBOrderTransmit		( getPXVBServiceLocator()->getPXVBOrderTransmit()	);

		m_CSCBatchOrderHeadDM->injectICSCOrderObjectGetter ( m_CSCBatchOrderDM );
		m_CSCBatchOrderPosDM->injectICSCOrderObjectGetter ( m_CSCBatchOrderDM );

		m_CSC_PhaborUC.injectPDX050Caller			( m_PDX050CallerPtr			); 
		m_CSC_PhaborUC.injectCICSBatchOrderDMPtr	( m_CICSBatchOrderDM		); 
		m_CSC_PhaborUC.injectBatchOrderTransformer	( m_BatchOrderTransformer	); 
		m_CSC_PhaborUC.injectICSC_LoggerPtr			( m_CSC_LoggerPtr			);
		m_CSC_PhaborUC.injectInitParamsDMPtr		( m_InitParamsDM			);
		m_CSC_PhaborUC.injectTransferKeyGetterPtr	( m_BatchOrderDM			);
		m_CSC_PhaborUC.injectIFXBatchOrderDMPtr		( m_BatchOrderDM			);
		m_CSC_PhaborUC.injectCSCBatchOrderDMPtr		( m_CSCBatchOrderDM			);
		m_CSC_PhaborUC.injectHeartBeat				( getHeartBeat()			);
		m_CSC_PhaborUC.injectAppSession				( m_AppSession				);
		m_CSC_PhaborUC.injectAppConfig				( m_ApplConfiguration		);

		m_CICSBatchOrderDM->injectCICSBatchOrderPosDMPtr	( m_CICSBatchOrderPosDM		);
		m_CICSBatchOrderDM->injectCICSBatchOrderHeadDMPtr	( m_CICSBatchOrderHeadDM	);

		m_SignalHandler.registerSignalReceiver(m_CSC_PhaborUC);
	}

	//----------------------------------------------------------------------------------------------//
	/*!	\throw  no-throw */
	domMod::batchOrder::pxVerbund::IPXVBServiceLocatorPtr CSC_PhaborApplBase::getPXVBServiceLocator()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getPXVBServiceLocator ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		using namespace domMod::batchOrder::pxVerbund;

		if( 0 == m_PXVBServiceLocator.get() )
		{
			PXVBComponentManager* cm = new PXVBComponentManager( m_ApplConfiguration, m_CSC_LoggerPtr );
			cm->injectCscDbConnection(
				libcsc::persistence::ConnectionPtr(
					new libcsc::persistence::Connection(m_AppSession->m_IFXConnection->getCurrentConnection().getSqlConnection()
					)
				)
			);
			m_PXVBServiceLocator = IPXVBServiceLocatorPtr( cm );
		}

		return m_PXVBServiceLocator;
	}

	//----------------------------------------------------------------------------------------------//
	/*!	\throw  no-throw */
	csc_phabor::ICSC_HeartBeatPtr CSC_PhaborApplBase::getHeartBeat()
	{
		METHODNAME_DEF( CSC_PhaborApplBase, getHeartBeat ) 
		BLOG_TRACE_METHOD( m_Logger, fun );

		if (0 == m_CSC_HeartBeat.get())
		{
			domMod::batchOrder::pxVerbund::IPXVBServiceLocatorPtr ipvbxslp = getPXVBServiceLocator();
			m_CSC_HeartBeat = 
			ICSC_HeartBeatPtr(new 
			CSC_HeartBeat(
			ipvbxslp->getPXVBSession(), m_CSC_LoggerPtr, APPLICATION_NAME, m_ApplConfiguration->getBranchNo()) );
		}

		return m_CSC_HeartBeat;
	}

} // end namespace csc_phabor

