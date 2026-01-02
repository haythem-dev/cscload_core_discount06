#include "mainuc.h"
#include "componentmanager/csc_phadexapplcompmgr.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "usecase/transferuc/itransferuc.h"
#include "domainmodule/taskcontrol/itaskcontrol.h"
#include <setupsignalhandlingexception.h>
#include <libutil/util.h>

namespace csc_phadex
{
namespace useCase
{
MainUC::MainUC()
: m_Logger( LoggerPool::getLoggerUseCases() ),
  m_ExitGraceful( false ),
  m_NoCICS( false )
{
	METHODNAME_DEF( MainUC, MainUC )
	BLOG_TRACE_METHOD( m_Logger, fun );

	try
	{
		m_SignalHandler.setupSignalHandling();
		m_SignalHandler.registerSignalReceiver( *this );
	}
	catch( const libcsc_utils::SetupSignalHandlingException & e )
	{
		std::stringstream ss;
		ss << "Error setting up signal handling: " << e.what();
		BLOG_ERROR( m_Logger, ss.str().c_str() );
		//m_CSC_LoggerPtr->logBasarException( "error setting up signal handling", ex );
		throw;
	}
	catch( ... )
	{
		BLOG_ERROR( m_Logger, "Generic error setting up signal handling" );
		//m_CSC_LoggerPtr->log( log4cplus::ERROR_LOG_LEVEL, "generic error setting up signal handling" );
	}
}

MainUC::~MainUC()
{
	METHODNAME_DEF( MainUC, ~MainUC )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void MainUC::injectUseCaseGetter( csc_phadex::componentManager::IUseCaseGetterPtr useCaseGetter )
{
	METHODNAME_DEF( MainUC, injectUseCaseGetter )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_UseCaseGetter = useCaseGetter;
}

void MainUC::injectTaskControl( csc_phadex::domMod::ITaskControlPtr taskControl )
{
	METHODNAME_DEF( MainUC, injectTaskControl )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_TaskControl = taskControl;
}

void MainUC::setSleepDuration( const basar::Int32 milliSeconds )
{
	m_SleepDuration = milliSeconds;
}

void MainUC::setNoCICS(const bool noCICS)
{
	m_NoCICS = noCICS;
}

csc_phadex::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
{
	METHODNAME_DEF( MainUC, getUseCaseGetter )
	BLOG_TRACE_METHOD( m_Logger, fun );

	CHECK_INSTANCE_EXCEPTION( m_UseCaseGetter.get() );
	return m_UseCaseGetter;
}

void MainUC::run()
{
	METHODNAME_DEF(MainUC, run)
	BLOG_TRACE_METHOD(m_Logger, fun);

	if (true == m_NoCICS)
	{
		doRunWithoutCICS();
	}
	else
	{
		doRunWithCICS();
	}
}


void MainUC::doRunWithCICS()
{
	METHODNAME_DEF( MainUC, doRunWithCICS )
	BLOG_TRACE_METHOD( m_Logger, fun );

	try
	{
		csc_phadex::useCase::ITransferUCPtr transferUC = getUseCaseGetter()->getTransferUC();
		libutil::useCase::IRunnablePtr processUC = getUseCaseGetter()->getProcessUC();

		while( false == m_ExitGraceful )
		{
			m_TaskControl->heartBeat();
			checkConnections();

			do
			{
				transferUC->run();
				if( m_ExitGraceful )
				{
					break;
				}
				processUC->run();
				m_TaskControl->heartBeat();
			}
			while(    false == m_ExitGraceful
				   && transferUC->hasRecordsLeft() );

			m_TaskControl->heartBeat();
			if( false == m_ExitGraceful )
			{
				processSleep();
			}
		}
	}
	catch( basar::Exception & e )
	{
		BLOG_ERROR( m_Logger, e.what() );
	}
}

void MainUC::doRunWithoutCICS()
{
	METHODNAME_DEF(MainUC, doRunWithoutCICS)
	BLOG_TRACE_METHOD(m_Logger, fun);

	try
	{
		libutil::useCase::IRunnablePtr processUC = getUseCaseGetter()->getProcessUC();

		while (false == m_ExitGraceful)
		{
			m_TaskControl->heartBeat();
			checkConnections();
			processUC->run();
			m_TaskControl->heartBeat();
			if (false == m_ExitGraceful)
			{
				processSleep();
			}
		}
	}
	catch (basar::Exception & e)
	{
		BLOG_ERROR(m_Logger, e.what());
	}
}

void MainUC::checkConnections()
{
	// TODO DK
}

#ifndef WIN32
	#include <unistd.h>
	static unsigned int Sleep( unsigned int milliseconds )
	{
		return usleep( milliseconds * 1000 );
	}
#else
	#include <windows.h>
#endif

void MainUC::processSleep()
{
	Sleep( m_SleepDuration );
}

void MainUC::receiveSignal( int signal )
{
	if(	   SIGTERM == signal 
		|| SIGINT == signal )
	{
		m_ExitGraceful = true;
		BLOG_INFO( m_Logger, "Received SIGTERM / SIGINT" );
		//m_CSC_CorphaUC.flagExitGracefull();
		//if( 0 != m_CSC_LoggerPtr.get() )
		//{
		//	m_CSC_LoggerPtr->log( log4cplus::INFO_LOG_LEVEL, "received SIGTERM / SIGINT" );
		//}
	}
}

} // namespace usecase
} // namespace csc_phadex
