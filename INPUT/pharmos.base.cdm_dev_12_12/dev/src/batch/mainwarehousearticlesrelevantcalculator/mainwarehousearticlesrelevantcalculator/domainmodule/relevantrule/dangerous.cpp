#include "dangerous.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Dangerous::Dangerous()
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Dangerous::~Dangerous()
    {
    }

    RuleDescription Dangerous::getDescription() const
    {
        return RuleDescription( RuleDescription::DANGEROUS );
    }

    infrastructure::dataType::Trilean Dangerous::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool dangerousFlag = ! articleData->getString( properties::UN_NO ).empty();
        const infrastructure::dataType::Trilean relevance = dangerousFlag ? infrastructure::dataType::Trilean::T_FALSE 
                                                                          : infrastructure::dataType::Trilean::T_UNKNOWN;


        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Dangerous flag is " << dangerousFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
