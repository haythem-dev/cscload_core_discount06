//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "relevantcalculatoruc.h"

#include "domainmodule/relevantcalculator/irelevantcalculator.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace useCase
{
    RelevantCalculatorUC::RelevantCalculatorUC()
    : m_Logger( mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerUseCases() )
    {
        METHODNAME_DEF( RelevantCalculatorUC, RelevantCalculatorUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    RelevantCalculatorUC::~RelevantCalculatorUC()
    {
        METHODNAME_DEF( RelevantCalculatorUC, ~RelevantCalculatorUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void RelevantCalculatorUC::injectRelevantCalculator( domMod::relevantCalculator::IRelevantCalculatorPtr calc )
    {
        m_RelevantCalculator = calc;
    }

    domMod::relevantCalculator::IRelevantCalculatorPtr RelevantCalculatorUC::getRelevantCalculator() const
    {
        CHECK_INSTANCE_EXCEPTION( m_RelevantCalculator.get() );
        return m_RelevantCalculator;
    }

    void RelevantCalculatorUC::run()
    {
        METHODNAME_DEF( RelevantCalculatorUC, run )
        BLOG_TRACE_METHOD( m_Logger, fun );

        try
        {
            getRelevantCalculator()->calculate();
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
