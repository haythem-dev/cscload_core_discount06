//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#include "csc_phatrauc.h"
#include "icsc_heartbeat.h"
#include <missingdependencyinjectionexception.h>
#include <classinfo_macros.h>
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

CSC_PhatraUC::CSC_PhatraUC() : m_ExitGracefull(false), m_IsTesting(false)
{
}

//-------------------------------------------------------------------------------------------//

CSC_PhatraUC::~CSC_PhatraUC()
{
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::flagTesting()
{
	m_IsTesting = true;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::flagExitGracefull()
{
	m_ExitGracefull = true;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::receiveSignal(int signal)
{
	basar::VarString msg;

	msg.format("CSC_PhatraUC got signal %d", signal);

	m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
            
	if (SIGTERM == signal || SIGINT == signal)
	{
		flagExitGracefull();
		m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "exiting gracefull, please stand by...");
	}
}

//-------------------------------------------------------------------------------------------//

basar::appl::EventReturnStruct CSC_PhatraUC::run()
{
	checkInjections();

	basar::Int32 recordsProcessed = 0;

	do
	{
		m_HeartBeat->emitHeartBeat();
                
		if (!m_ExitGracefull)
		{
			m_TransferFromZdpUC->run();
		}

		if(!m_ExitGracefull)
		{
			m_TransferToCscUC->run();
		}

		if (!m_ExitGracefull)
		{
			m_TransferFromCicsUC->run();
			recordsProcessed = m_TransferFromCicsUC->getRecordsProcessed();
		}

		if (m_ExitGracefull)
		{
			m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "UC exiting");
		}
	}
	while (recordsProcessed > 0 && !m_IsTesting);

	return basar::appl::EventReturnStruct();
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::checkInjections() const
{	
	METHODNAME_DEF( CSC_PhatraUC, checkInjections );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	if ( 0 == m_CSC_Logger.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "CSC_Logger missing! Inject CSC_Logger first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_HeartBeat.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "ICSC_HeartBeat missing! Inject ICSC_HeartBeat first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_TransferFromCicsUC.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "TransferFromCicsUC missing! Inject TransferFromCicsUC first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_TransferFromZdpUC.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "TransferFromZdpUC missing! Inject TransferFromZdpUC first!", __FILE__, __LINE__) );
	}
	if ( 0 == m_TransferToCscUC.get() )
	{
		throw libcsc_utils::MissingDependencyInjectionException( basar::ExceptInfo(fun, "TransferToCscUC missing! Inject TransferToCscUC first!", __FILE__, __LINE__) );
	}
}
		
//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::injectTransferFromCicsUC(ITransferUCPtr uc)
{
	m_TransferFromCicsUC = uc;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::injectTransferFromZdpUC(ITransferUCPtr uc)
{
	m_TransferFromZdpUC = uc;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::injectTransferToCscUC(ITransferUCPtr uc)
{
	m_TransferToCscUC = uc;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::injectHeartBeat(csc_phatra::ICSC_HeartBeatPtr heartBeat)
{
	m_HeartBeat = heartBeat;
}

//-------------------------------------------------------------------------------------------//

void CSC_PhatraUC::injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger)
{
	m_CSC_Logger = csc_logger;
}

//-------------------------------------------------------------------------------------------//

} //namespace useCase
} //namespace csc_phatra

//-------------------------------------------------------------------------------------------//
