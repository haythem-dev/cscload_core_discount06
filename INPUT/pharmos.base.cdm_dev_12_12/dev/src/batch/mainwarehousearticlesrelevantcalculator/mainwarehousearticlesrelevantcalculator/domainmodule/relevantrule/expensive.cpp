#include "expensive.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Expensive::Expensive( basar::Decimal priceBorder )
        : m_PriceBorder( priceBorder )
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << ">: priceBorder=" << m_PriceBorder.toString(2) << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Expensive::~Expensive()
    {
    }

    RuleDescription Expensive::getDescription() const
    {
        return RuleDescription( RuleDescription::EXPENSIVE );
    }

    infrastructure::dataType::Trilean Expensive::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Decimal purchasePrice = articleData->getDecimal( properties::PURCHASING_PRICE );
        const infrastructure::dataType::Trilean relevance = purchasePrice >= m_PriceBorder ? infrastructure::dataType::Trilean::T_FALSE 
                                                                                           : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << purchasePrice << " >= " << m_PriceBorder << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
