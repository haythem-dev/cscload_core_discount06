#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATORPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATORPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantCalculator
{
    class IRelevantCalculator;
    typedef boost::shared_ptr< IRelevantCalculator > IRelevantCalculatorPtr;

} // end namespace relevantCalculator
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTCALCULATOR_IRELEVANTCALCULATORPTR_H
