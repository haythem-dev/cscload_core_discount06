#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATOR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATOR_H

#include "domainmodule/article/iarticleptr.h"

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantCalculator
{
    class IRelevantCalculator
    {
    public:
        virtual ~IRelevantCalculator() {}

        virtual void                                         calculate() = 0;
    };

} // end namespace relevantCalculator
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATOR_H
