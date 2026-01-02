//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		22.10.2012
 *  \version	00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_CSC_CORPHA_CSC_CORPHA_APPL_H
#define GUARD_CSC_CORPHA_CSC_CORPHA_APPL_H

#include <libbasarcmnutil.h>
#include <libbasarcmnutil_pattern.h>
#include <dbconnectionbaseptr.h>
#include <icsc_loggerptr.h>
#include <iremoteprocedurecallerptr.h>
#include <iapplconfigurationptr.h>
#include <isignalreceiver.h>
#include <csc_signalhandler.h>

#include "appsessionptr.h"
#include "appinitializer.h"
#include "csc_corphauc.h"
#include "ipxvbservicelocatorptr.h"
#include "ipxvbordercollectionptr.h"
#include "ipxvbtaskcontrolptr.h"
#include "icicsorderdmptr.h"
#include "csc_corphaappinitializerptr.h"

namespace csc_corpha
{
    class CSC_CorphaAppl;
    class AppInitializer;
} // csc_corpha

namespace libBatch
{
    class CommandLineParser;
} // libBatch

namespace domMod
{
	class Mail;
} // domMod

namespace basar
{
    namespace appl
    {
        struct EventReturnStruct;
    } // appl
} // basar

namespace log4cplus 
{
	class Logger;
} // log4cplus


namespace csc_corpha
{
	class CSC_CorphaApplBase : public libcsc_utils::ISignalReceiver
	{  
		friend class basar::cmnutil::Singleton< CSC_CorphaApplBase >;

		public:			
			virtual	~CSC_CorphaApplBase();	    

		private:			
			CSC_CorphaApplBase();	        
			CSC_CorphaApplBase( const CSC_CorphaApplBase & rCopy );		    
			CSC_CorphaApplBase & operator = ( const CSC_CorphaApplBase & rCopy );	
        
		public:						
			void												init( int argc, char *argv[] );
			void												shutdown();	    
			basar::appl::EventReturnStruct						run();	    			
			void												receiveSignal(int sig);

		private:			
			void												initSession( const cmdLine::CSC_CorphaAppInitializerPtr );
			void												createComponents();
			bool												checkConnections();
			void												connect();
			void												disconnect();
			void												processingSleep();
			void												waitRetries(basar::Int32 time);
			void												establishConnection( ::libBatch::dbConnection::DBConnectionBasePtr dbconn, basar::Int32 maxRetries, basar::Int32 secBetweenRetries );		
			const basar::db::sql::DatabaseInfo					getTCAConfiguration( const cmdLine::CSC_CorphaAppInitializerPtr appInitializer );
			void												reconnect();
			void												resetDMs();
			void 												resetConnections();
			void 												logConnectionStatus();

			const basar::VarString								getTCAStartTransaction() const;			

			domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr	getPXVBServiceLocator();	
			domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr	getPXVBOrderCollection();
			domMod::corpha::pxVerbund::IPXVBTaskControlPtr		getPXVBTaskControl();
			domMod::corpha::processOrder::ICICSOrderDMPtr		getCICSOrderDM();			

		private:        
			libcsc_utils::CSC_SignalHandler                     m_SignalHandler;
			AppSessionPtr										m_AppSession;
			cmdLine::CSC_CorphaAppInitializerPtr 				m_AppInitializer;
			log4cplus::Logger&									m_Logger;				
			libcsc_utils::IApplConfigurationPtr					m_ApplConfiguration;											
			useCase::CSC_CorphaUC								m_CSC_CorphaUC;
			libcsc_utils::ICSC_LoggerPtr						m_CSC_LoggerPtr;			
			domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr	m_PXVBServiceLocator;
			domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr  m_PXVBOrderCollection;
			domMod::corpha::pxVerbund::IPXVBTaskControlPtr		m_PXVBTaskControl;
			domMod::corpha::processOrder::ICICSOrderDMPtr		m_CICSOrderDM;
			bool												m_ExitGracefull;
			bool                                                m_TestingMode;
	};
















	//---------------------------------------------------------------------------------------//
	/*! \brief  derived class from CSC_CorphaApplBase.
		This is a final class. Singleton  
	*  \note  class is necessary for dll exporting Singleton\<CSC_CorphaApplBase\>  */
	//---------------------------------------------------------------------------------------//
	class CSC_CorphaAppl : public basar::cmnutil::Singleton< CSC_CorphaApplBase > 
	{
		friend class dummy;			//!< prevents pedantic compiler warning

		private:	
			CSC_CorphaAppl();	
			CSC_CorphaAppl( const CSC_CorphaAppl & r );	
			CSC_CorphaAppl & operator = ( const CSC_CorphaAppl & r );	
	};
}

#endif // GUARD_CSC_CORPHA_CSC_CORPHA_APPL_H

