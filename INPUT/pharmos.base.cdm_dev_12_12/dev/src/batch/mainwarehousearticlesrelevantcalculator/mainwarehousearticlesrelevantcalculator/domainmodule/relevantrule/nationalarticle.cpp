#include "nationalarticle.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    NationalArticle::NationalArticle( basar::Int32 nationalArticleMinimalCount )
        : m_NationalArticleMinimalCount( nationalArticleMinimalCount )
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << ">: min=" << m_NationalArticleMinimalCount << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );

    }

    NationalArticle::~NationalArticle()
    {
    }

    RuleDescription NationalArticle::getDescription() const
    {
        return RuleDescription( RuleDescription::NATIONALARTICLE );
    }

    infrastructure::dataType::Trilean NationalArticle::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Int32 ibtRelevantCount = articleData->getInt32( properties::IBT_RELEVANT_COUNT );
        const infrastructure::dataType::Trilean relevance = ibtRelevantCount >= m_NationalArticleMinimalCount ? infrastructure::dataType::Trilean::T_FALSE 
                                                                                                              : infrastructure::dataType::Trilean::T_UNKNOWN;


        std::ostringstream oss;
        oss << getDescription().toString() << ": " << ibtRelevantCount << " >= " << m_NationalArticleMinimalCount << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
