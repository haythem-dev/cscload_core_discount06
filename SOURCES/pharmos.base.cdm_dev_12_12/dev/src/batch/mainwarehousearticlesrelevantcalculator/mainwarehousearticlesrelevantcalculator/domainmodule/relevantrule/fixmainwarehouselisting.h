#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_FIXMAINWAREHOUSELISTING_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_FIXMAINWAREHOUSELISTING_H

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
    class FixMainWarehouseListing : public IRelevantRule
    {
    public:
        FixMainWarehouseListing();
        ~FixMainWarehouseListing();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_FIXMAINWAREHOUSELISTING_H
