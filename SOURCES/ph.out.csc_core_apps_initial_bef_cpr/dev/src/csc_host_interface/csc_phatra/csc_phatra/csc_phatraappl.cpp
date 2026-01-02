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
#include "csc_phatraappl.h"
#include "csc_phatraappinitializer.h"
#include "csc_phatracmdlineevaluatorptr.h"
#include "csc_phatracmdlineevaluator.h"

#include "csc_phatrauc.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include <imailptr.h>
#include <imail.h>
#include <mail.h>

#include <loggerpool.h>
#include "csc_phatra_definitions.h"
#include "appsession.h"
#include <ifxconnection.h>
#include <tcaconnection.h>

#include <iapplconfiguration.h>

// Exceptions
#include <softkillexception.h>
#include <appinitializerexception.h>
#include <xmlreaderexception.h>
#include <missingdependencyinjectionexception.h>
#include <cmdlineexception.h>
#include <mailexception.h>
#include <setupsignalhandlingexception.h>

#include <libbasarappl.h>
#include <libbasarcmnutil_logging.h>
#include <cmdlineoption_definitions.h>
#include <cmdlineparser.h>
#include "transactiondmbaseptr.h"
#include "cicspharmostransactiondm.h"
#include "cicspharmostransactionrecord.h"
#include "transactionrecordbase.h"
#include <remoteprocedureresult.h>
#include <remoteprocedurecaller.h>
#include "pdx010remoteprocedure.h"
#include "property_definitions.h"
#include "pharmostransactiondm.h"
#include "pharmostransactiondmptr.h"
#include "cicspharmostransactiondmptr.h"
#include "ctransfercscdm.h"
#include "ctransfercscdmptr.h"
#include "itransferkeygetterptr.h"
#include "itransactionrecordcreatorptr.h"
#include "irecordtypetransformercreatorptr.h"
#include "recordtypefactory.h"
#include "recordtypefactoryptr.h"
#include "irecordtypetransformerptr.h"
#include "irecordtypetransformer.h"
#include "ipxvbservicelocator.h"
#include "recordtypebase.h"
#include "recordtypebaseptr.h"
#include "irecordtypecreatorptr.h"
#include "icsc_heartbeatptr.h"
#include "icsc_heartbeat.h"
#include "csc_heartbeat.h"
#include "pxvbcomponentmanager.h"
#include "pxvbcomponentmanagerptr.h"

#include "nulltransferuc.h"
#include "pxvbcomponentmanager.h"

#include "dkbvzacc_definitions.h"
#include <libbasardbaspect.h>

