#include "narcotic.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Narcotic::Narcotic()
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Narcotic::~Narcotic()
    {
    }

    RuleDescription Narcotic::getDescription() const
    {
        return RuleDescription( RuleDescription::NARCOTIC );
    }

    infrastructure::dataType::Trilean Narcotic::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        bool narcoticFlag = articleData->getString( properties::NARCOTIC_FLAG ) == "1";
        const infrastructure::dataType::Trilean relevance = narcoticFlag ? infrastructure::dataType::Trilean::T_FALSE 
                                                                         : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Narcotics flag " << narcoticFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
