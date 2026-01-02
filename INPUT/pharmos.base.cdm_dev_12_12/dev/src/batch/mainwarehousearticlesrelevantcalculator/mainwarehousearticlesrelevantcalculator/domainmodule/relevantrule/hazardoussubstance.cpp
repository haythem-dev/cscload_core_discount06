#include "hazardoussubstance.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    HazardousSubstance::HazardousSubstance()
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );

    }

    HazardousSubstance::~HazardousSubstance()
    {
    }

    RuleDescription HazardousSubstance::getDescription() const
    {
        return RuleDescription( RuleDescription::HAZARDOUSSUBSTANCE );
    }

    infrastructure::dataType::Trilean HazardousSubstance::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool isHazardous = articleData->getInt16( properties::HAZARDOUS_SUBSTANCE_OLD ) > 0 ||
                                 articleData->getInt16( properties::HAZARDOUS_SUBSTANCE_NEW ) > 0;
        const infrastructure::dataType::Trilean relevance = isHazardous ? infrastructure::dataType::Trilean::T_FALSE 
                                                                        : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Is hazardous " << isHazardous << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
