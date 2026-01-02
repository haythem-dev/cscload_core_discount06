#include "registrable.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Registrable::Registrable()
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Registrable::~Registrable()
    {
    }

    RuleDescription Registrable::getDescription() const
    {
        return RuleDescription( RuleDescription::REGISTRABLE );
    }

    infrastructure::dataType::Trilean Registrable::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool registrableFlag = articleData->getString( properties::REGISTRABLE_FLAG ) == "1";
        const infrastructure::dataType::Trilean relevance = registrableFlag ? infrastructure::dataType::Trilean::T_FALSE 
                                                                            : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Registrable flag " << registrableFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
