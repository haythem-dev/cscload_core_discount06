#include "centralpurchaseblockedarticle.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    CentralPurchaseBlockedArticle::CentralPurchaseBlockedArticle()
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    CentralPurchaseBlockedArticle::~CentralPurchaseBlockedArticle()
    {
    }

    RuleDescription CentralPurchaseBlockedArticle::getDescription() const
    {
        return RuleDescription( RuleDescription::CENTRALPURCHASEBLOCKEDARTICLE );
    }

    infrastructure::dataType::Trilean CentralPurchaseBlockedArticle::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool lockedFlag = articleData->getString( properties::CENTRALPURCHASE_LOCKED_FLAG ) == "1";
        const infrastructure::dataType::Trilean relevance = lockedFlag ? infrastructure::dataType::Trilean::T_FALSE 
                                                                       : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Lock flag is " << lockedFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
