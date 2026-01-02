 //-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief  application (main) functions for IBTORDERIMPORT
*   \author
*   \date
*/
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// includes
//-------------------------------------------------------------------------------------------------//
#include "ibtorderimportapplctrl.h"
#include "componentmanager/ibtorderimportinfrastructurecompmgr.h"

#include <libutil/irunnable.h>
#include <libutil/exception.h>

#include <signal.h>
#include <setupsignalhandlingexception.h>
#include <softkillexception.h>

//-------------------------------------------------------------------------------------------------//
// singleton qualification
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace cmnutil
    {
        /*! specialised method */
        template <>
        typename Singleton<ibtorderimport::ApplCtrlImpl>::InstancePtr& Singleton<ibtorderimport::ApplCtrlImpl>::inst()
        {
            static InstancePtr s_inst;
            return s_inst;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// namespace
//-------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{

#ifndef WIN32
	#include <unistd.h>
	static unsigned int Sleep( unsigned int seconds )
	{
		return sleep( seconds );
	}
#else
	#include <windows.h>
#endif

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    ApplCtrlImpl::ApplCtrlImpl()
		: m_Logger( ibtorderimport::LoggerPool::getLoggerIbtorderimport() ), m_ExitGracefull(false)
    {
        METHODNAME_DEF( ApplCtrlImpl, ApplCtrlImpl )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    ApplCtrlImpl::~ApplCtrlImpl()
    {
        METHODNAME_DEF( ApplCtrlImpl, ~ApplCtrlImpl )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    const log4cplus::Logger& ApplCtrlImpl::getLogger() const
    {
        return m_Logger;
    }

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    void ApplCtrlImpl::createInfrastructureCM( int argc, char *argv[] )
    {
        METHODNAME_DEF( ApplCtrlImpl, createInfrastructureCM )
        BLOG_TRACE_METHOD( getLogger(), fun );

        m_InfrastructureCM = componentManager::InfrastructureCompMgrPtr( new componentManager::InfrastructureCompMgr(argc, argv) );
    }

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    componentManager::InfrastructureCompMgrPtr ApplCtrlImpl::getInfrastructureCM()
    {
        METHODNAME_DEF( ApplCtrlImpl, getInfrastructureCM )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return m_InfrastructureCM;
    }

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    void ApplCtrlImpl::deleteInfrastructureCM()
    {
        METHODNAME_DEF( ApplCtrlImpl, deleteInfrastructureCM )
        BLOG_TRACE_METHOD( getLogger(), fun );

        m_InfrastructureCM.reset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    void ApplCtrlImpl::init( int argc, char *argv[] )
    {
        METHODNAME_DEF( ApplCtrlImpl, init )
        BLOG_TRACE_METHOD( getLogger(), fun );

        try
        {
            createInfrastructureCM( argc, argv );
            getInfrastructureCM()->getInfrastructureSetup()->init();
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processBasarException( e, getLogger(), fun, __FILE__, __LINE__ );
            throw e;
        }
    }

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw
    \retval true if initialization was ok */
    //-------------------------------------------------------------------------------------------------//
    void ApplCtrlImpl::run()
    {
        METHODNAME_DEF( ApplCtrlImpl, run )
        BLOG_TRACE_METHOD( getLogger(), fun );

		try
		{
			m_SignalHandler.setupSignalHandling();
			m_SignalHandler.registerSignalReceiver(*this);
			BLOG_INFO( getLogger(), "signal handling set up + registered.");
		}
		catch( libcsc_utils::SetupSignalHandlingException& ex )
		{
			std::stringstream msg;
			msg << "error setting up signal handling: " << ex.what().c_str() << std::endl;
			BLOG_ERROR( getLogger(), msg.str());
			throw ex;
		}
		catch( ... )
		{
			BLOG_ERROR( getLogger(), "generic error setting up signal handling" );
			throw;
		}

        try
        {
			while( !m_ExitGracefull )
			{						
				getInfrastructureCM()->getApplComponentManager()->getMainUC()->run();

				processingSleep();

				if( m_ExitGracefull )
				{
					BLOG_INFO( getLogger(), "exit - got signal" );
					break;
				}
			}
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processBasarException( e, getLogger(), fun, __FILE__, __LINE__ );
            throw e;
        }
    }

	//-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
	void ApplCtrlImpl::processingSleep()
	{
		METHODNAME_DEF( ApplCtrlImpl, processingSleep )
        BLOG_TRACE_METHOD( getLogger(), fun );

		basar::Int32 secs = m_InfrastructureCM->getSleepInterval();

		std::stringstream msg;
		msg << "sleeping in ApplBase for < " << secs << " > seconds ...";
		BLOG_INFO( getLogger(), msg.str());
		
		Sleep(secs);

		BLOG_INFO( getLogger(), "... wake up again!" );
	}

	//--------------------------------------------------------------------------------------------------//
	void ApplCtrlImpl::receiveSignal(int signal)
	{
		if (SIGTERM == signal || SIGINT == signal)
		{
			m_ExitGracefull = true;
			BLOG_INFO( getLogger(), "received SIGTERM / SIGINT" );
		}
	}

    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    void ApplCtrlImpl::shutdown()
    {
        METHODNAME_DEF( ApplCtrlImpl, shutdown )
        BLOG_TRACE_METHOD( getLogger(), fun );

        try
        {
            getInfrastructureCM()->getApplComponentManager()->clear();
            getInfrastructureCM()->getInfrastructureSetup()->shutdown();
            deleteInfrastructureCM();
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processBasarException( e, getLogger(), fun, __FILE__, __LINE__ );
            throw e;
        }
    }

} // namespace ibtorderimport
