#include "batch.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Batch::Batch()
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Batch::~Batch()
    {
    }

    RuleDescription Batch::getDescription() const
    {
        return RuleDescription( RuleDescription::BATCH );
    }

    infrastructure::dataType::Trilean Batch::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool batchFlag = articleData->getString( properties::BATCH_FLAG ) == "1";
        const infrastructure::dataType::Trilean relevance = batchFlag ? infrastructure::dataType::Trilean::T_FALSE
                                                                      : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Batch flag is " << batchFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
