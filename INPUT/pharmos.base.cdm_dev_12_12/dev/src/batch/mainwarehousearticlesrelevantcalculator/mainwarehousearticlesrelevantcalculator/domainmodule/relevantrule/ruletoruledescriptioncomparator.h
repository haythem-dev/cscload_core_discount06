#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULETORULEDESCRIPTIONCOMPARATOR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULETORULEDESCRIPTIONCOMPARATOR_H

#include "ruledescription.h"
#include "irelevantrule.h"
#include "irelevantruleptr.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    // comparison class for algorithm
    class RuleToRuleDescriptionComparator
    {
        RuleDescription m_RuleDescription;

    public:
        RuleToRuleDescriptionComparator( RuleDescription desc )
            : m_RuleDescription( desc )
        {
        }

        bool operator()( IRelevantRulePtr rule )
        {
            return rule->getDescription() == m_RuleDescription;
        }
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULETORULEDESCRIPTIONCOMPARATOR_H 
