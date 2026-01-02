#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORY_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORY_H

#include "domainmodule/relevantrule/irelevantruleptr.h"
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    class IRelevantRuleFactory
    {
    public:
        virtual ~IRelevantRuleFactory() {}

        virtual domMod::relevantRule::IRelevantRulePtr create( basar::Int16 branchNo ) = 0;
    };

}// end namespace componentManager
}// end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORY_H