//--------------------------------------------------------------------------------------------------//
// template qualification section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace cmnutil
	{
		using csc_phatra::CSC_PhatraApplBase;
		template<>
		typename Singleton<CSC_PhatraApplBase>::InstancePtr& Singleton<CSC_PhatraApplBase>::inst()
		{
			static InstancePtr s_inst;
			return s_inst;
		}
	}
}

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{

//--------------------------------------------------------------------------------------------------//
// static functions section
//--------------------------------------------------------------------------------------------------//

#ifndef WIN32
#include <unistd.h>

// there is no Sleep() function available in non windows systems
static unsigned int Sleep( unsigned int seconds )
{
	return sleep( seconds );
}
#else
#include <windows.h>
#endif

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
CSC_PhatraApplBase::CSC_PhatraApplBase()
: m_Logger( libcsc_utils::LoggerPool::LoggerCSC ), m_ExitGracefull(false), m_TestingMode(false)
{  
    METHODNAME_DEF( CSC_PhatraApplBase, CSC_PhatraApplBase ) 
	BLOG_TRACE_METHOD( m_Logger, fun );
}

/*!	\throw  no-throw */
CSC_PhatraApplBase::~CSC_PhatraApplBase()
{
}

domMod::pharmosTransaction::pxVerbund::IPXVBServiceLocatorPtr CSC_PhatraApplBase::getPXVBServiceLocator()
{
	METHODNAME_DEF( CSC_PhatraApplBase, getPXVBServiceLocator ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace domMod::pharmosTransaction::pxVerbund;

	if( 0 == m_PXVBServiceLocator.get() )
	{
        PXVBComponentManagerPtr cm( new PXVBComponentManager(m_ApplConfiguration, m_CSC_LoggerPtr) );
        cm->injectIFXConnection( m_AppSession->m_IFXConnection );
		m_PXVBServiceLocator = cm;
	}
	return m_PXVBServiceLocator;
}

csc_phatra::ICSC_HeartBeatPtr CSC_PhatraApplBase::getHeartBeat()
{
	METHODNAME_DEF( CSC_PhatraApplBase, getHeartBeat ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

    if (0 == m_CSC_HeartBeat.get())
    {
        domMod::pharmosTransaction::pxVerbund::IPXVBServiceLocatorPtr ipvbxslp = getPXVBServiceLocator();
        m_CSC_HeartBeat = ICSC_HeartBeatPtr(new CSC_HeartBeat(ipvbxslp->getPXVBSession(), ipvbxslp->getPXVBDBConnection(), m_CSC_LoggerPtr, APPLICATION_NAME, m_ApplConfiguration->getBranchNo()) );
    }

    return m_CSC_HeartBeat;
}

domMod::pharmosTransaction::core::RecordTypeFactoryPtr CSC_PhatraApplBase::getRecordTypeFactory()
{
	METHODNAME_DEF( CSC_PhatraApplBase, getRecordTypeFactory ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace domMod::pharmosTransaction::core;

	if( 0 == m_RecordTypeFactory.get() ){
		m_RecordTypeFactory = RecordTypeFactoryPtr( new RecordTypeFactory( getPXVBServiceLocator(), m_CSC_LoggerPtr ) );    
	}

	return m_RecordTypeFactory;
}

/*!	\throw  no-throw   */
basar::appl::EventReturnStruct CSC_PhatraApplBase::run()
{
	METHODNAME_DEF( CSC_PhatraApplBase, run ) 
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );
    
    try
    {
        m_SignalHandler.setupSignalHandling();
        m_SignalHandler.registerSignalReceiver(*this);
    }
    catch(libcsc_utils::SetupSignalHandlingException& ex)
    {
        m_CSC_LoggerPtr->logBasarException("error setting up signal handling", ex);
        throw;
    }
    catch(...)
    {
        m_CSC_LoggerPtr->log(log4cplus::ERROR_LOG_LEVEL, "generic error setting up signal handling");
		throw;
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
			
			// check if TCA & IFX connections are OK, connect if connections are not available
			if( !checkConnections() )
			{
				reconnect();
				//todo: reset components (they need the new connections)
				//new method: reconnect (need to get new pxvb-connection, new basar batabase conenction, new injections in use case, etc...
			}			
			
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text calling run of UC");

			m_CSC_PhatraUC.run();
			
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text run of UC returned, going to sleep");
			
			processingSleep();

			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text woke up");
			//break; // TODO Später wieder rausnehmen!

            if (m_ExitGracefull)
            {
                m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text exiting - got signal");
            }
            
            if (m_TestingMode)
            {
                m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text exiting - testing mode");
                break;
            }
		}		
		//disconnect(); // disconnect is handled by shutdown()
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

void CSC_PhatraApplBase::establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries )
{
	METHODNAME_DEF( CSC_PhatraApplBase, establishConnection )
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

	basar::Int32 currentTries = 0;

	// establish connection
	while( !dbconn->isValid() && !m_ExitGracefull)
	{
		// TODO: Softkill behandeln -> throw SoftKillException();

		// try to connect to connection
		try
		{
			dbconn->connect();
		}
		catch(basar::Exception& ex)
		{
			m_CSC_LoggerPtr->logBasarException("text exception during dbConnect", ex, m_ApplConfiguration);

			//remove throw before live
			//throw ex;
		}

		if( dbconn->isValid() )
		{
			break;
		}

		// count connection tries
		++currentTries;

		// send warning if connect fails only for the first trial
		if( 1 == currentTries )
		{
			basar::VarString logmessage = "";
			logmessage.format( "connection to database %s %s could not be established on the first try"
								, dbconn->getDBInfo().dbServer.c_str()
								, dbconn->getDBInfo().database.c_str() );
			m_CSC_LoggerPtr->log(log4cplus::WARN_LOG_LEVEL, logmessage.c_str());

		}

		if( maxRetries == currentTries )
		{
			basar::VarString logmessage = "";
			logmessage.format( "connection to database %s %s could not be established after %d retries"
								, dbconn->getDBInfo().dbServer.c_str()
								, dbconn->getDBInfo().database.c_str()
								, maxRetries);
			m_CSC_LoggerPtr->log(log4cplus::ERROR_LOG_LEVEL, logmessage.c_str());

			// TODO: ERR email

			currentTries = 0;
		}

		waitRetries(secBetweenRetries);
	}
}

void CSC_PhatraApplBase::disconnect()
{
	METHODNAME_DEF( CSC_PhatraApplBase, disconnect ) 
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

	// disconnect TCA
    if (m_AppSession->m_TCAConnection->isOpen())
    {
	    m_AppSession->m_TCAConnection->disconnect();
    }

	// disconnect IFX
    if(m_AppSession->m_IFXConnection->isOpen())
    {
	    m_AppSession->m_IFXConnection->disconnect();
    }
}

bool CSC_PhatraApplBase::checkConnections()
{
	METHODNAME_DEF( CSC_PhatraApplBase, checkConnections ) 
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

	bool retval = true;
	if (m_ApplConfiguration->isTCAActivated())
	{
		retval &= m_AppSession->m_TCAConnection->isValid();
	}
	retval &= m_AppSession->m_IFXConnection->isValid();
    return retval;
}

void CSC_PhatraApplBase::connect()
{
	METHODNAME_DEF( CSC_PhatraApplBase, connect ) 
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );

	if (m_ApplConfiguration->isTCAActivated())
	{
		// connect to TCA
		establishConnection( m_AppSession->m_TCAConnection, m_ApplConfiguration->getTCAConnectionRetries(), m_ApplConfiguration->getTCAConnectionWaitBeforeRetry() );
	}
	
	// connect to IFX
	establishConnection( m_AppSession->m_IFXConnection, m_ApplConfiguration->getIFXConnectionRetries(), m_ApplConfiguration->getIFXConnectionWaitBeforeRetry() );
}

void CSC_PhatraApplBase::reconnect()
{
	METHODNAME_DEF( CSC_PhatraApplBase, reconnect ) 
	BLOG_TRACE_METHOD( m_CSC_LoggerPtr->getLogger(), fun );
	//1) tear down old components
	//2) kill old db connections
	//3) re-establish db connections
	//4) create components anew

	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text starting reconnect...");

	try
	{
		if (0 != m_CicsPharmosTransactionDM.get())
		{
			m_CicsPharmosTransactionDM.reset();
		}
	}
	catch(...)
	{
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
	}

	try
	{
		if (0 != m_PharmosTransactionDM.get())
		{
			m_PharmosTransactionDM.reset();
		}
	}
	catch(...)
	{
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
	}

	try
	{
		if (0 != m_CTransferCscDM.get())
		{
			m_CTransferCscDM.reset();
		}
	}
	catch(...)
	{
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
	}

	try
	{
		if (m_ApplConfiguration->isTCAActivated())
		{
			m_AppSession->m_TCAConnection->disconnect();
			m_AppSession->m_TCAConnection.reset();
		}
	}
	catch(...)
	{
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
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
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text got exception during disconnect of tca connection, ignored");
	}

	//get status of components
	bool statusCicsPharmosTransactionDM = (0 == m_CicsPharmosTransactionDM.get());
	bool statusPharmosTransactionDM = (0 == m_PharmosTransactionDM.get());
	bool statusCTransferCscDM = (0 == m_CTransferCscDM.get());
	bool statusTCAConnection = (0 ==  m_AppSession->m_TCAConnection.get());
	bool statusIFXConnection = (0 == m_AppSession->m_IFXConnection.get());

	std::ostringstream os;

	os << "shutdown status of components:\n";
	os << "CicsPharmosTransactionDM: " << std::boolalpha << statusCicsPharmosTransactionDM << "\n";
	os << "PharmosTransactionDM: " << std::boolalpha << statusPharmosTransactionDM << "\n";
	os << "CTransferCscDM: " << std::boolalpha << statusCTransferCscDM << "\n";
	os << "TCAConnection: " << std::boolalpha << statusTCAConnection << "\n";
	os << "IFXConnection: " << std::boolalpha << statusIFXConnection << "\n";
	os << "Trying to reconnect...";

	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, os.str().c_str());


	try
	{
		connect();
		createComponents();
	}
	catch(...)
	{
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "text reconnect: got exception during connect / createComponents, ignored");
	}
}

