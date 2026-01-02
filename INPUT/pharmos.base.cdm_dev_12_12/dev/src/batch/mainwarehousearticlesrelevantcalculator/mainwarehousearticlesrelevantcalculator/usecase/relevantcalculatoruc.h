#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_RELEVANTCALCULATORUC_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_RELEVANTCALCULATORUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "domainmodule/relevantcalculator/irelevantcalculatorptr.h"

#include <libutil/irunnable.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace useCase
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration
    //-------------------------------------------------------------------------------------------------//
    class RelevantCalculatorUC : public libutil::useCase::IRunnable
    {
    public:
        RelevantCalculatorUC();
        ~RelevantCalculatorUC();

        void                                               injectRelevantCalculator( domMod::relevantCalculator::IRelevantCalculatorPtr );

        // from IRunnable interface
        void                                               run();

    private:
        RelevantCalculatorUC(const RelevantCalculatorUC& );
        RelevantCalculatorUC& operator= (const RelevantCalculatorUC& );

        domMod::relevantCalculator::IRelevantCalculatorPtr getRelevantCalculator() const;

    private:
        const log4cplus::Logger&                           m_Logger;
        domMod::relevantCalculator::IRelevantCalculatorPtr m_RelevantCalculator;
    };
} // namespace useCase
} // namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_RELEVANTCALCULATORUC_H
