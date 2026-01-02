//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief application controller 
 *  \author Johann Franz
 *  \date 06.12.2010
 *  \version 00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CSC_PHATRA_APPL_H
#define GUARD_CSC_PHATRA_CSC_PHATRA_APPL_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <libbasarcmnutil_pattern.h>
#include <dbconnectionbaseptr.h>
#include "appsessionptr.h"
#include "iapplconfigurationptr.h"
#include "csc_phatraappinitializer.h"
#include "recordtypefactoryptr.h"
#include "ipxvbservicelocatorptr.h"
#include "csc_phatrauc.h"
#include "icsc_loggerptr.h"
#include "csc_phatraappinitializerptr.h"
#include "icsc_heartbeatptr.h"

#include "itransferuc.h"
#include "transferfromcicsuc.h"
#include "transferfromzdpuc.h"
#include "transfertocscuc.h"

#include <isignalreceiver.h>
#include <csc_signalhandler.h>


//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
    class CSC_PhatraAppl;
}

namespace libBatch
{
    class CommandLineParser;

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
namespace csc_phatra
{
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
    class CSC_PhatraApplBase : public libcsc_utils::ISignalReceiver
    {  
        friend class basar::cmnutil::Singleton<CSC_PhatraApplBase>;

    public:
	    /*! \brief destructor \n no-throw */
	    virtual ~CSC_PhatraApplBase();

	    /*! \brief initialize members \n \throw no-throw */
	    void init( int argc, char *argv[] );
        void shutdown();

	    /*! \brief main entrance, called from main()
		    \n no-throw */
	    basar::appl::EventReturnStruct	run();

        void receiveSignal(int signal);

    private:
        //!< std constructor, protected because of singleton
	    CSC_PhatraApplBase();	
        //!< forbidden copy constructor
	    CSC_PhatraApplBase( const CSC_PhatraApplBase & rCopy );	
	    //!< forbidden assignment operator
	    CSC_PhatraApplBase & operator = ( const CSC_PhatraApplBase & rCopy );	

		void initSession( const cmdLine::CSC_PhatraAppInitializerPtr );
		void createComponents();
		useCase::ITransferUCPtr createTransferFromCicsUC();
		useCase::ITransferUCPtr createTransferFromZdpUC();
		useCase::ITransferUCPtr createTransferToCscUC();

		bool checkConnections();
		void connect(); // SH, 2012-06-15
		void reconnect();
		void disconnect();
		void establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries ); // SH, 2012-06-15
		void processingSleep();
		void waitRetries(basar::Int32 time);


        domMod::pharmosTransaction::core::RecordTypeFactoryPtr		    getRecordTypeFactory();
		domMod::pharmosTransaction::pxVerbund::IPXVBServiceLocatorPtr	getPXVBServiceLocator();
        csc_phatra::ICSC_HeartBeatPtr                                   getHeartBeat();

    private:
        /////////////////////
        // Members
        /////////////////////
        AppSessionPtr												            m_AppSession;
        log4cplus::Logger&											            m_Logger;

		domMod::pharmosTransaction::core::RecordTypeFactoryPtr		            m_RecordTypeFactory;

		libcsc_utils::IApplConfigurationPtr							            m_ApplConfiguration;								
		domMod::pharmosTransaction::pxVerbund::IPXVBServiceLocatorPtr           m_PXVBServiceLocator;

		useCase::CSC_PhatraUC											        m_CSC_PhatraUC; // main UC
		useCase::TransferFromCicsUCPtr											m_TransferFromCicsUC; // sub UC
		useCase::TransferFromZDPUCPtr 									        m_TransferFromZdpUC; // sub UC
		useCase::TransferToCscUCPtr										        m_TransferToCscUC; // sub UC

		libcsc_utils::ICSC_LoggerPtr										    m_CSC_LoggerPtr;

        csc_phatra::ICSC_HeartBeatPtr                                           m_CSC_HeartBeat;

		domMod::pharmosTransaction::preparation::CICSPharmosTransactionDMPtr    m_CicsPharmosTransactionDM;
		domMod::pharmosTransaction::preparation::CTransferCscDMPtr              m_CTransferCscDM;
		domMod::pharmosTransaction::core::PharmosTransactionDMPtr		        m_PharmosTransactionDM;


        libcsc_utils::CSC_SignalHandler                                         m_SignalHandler;
		bool															        m_ExitGracefull;
        bool                                                                    m_TestingMode;
};

//---------------------------------------------------------------------------------------//
/*! \brief  derived class from CSC_PhatraApplBase.
	This is a final class. Singleton  
 *  \note  class is necessary for dll exporting Singleton\<CSC_PhatraApplBase\>  */
class CSC_PhatraAppl : public basar::cmnutil::Singleton<CSC_PhatraApplBase> 
{
	friend class dummy;			//!< prevents pedantic compiler warning

private:
	/*! \brief standard constructor \n \throw no-throw */
	CSC_PhatraAppl();
	/*! \brief copy constructor \n \throw no-throw */
	CSC_PhatraAppl( const CSC_PhatraAppl & r );
	/*! \brief assign operator \n \throw no-throw */
	CSC_PhatraAppl & operator = ( const CSC_PhatraAppl & r );	
};

} // end namespace csc_phatra

#endif // GUARD_CSC_PHATRA_CSC_PHATRA_APPL_H

