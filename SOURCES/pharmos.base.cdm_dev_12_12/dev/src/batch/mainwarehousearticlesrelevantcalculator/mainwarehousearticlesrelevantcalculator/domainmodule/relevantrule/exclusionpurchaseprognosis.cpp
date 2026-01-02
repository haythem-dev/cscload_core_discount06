#include "exclusionpurchaseprognosis.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    ExclusionPurchasePrognosis::ExclusionPurchasePrognosis( basar::Int32 days, basar::Int32 prognosisLimit )
        : m_Days( days ), m_PrognosisLimit( prognosisLimit )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: days=" << m_Days << ", limit=" << m_PrognosisLimit << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    ExclusionPurchasePrognosis::~ExclusionPurchasePrognosis()
    {
    }

    RuleDescription ExclusionPurchasePrognosis::getDescription() const
    {
        return RuleDescription( RuleDescription::EXCLUSION_PURCHASE_PROGNOSIS );
    }

    infrastructure::dataType::Trilean ExclusionPurchasePrognosis::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Decimal prognosis( articleData->getFloat64( properties::PROGNOSIS ) * m_Days );
        const bool exclusion = prognosis > m_PrognosisLimit;
        const infrastructure::dataType::Trilean relevance = exclusion ? infrastructure::dataType::Trilean::T_FALSE 
                                                                      : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << prognosis << " > " << m_PrognosisLimit << ": " << exclusion << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
