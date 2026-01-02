#include "admissionpurchaseprognosis.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    AdmissionPurchasePrognosis::AdmissionPurchasePrognosis( basar::Int32 days, basar::Int32 prognosisLimit )
        : m_Days( days ), m_PrognosisLimit( prognosisLimit )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: days=" << m_Days << ", limit=" << m_PrognosisLimit << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    AdmissionPurchasePrognosis::~AdmissionPurchasePrognosis()
    {
    }

    RuleDescription AdmissionPurchasePrognosis::getDescription() const
    {
        return RuleDescription( RuleDescription::ADMISSION_PURCHASE_PROGNOSIS );
    }

    infrastructure::dataType::Trilean AdmissionPurchasePrognosis::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Decimal prognosis( articleData->getFloat64( properties::PROGNOSIS ) * m_Days );
        const bool admission = prognosis < m_PrognosisLimit;
        const infrastructure::dataType::Trilean relevance = admission ? infrastructure::dataType::Trilean::T_TRUE 
                                                                      : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << prognosis << " < " << m_PrognosisLimit << ": " << admission << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