/*!	\throw  no-throw  
	\retval true if initialization was ok */
void CSC_PhatraApplBase::init( int argc, char *argv[] )
{
	METHODNAME_DEF( CSC_PhatraApplBase, init ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	try
	{
		cmdLine::CSC_PhatraCmdLineEvaluatorPtr cmdEvalPtr = cmdLine::CSC_PhatraCmdLineEvaluatorPtr( new cmdLine::CSC_PhatraCmdLineEvaluator( ::libBatch::cmdLine::CmdLineConfiguration( argc, argv ) ) );
		
		cmdEvalPtr->evaluate();
		
        cmdLine::CSC_PhatraAppInitializerPtr appInitializer = cmdLine::CSC_PhatraAppInitializerPtr(new cmdLine::CSC_PhatraAppInitializer());
        appInitializer->setAppArgs( cmdEvalPtr );
		appInitializer->init();
		      
        initSession( appInitializer );

        m_TestingMode = m_ApplConfiguration->isTestingSet();
        
        if (m_TestingMode)
        {
            m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "testing mode requested, stopping after one cycle");
        }
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

void CSC_PhatraApplBase::createComponents()
{
	METHODNAME_DEF( CSC_PhatraApplBase, createComponents ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components...");

	try
	{
        m_CSC_PhatraUC.injectHeartBeat(getHeartBeat());
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... HeartBeat injected");
		
		m_PharmosTransactionDM = domMod::pharmosTransaction::core::PharmosTransactionDMPtr( 
			new domMod::pharmosTransaction::core::PharmosTransactionDM(m_AppSession->m_IFXConnection->getCurrentConnection(), m_CSC_LoggerPtr) );
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... PharmosTransactionDM created");
		{
			domMod::InitParamsDM initParamsDM;  initParamsDM.m_Branchno = m_ApplConfiguration->getBranchNo();
			m_PharmosTransactionDM->init( initParamsDM );
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... PharmosTransactionDM initialized");
		}

		m_CSC_PhatraUC.injectTransferFromCicsUC(createTransferFromCicsUC());
		m_CSC_PhatraUC.injectTransferFromZdpUC(createTransferFromZdpUC());
		m_CSC_PhatraUC.injectTransferToCscUC(createTransferToCscUC());

		m_CSC_PhatraUC.injectICSC_LoggerPtr(m_CSC_LoggerPtr);
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... ICSC_LoggerPtr injected");

        m_SignalHandler.registerSignalReceiver(m_CSC_PhatraUC);
		m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... SignalReceiver registered");

        if (m_TestingMode)
        {
            m_CSC_PhatraUC.flagTesting();
			m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... set Testing flag");
        }

	}
	catch(basar::Exception& ex)
	{
		m_CSC_LoggerPtr->logBasarException("text exception during createComponents", ex);
		throw ex;
	}

	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "creating components finished");
}

useCase::ITransferUCPtr CSC_PhatraApplBase::createTransferFromCicsUC()
{
	METHODNAME_DEF( CSC_PhatraApplBase, createTransferFromCicsUC ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	if (!m_ApplConfiguration->isTCAActivated())
	{
		return useCase::ITransferUCPtr(new useCase::NullTransferUC(m_CSC_LoggerPtr));
	}

	m_TransferFromCicsUC = useCase::TransferFromCicsUCPtr(new useCase::TransferFromCicsUC());
	m_TransferFromCicsUC->injectRecordTypeFactoryPtr(getRecordTypeFactory());
	m_TransferFromCicsUC->injectICSC_LoggerPtr(m_CSC_LoggerPtr);
	m_TransferFromCicsUC->injectPharmosTransactionDMPtr(m_PharmosTransactionDM);
			
	libcsc_utils::IRemoteProcedurePtr pdx010 = libcsc_utils::IRemoteProcedurePtr(
								new domMod::pharmosTransaction::preparation::PDX010RemoteProcedure(
								m_ApplConfiguration->getBranchNo(), m_ApplConfiguration->getApplicationName()));
	libcsc_utils::IRemoteProcedureCallerPtr pdx010callerptr = libcsc_utils::IRemoteProcedureCallerPtr(
								new libcsc_utils::RemoteProcedureCaller(
								m_AppSession->m_TCAConnection->getCurrentConnection(), m_CSC_LoggerPtr ));
	pdx010callerptr->injectRemoteProcedure(pdx010);
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... RemoteProcedure injected");

	m_TransferFromCicsUC->injectPDX010Caller(pdx010callerptr);
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... PDX010Caller injected");

	m_CicsPharmosTransactionDM = domMod::pharmosTransaction::preparation::CICSPharmosTransactionDMPtr( 
			new domMod::pharmosTransaction::preparation::CICSPharmosTransactionDM(m_AppSession->m_TCAConnection->getCurrentConnection(), m_CSC_LoggerPtr) );
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CicsPharmosTransactionDM created");
		
	domMod::InitParamsDM initParamsDM;  initParamsDM.m_Branchno = m_ApplConfiguration->getBranchNo();
	m_CicsPharmosTransactionDM->init( initParamsDM );
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CicsPharmosTransactionDM initialized");

	m_TransferFromCicsUC->injectCICSPharmosTransactionDMPtr(m_CicsPharmosTransactionDM);
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CICSPharmosTransactionDMPtr injected");
	return m_TransferFromCicsUC;
}

useCase::ITransferUCPtr CSC_PhatraApplBase::createTransferFromZdpUC()
{
	METHODNAME_DEF( CSC_PhatraApplBase, createTransferFromZdpUC ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	if (!m_ApplConfiguration->isZDPActivated())
	{
		return useCase::ITransferUCPtr(new useCase::NullTransferUC(m_CSC_LoggerPtr));
	}
	m_TransferFromZdpUC = useCase::TransferFromZDPUCPtr(new useCase::TransferFromZDPUC());
	m_TransferFromZdpUC->injectRecordTypeFactoryPtr(getRecordTypeFactory());
	m_TransferFromZdpUC->injectICSC_LoggerPtr(m_CSC_LoggerPtr);
	m_TransferFromZdpUC->injectPharmosTransactionDMPtr(m_PharmosTransactionDM);

	m_CTransferCscDM = domMod::pharmosTransaction::preparation::CTransferCscDMPtr( 
		new domMod::pharmosTransaction::preparation::CTransferCscDM(m_AppSession->m_IFXConnection->getCurrentConnection(), m_CSC_LoggerPtr) );
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CTransferCscDM created");

	InitCTransferCscDM initStruct;
	initStruct.m_ZDPHost = m_ApplConfiguration->getZDPHost();
	initStruct.m_ZDPDatabase = m_ApplConfiguration->getZDPDatabase();
	m_CTransferCscDM->init(initStruct);
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CTransferCscDM initialized");
	m_TransferFromZdpUC->injectCTransferCscDMPtr(m_CTransferCscDM);
	m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "... CTransferCscDM injected");
	return m_TransferFromZdpUC;
}

useCase::ITransferUCPtr CSC_PhatraApplBase::createTransferToCscUC()
{
	METHODNAME_DEF( CSC_PhatraApplBase, createTransferToCscUC ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_TransferToCscUC = useCase::TransferToCscUCPtr(new useCase::TransferToCscUC());
	m_TransferToCscUC->injectRecordTypeFactoryPtr(getRecordTypeFactory());
	m_TransferToCscUC->injectICSC_LoggerPtr(m_CSC_LoggerPtr);
	m_TransferToCscUC->injectPharmosTransactionDMPtr(m_PharmosTransactionDM);
	return m_TransferToCscUC;
}


void CSC_PhatraApplBase::initSession( const cmdLine::CSC_PhatraAppInitializerPtr appInitializer )
{
	METHODNAME_DEF( CSC_PhatraApplBase, initSession ) 
	BLOG_TRACE_METHOD( m_Logger, fun );

	const basar::db::sql::DatabaseInfo& ifxdatabaseinfo = appInitializer->getIFXConnConfiguration();
	const basar::db::sql::DatabaseInfo& tcadatabaseinfo = appInitializer->getTCAConnConfiguration();

    m_AppSession = AppSessionPtr(
		new AppSession(	
			libBatch::dbConnection::DBConnectionBasePtr(new libcsc_utils::dbConnection::IfxConnection(ifxdatabaseinfo)),
			libBatch::dbConnection::DBConnectionBasePtr(new libcsc_utils::dbConnection::TCAConnection(tcadatabaseinfo))
			)
		);

	m_ApplConfiguration = appInitializer->getAppConfiguration();
	m_CSC_LoggerPtr = appInitializer->getCSCLogger();
}

/*!	\throw  no-throw */
void CSC_PhatraApplBase::shutdown()
{	
	METHODNAME_DEF( CSC_PhatraApplBase, shutdown )
	BLOG_TRACE_METHOD( m_Logger, fun );
	
	if (0 != m_CicsPharmosTransactionDM.get())
	{
		m_CicsPharmosTransactionDM->shutdown();
	}
	if (0 != m_PharmosTransactionDM.get())
	{
		m_PharmosTransactionDM->shutdown();
	}
	if (0 != m_CTransferCscDM.get())
	{
		m_CTransferCscDM->shutdown();
	}

	disconnect();
}

void CSC_PhatraApplBase::processingSleep()
{
	basar::VarString msg;

	msg.format("CSC_PhatraApplBase::processingSleep: %d seconds", m_ApplConfiguration->getPollingInterval());
	m_CSC_LoggerPtr->log(log4cplus::DEBUG_LOG_LEVEL, msg);

	Sleep(m_ApplConfiguration->getPollingInterval());
}

void CSC_PhatraApplBase::waitRetries(basar::Int32 time)
{
	Sleep(time);
}

void CSC_PhatraApplBase::receiveSignal(int signal)
{
    basar::VarString msg;

    msg.format("csc_phatraApplBase got signal %d", signal);

    m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, msg);
    if (SIGTERM == signal || SIGINT == signal)
    {
        m_ExitGracefull = true;
        m_CSC_LoggerPtr->log(log4cplus::INFO_LOG_LEVEL, "exiting gracefull, please stand by...");
    }
}


} // end namespace csc_phatra
