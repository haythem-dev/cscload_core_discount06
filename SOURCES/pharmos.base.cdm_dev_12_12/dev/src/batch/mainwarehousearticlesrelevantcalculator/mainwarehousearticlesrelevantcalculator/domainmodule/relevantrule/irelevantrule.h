#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRELEVANTRULE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRELEVANTRULE_H

#include "ruledescription.h"
#include "infrastructure/datatype/trilean.h"
#include "infrastructure/dataprovider/idataproviderptr.h"

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class IRelevantRule
    {
    public:
        virtual ~IRelevantRule() {}

        virtual RuleDescription                   getDescription()                                             const = 0;
        virtual infrastructure::dataType::Trilean isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const = 0;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRELEVANTRULE_H
