#include "regionalarticle.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
	namespace domMod
	{
		namespace relevantRule
		{
			RegionalArticle::RegionalArticle()
			{
				std::ostringstream oss;
				oss << "rule <" << getDescription().toString() << "> created.";
				BLOG_INFO(LoggerPool::getLoggerDomModules(), oss.str());
			}

			RegionalArticle::~RegionalArticle()
			{
			}

			RuleDescription RegionalArticle::getDescription() const
			{
				return RuleDescription(RuleDescription::REGIONALARTICLE);
			}

			infrastructure::dataType::Trilean RegionalArticle::isRelevant(infrastructure::dataProvider::IDataProviderPtr articleData) const
			{
				bool regionalArticleFlag = articleData->getString(properties::REGIONALARTICLE_FLAG) == "1";
				const infrastructure::dataType::Trilean relevance = regionalArticleFlag ? infrastructure::dataType::Trilean::T_FALSE
					: infrastructure::dataType::Trilean::T_UNKNOWN;

				std::ostringstream oss;
				oss << getDescription().toString() << ": " << "RegionalArticles flag " << regionalArticleFlag << " => " << relevance;
				BLOG_DEBUG(LoggerPool::getLoggerDomModules(), oss.str());

				return relevance;
			}

		} // end namespace relevantRule
	} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
