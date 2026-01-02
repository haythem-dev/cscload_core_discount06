 //-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief  application (main) functions for CSC_PHADEX
*   \author
*   \date
*/
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// includes
//-------------------------------------------------------------------------------------------------//
#include "csc_phadexapplctrl.h"
#include "componentmanager/csc_phadexinfrastructurecompmgr.h"

#include <libutil/irunnable.h>
#include <libutil/exception.h>


#include "infrastructure/config/xmlconfigreader.h"

//#include <libbasarguitie.h>


//-------------------------------------------------------------------------------------------------//
// singleton qualification
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace cmnutil
    {
        /*! specialised method */
        template <>
        typename Singleton<csc_phadex::ApplCtrlImpl>::InstancePtr& Singleton<csc_phadex::ApplCtrlImpl>::inst()
        {
            static InstancePtr s_inst;
            return s_inst;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// namespace
//-------------------------------------------------------------------------------------------------//
namespace csc_phadex
{
    //-------------------------------------------------------------------------------------------------//
    /*! \throw no-throw */
    //-------------------------------------------------------------------------------------------------//
    ApplCtrlImpl::ApplCtrlImpl()
    : m_Logger( csc_phadex::LoggerPool::getLoggerCsc_phadex() )
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
			getInfrastructureCM()->getApplComponentManager()->injectCICSConnection( getInfrastructureCM()->getInfrastructureSetup()->getCICSConnection() );
			getInfrastructureCM()->getApplComponentManager()->injectDBConnection( getInfrastructureCM()->getInfrastructureSetup()->getDBConnection() );
			getInfrastructureCM()->getApplComponentManager()->setConfig( getInfrastructureCM()->getInfrastructureSetup()->getConfig() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processBasarException( e, getLogger(), fun, __FILE__, __LINE__ );
            throw;
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
            getInfrastructureCM()->getInfrastructureSetup()->checkSetting();
            getInfrastructureCM()->getApplComponentManager()->getMainUC()->run();
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processBasarException( e, getLogger(), fun, __FILE__, __LINE__ );
            // throw int
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
            // throw int
        }
    }

} // namespace csc_phadex
