//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainuc.h"

#include "componentmanager/iusecasegetter.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include <libutil/irunnableptr.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace useCase
{
    MainUC::MainUC()
    : m_Logger( mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerUseCases() )
    {
        METHODNAME_DEF( MainUC, MainUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    MainUC::~MainUC()
    {
        METHODNAME_DEF( MainUC, ~MainUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void MainUC::injectUseCaseGetter( componentManager::IUseCaseGetterPtr useCaseGetter )
    {
        METHODNAME_DEF( MainUC, injectUseCaseGetter )
        BLOG_TRACE_METHOD( m_Logger, fun );

        m_UseCaseGetter = useCaseGetter;
    }

    componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
    {
        METHODNAME_DEF( MainUC, getUseCaseGetter )
        BLOG_TRACE_METHOD( m_Logger, fun );

        CHECK_INSTANCE_EXCEPTION( m_UseCaseGetter.get() );
        return m_UseCaseGetter;
    }

    void MainUC::run()
    {
        METHODNAME_DEF( MainUC, run )
        BLOG_TRACE_METHOD( m_Logger, fun );

        try
        {
            libutil::useCase::IRunnablePtr relevantCalculator = getUseCaseGetter()->getRelevantCalculatorUC();
            relevantCalculator->run();
        }
        catch( basar::Exception& e )
        {
            // todo: Deal with the exception and log
            BLOG_DEBUG( m_Logger, e.what() );
            e;
        }

    }
} // end namespace usecase
} // end namespace mainwarehousearticlesrelevantcalculator
