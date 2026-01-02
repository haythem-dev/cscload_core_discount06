//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainuc.h"

#include "componentmanager/iusecasegetter.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace useCase
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MainUC::MainUC()
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MainUC::MainUC()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerUseCases() )
    {
        METHODNAME_DEF( MainUC, MainUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MainUC::~MainUC()
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MainUC::~MainUC()
    {
        METHODNAME_DEF( MainUC, ~MainUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void MainUC::injectUseCaseGetter( csc_deli::componentManager::IUseCaseGetterPtr useCaseGetter )
    {
        METHODNAME_DEF( MainUC, injectUseCaseGetter )
        BLOG_TRACE_METHOD( m_Logger, fun );

        m_UseCaseGetter = useCaseGetter;
    }

    csc_deli::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
    {
        METHODNAME_DEF( MainUC, getUseCaseGetter )
        BLOG_TRACE_METHOD( m_Logger, fun );

        CHECK_INSTANCE_EXCEPTION( m_UseCaseGetter.get() );
        return m_UseCaseGetter;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void MainUC::run()
    {
        METHODNAME_DEF( MainUC, run )
        BLOG_TRACE_METHOD( m_Logger, fun );

        try
        {
            libutil::useCase::IRunnablePtr debtLimitBatchUC = getUseCaseGetter()->getDebtLimitBatchUC();
            debtLimitBatchUC->run();
        }
        catch( basar::Exception& e )
        {
            // todo: Deal with the exception and log
            BLOG_DEBUG( m_Logger, e.what() );
        }

    }
} // namespace usecase
} // namespace csc_deli
