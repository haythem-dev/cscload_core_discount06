#include "specialarticletype.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    SpecialArticleType::SpecialArticleType()
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    SpecialArticleType::~SpecialArticleType()
    {
    }

    RuleDescription SpecialArticleType::getDescription() const
    {
        return RuleDescription( RuleDescription::SPECIALARTICLETYPE );
    }

    infrastructure::dataType::Trilean SpecialArticleType::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const bool specialArticleFlag = ! articleData->getString( properties::SPECIAL_ARTICLE_TYPE ).empty();
        const infrastructure::dataType::Trilean relevance = specialArticleFlag ? infrastructure::dataType::Trilean::T_FALSE 
                                                                               : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Special article flag is " << specialArticleFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
