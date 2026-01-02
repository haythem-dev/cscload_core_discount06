#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_HAZARDOUSSUBSTANCE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_HAZARDOUSSUBSTANCE_H

#include "irelevantrule.h"

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class HazardousSubstance : public IRelevantRule
    {
    public:
        HazardousSubstance();
        ~HazardousSubstance();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_HAZARDOUSSUBSTANCE_H
