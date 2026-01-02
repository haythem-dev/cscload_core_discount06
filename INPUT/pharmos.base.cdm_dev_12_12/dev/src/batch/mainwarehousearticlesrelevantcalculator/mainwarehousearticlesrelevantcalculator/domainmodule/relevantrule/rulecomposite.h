#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULECOMPOSITE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULECOMPOSITE_H

#include "irelevantrule.h"
#include "irelevantruleptr.h"

#include <list>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class RuleComposite : public IRelevantRule
    {
    public:
        RuleComposite();
        ~RuleComposite();

        typedef std::list< IRelevantRulePtr >          RelevantRuleCollection;
        typedef RelevantRuleCollection::const_iterator const_iterator;

        void                                           addRule( IRelevantRulePtr );

        // Use these methods to build rule priorities e.g. if rule <rule1> has a bigger priority than
        // <rule2> than call it like that: 
        // addRuleBefore( RULE2, rule1 ); // <rule1> is put before <rule2> into the list
        // addRuleAfter( RULE1, rule2);   // <rule2> is put after  <rule1> into the list
        void                                           addRuleBefore( RuleDescription, IRelevantRulePtr );
        void                                           addRuleAfter ( RuleDescription, IRelevantRulePtr );

        bool                                           contains( RuleDescription ) const;
        bool                                           empty()                     const;

        const_iterator                                 begin() const;
        const_iterator                                 end()   const;

        // from IRelevantRule interface
        RuleDescription                                getDescription() const;
        infrastructure::dataType::Trilean              isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        RelevantRuleCollection                         m_RelevantRules;
        mutable RuleDescription                        m_RuleDescription;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_RULECOMPOSITE_H
