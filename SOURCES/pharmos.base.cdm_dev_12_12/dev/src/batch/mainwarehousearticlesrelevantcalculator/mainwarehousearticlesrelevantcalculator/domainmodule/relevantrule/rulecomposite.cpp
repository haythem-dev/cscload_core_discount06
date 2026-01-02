#include "rulecomposite.h"

#include "ruletoruledescriptioncomparator.h"
#include <algorithm>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    RuleComposite::RuleComposite()
        : m_RuleDescription( RuleDescription::RULE_COMPOSITE )
    {
    }

    RuleComposite::~RuleComposite()
    {
    }

    void RuleComposite::addRule( IRelevantRulePtr rule )
    {
        m_RelevantRules.push_back( rule );
    }

    void RuleComposite::addRuleBefore( RuleDescription desc, IRelevantRulePtr rule )
    {
        RelevantRuleCollection::iterator it = std::find_if( m_RelevantRules.begin(), m_RelevantRules.end(), 
                                                            RuleToRuleDescriptionComparator( desc ) );
        m_RelevantRules.insert( it, rule );
    }

    void RuleComposite::addRuleAfter( RuleDescription desc, IRelevantRulePtr rule )
    {
        RelevantRuleCollection::iterator it = std::find_if( m_RelevantRules.begin(), m_RelevantRules.end(), 
                                                            RuleToRuleDescriptionComparator( desc ) );
        if( it != m_RelevantRules.end() )
        {
            m_RelevantRules.insert( ++it, rule );
        }
        else
        {
            addRule( rule );
        }
    }

    bool RuleComposite::contains( RuleDescription desc ) const
    {
        return std::find_if( m_RelevantRules.begin(), m_RelevantRules.end(), RuleToRuleDescriptionComparator( desc ) ) != m_RelevantRules.end();
    }

    bool RuleComposite::empty() const
    {
        return m_RelevantRules.empty();
    }

    RuleComposite::const_iterator RuleComposite::begin() const
    {
        return m_RelevantRules.begin();
    }

    RuleComposite::const_iterator RuleComposite::end() const
    {
        return m_RelevantRules.end();
    }

    RuleDescription RuleComposite::getDescription() const
    {
        return m_RuleDescription;
    }

    infrastructure::dataType::Trilean RuleComposite::isRelevant( infrastructure::dataProvider::IDataProviderPtr data ) const
    {
        infrastructure::dataType::Trilean relevant;
        for( RelevantRuleCollection::const_iterator it = m_RelevantRules.begin(); it != m_RelevantRules.end() && relevant.isUnknown(); ++it )
        {
            const IRelevantRulePtr rule = *it;

            const infrastructure::dataType::Trilean relevance = rule->isRelevant( data );
            if( ! relevance.isUnknown() )
            {
                relevant = relevance;
                m_RuleDescription = rule->getDescription();
            }
        }
        
        return relevant;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
