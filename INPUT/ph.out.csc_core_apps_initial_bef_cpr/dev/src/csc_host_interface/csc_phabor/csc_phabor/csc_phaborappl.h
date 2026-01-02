//--------------------------------------------------------------------------------------------------//
/*! \file		csc_phaborappl.h
 *  \brief      application controller 
 *  \author     Julian Machata
 *  \date       20.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_CSC_PHABOR_APPL_H
#define GUARD_CSC_PHABOR_CSC_PHABOR_APPL_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <libbasarcmnutil_pattern.h>
#include <dbconnectionbaseptr.h>
#include <iremoteprocedureptr.h>

#include "appsessionptr.h"
#include "iapplconfigurationptr.h"
#include "csc_phaborappinitializer.h"
#include "csc_phaborappinitializerptr.h"
#include "csc_phaboruc.h"
#include "icsc_loggerptr.h"
#include "cicsbatchorderheaddmptr.h"
#include "cicsbatchorderheaddm.h"
#include "cicsbatchorderposdmptr.h"
#include "cicsbatchorderposdm.h"
#include "cicsbatchorderdmptr.h"
#include "cicsbatchorderdm.h"
#include "batchorderheaddmptr.h"
#include "batchorderheaddm.h"
#include "batchorderposdmptr.h"
#include "batchorderposdm.h"
#include "batchorderdmptr.h"
#include "batchorderdm.h"
#include "cscbatchorderheaddmptr.h"
#include "cscbatchorderheaddm.h"
#include "cscbatchorderposdmptr.h"
#include "cscbatchorderposdm.h"
#include "cscbatchorderdmptr.h"
#include "cscbatchorderdm.h"
#include "batchordertransformerptr.h"
#include "batchordertransformer.h"
#include "ipxvbservicelocatorptr.h"
#include "icsc_heartbeatptr.h"
#include "icsc_heartbeat.h"
#include "csc_heartbeat.h"

#include "csc_phaborcmdlineevaluatorptr.h"
#include "initparamsdmptr.h"
#include "initparamsdm.h"
#include <isignalreceiver.h>
#include <csc_signalhandler.h>

//--------------------------------------------------------------------------------------------------//
// extern section
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
    class CSC_PhaborAppl;
}

namespace libBatch
{
    class CommandLineParser;
}

namespace domMod
{
	class Mail;
}

namespace basar
{
    namespace appl
    {
        struct EventReturnStruct;
    }
}

namespace log4cplus 
{
  class Logger;
}

//--------------------------------------------------------------------------------------------------//
// namespace setcion
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
class CSC_PhaborApplBase : public libcsc_utils::ISignalReceiver
{  
        friend class basar::cmnutil::Singleton<CSC_PhaborApplBase>;

		//------------------------------------------------------------------------------------------//
        // member definition section
        //------------------------------------------------------------------------------------------//

    public:
	    //!< \brief destructor \n no-throw 
	    virtual ~CSC_PhaborApplBase();

	    //!< \brief initialize members \n \throw no-throw 
	    void init( int argc, char *argv[] );

		//!< \brief shutdown members \n \throw no-throw 
        void shutdown();

	    //!< \brief main entrance, called from main() \n no-throw 
	    basar::appl::EventReturnStruct	run();

		void receiveSignal(int signal);

    private:
        //!< std constructor, protected because of singleton
	    CSC_PhaborApplBase();	
        //!< forbidden copy constructor
	    CSC_PhaborApplBase( const CSC_PhaborApplBase & rCopy );	
	    //!< forbidden assignment operator
	    CSC_PhaborApplBase & operator = ( const CSC_PhaborApplBase & rCopy );	

		void createCSC_Phabor();
		void initSession( const cmdLine::CSC_PhaborAppInitializerPtr );
		void createComponents();

		bool checkConnections();
		//!< \brief connect to ifx and tca
		void connect(); 
		//!< \brief disconnect from ifx and tca
		void disconnect();
		//!< \brief establish the given connection and handle retry if failing
		void establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries ); 
		//!< \brief establish the given connection without any retry handling
		void establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn );
		//!< \brief set application to sleep
		void processingSleep();
		//!< \brief set application to sleep between retries of connecting
		void waitRetries(basar::Int32 time);
		//!< \brief reconnect to database and tcaccess (e.g. if connection is lost)
		void reconnect();
		//!< \brief resetting dm's (mainly for preparing reconnect)
		void resetDMs();
		//!< \brief resetting connections (mainly for preparing reconnect)
		void resetConnections();
		//!< \brief logging current status of the components and connections
		void logConnectionStatus();

		//!< \brief creates new cmdLineEvaluator with given args
		cmdLine::CSC_PhaborCmdLineEvaluatorPtr getNewCmdLineEvaluator( int argc, char *argv[] );
		//!< \brief creates new PDX050RemoteProcedure with given args
		libcsc_utils::IRemoteProcedurePtr getNewPDX050RemoteProcedure( basar::Int16 branchNo, basar::VarString applicationName );
		//!< creates new RemoteProcedureCaller
		libcsc_utils::IRemoteProcedureCallerPtr getNewRemoteProcedureCaller();
		//!< creates new CICSBatchOrderHeadDM
		domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr getNewCICSBatchOrderHeadDM();
		//!< creates new CICSBatchOrderPosDM
		domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr getNewCICSBatchOrderPosDM();
		//!< creates new CICSBatchOrderDM
		domMod::batchOrder::preparation::CICSBatchOrderDMPtr getNewCICSBatchOrderDM();
		//!< creates new BatchOrderHeadDM
		domMod::batchOrder::processing::BatchOrderHeadDMPtr getNewBatchOrderHeadDM();
		//!< creates new BatchOrderPosDM
		domMod::batchOrder::processing::BatchOrderPosDMPtr getNewBatchOrderPosDM();
		//!< creates new BatchOrderDM
		domMod::batchOrder::processing::BatchOrderDMPtr getNewBatchOrderDM();
		//!< creates new CSCBatchOrderHeadDM
		domMod::batchOrder::processing::CSCBatchOrderHeadDMPtr getNewCSCBatchOrderHeadDM();
		//!< creates new CSCBatchOrderPosDM
		domMod::batchOrder::processing::CSCBatchOrderPosDMPtr getNewCSCBatchOrderPosDM();
		//!< creates new CSCBatchOrderDM
		domMod::batchOrder::processing::CSCBatchOrderDMPtr getNewCSCBatchOrderDM();
		//!< creates new BatchOrderTransformer
		domMod::batchOrder::core::BatchOrderTransformerPtr getNewBatchOrderTransformer();
		/*!	\throw  no-throw */
		domMod::batchOrder::pxVerbund::IPXVBServiceLocatorPtr getPXVBServiceLocator();
		//!< creates new InitParamsDM
		domMod::InitParamsDMPtr getNewInitParamsDM();
		//!< \brief runs CSC_PhaborUC
		basar::appl::EventReturnStruct runCscPhabor();
		//!< \brief logging fail of establishing connection
		void logConnectionEstablishFail( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 numberOfTrials, log4cplus::LogLevel logLevel );		
		//!< \brief get branchno from ApplConfiguration
		basar::Int16 getBranchNo() const;
		//!< \brief get ApplicationName from ApplConfiguration
		const basar::VarString getApplicationName() const;
		//!< \brief initialize dms
		void doInits();
		//!< \brief make injections for components
		void doInjects();
		//!< \brief get heartbeat component for taskcontrol
		csc_phabor::ICSC_HeartBeatPtr getHeartBeat();

    private:

        /////////////////////
        // Members
        /////////////////////

        AppSessionPtr															m_AppSession;
		cmdLine::CSC_PhaborAppInitializerPtr 									m_AppInitializer;
        log4cplus::Logger&														m_Logger;
		libcsc_utils::IApplConfigurationPtr										m_ApplConfiguration;								
		useCase::CSC_PhaborUC													m_CSC_PhaborUC;
		libcsc_utils::ICSC_LoggerPtr											m_CSC_LoggerPtr;
		libcsc_utils::IRemoteProcedurePtr										m_PDX050;
		libcsc_utils::IRemoteProcedureCallerPtr									m_PDX050CallerPtr;
		domMod::batchOrder::pxVerbund::IPXVBServiceLocatorPtr					m_PXVBServiceLocator;
        csc_phabor::ICSC_HeartBeatPtr                                           m_CSC_HeartBeat;

		domMod::InitParamsDMPtr													m_InitParamsDM;
		domMod::batchOrder::core::BatchOrderTransformerPtr						m_BatchOrderTransformer;

		domMod::batchOrder::preparation::CICSBatchOrderHeadDMPtr				m_CICSBatchOrderHeadDM;
		domMod::batchOrder::preparation::CICSBatchOrderPosDMPtr					m_CICSBatchOrderPosDM;
		domMod::batchOrder::preparation::CICSBatchOrderDMPtr					m_CICSBatchOrderDM;

		domMod::batchOrder::processing::BatchOrderHeadDMPtr						m_BatchOrderHeadDM;
		domMod::batchOrder::processing::BatchOrderPosDMPtr						m_BatchOrderPosDM;
		domMod::batchOrder::processing::BatchOrderDMPtr							m_BatchOrderDM;

		domMod::batchOrder::processing::CSCBatchOrderHeadDMPtr					m_CSCBatchOrderHeadDM;
		domMod::batchOrder::processing::CSCBatchOrderPosDMPtr					m_CSCBatchOrderPosDM;
		domMod::batchOrder::processing::CSCBatchOrderDMPtr						m_CSCBatchOrderDM;

		libcsc_utils::CSC_SignalHandler                                         m_SignalHandler;
		bool																	m_ExitGracefull;
		bool 																	m_TestingMode;
		bool 																	m_TransferMode;
		bool 																	m_ProcessMode;
};

//---------------------------------------------------------------------------------------//
/*! \brief  derived class from CSC_PhaborApplBase.
	This is a final class. Singleton  
 *  \note  class is necessary for dll exporting Singleton\<CSC_PhaborApplBase\>  */
class CSC_PhaborAppl : public basar::cmnutil::Singleton<CSC_PhaborApplBase> 
{
	friend class dummy;			//!< prevents pedantic compiler warning

private:
	/*! \brief standard constructor \n \throw no-throw */
	CSC_PhaborAppl();
	/*! \brief copy constructor \n \throw no-throw */
	CSC_PhaborAppl( const CSC_PhaborAppl & r );
	/*! \brief assign operator \n \throw no-throw */
	CSC_PhaborAppl & operator = ( const CSC_PhaborAppl & r );	
};

} // end namespace csc_phabor

#endif // GUARD_CSC_PHABOR_CSC_PHABOR_APPL_H

