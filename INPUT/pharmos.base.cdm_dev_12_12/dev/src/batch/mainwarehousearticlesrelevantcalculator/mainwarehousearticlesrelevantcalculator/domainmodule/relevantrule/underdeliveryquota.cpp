#include "underdeliveryquota.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
	namespace domMod
	{
		namespace relevantRule
		{
			UnderDeliveryQuota::UnderDeliveryQuota(basar::Int32 underDeliveryQuotaCount)
				: m_UnderDeliveryQuotaCount(underDeliveryQuotaCount)
			{
				std::ostringstream oss;
				oss << "rule <" << getDescription().toString() << ">: min=" << m_UnderDeliveryQuotaCount << " created.";
				BLOG_INFO(LoggerPool::getLoggerDomModules(), oss.str());

			}

			UnderDeliveryQuota::~UnderDeliveryQuota()
			{
			}

			RuleDescription UnderDeliveryQuota::getDescription() const
			{
				return RuleDescription(RuleDescription::UNDERDELIVERYQUOTA);
			}

			infrastructure::dataType::Trilean UnderDeliveryQuota::isRelevant(infrastructure::dataProvider::IDataProviderPtr articleData) const
			{
				const basar::Int32 underDeliveryQuotaLimit = articleData->getInt32(properties::UNDERDELIVERYQUOTA_LIMIT);
				const basar::Int32 underDeliveryQuotaVal = articleData->getInt32(properties::UNDERDELIVERYQUOTA_VAL);
				const infrastructure::dataType::Trilean relevance = underDeliveryQuotaVal > underDeliveryQuotaLimit ? infrastructure::dataType::Trilean::T_FALSE
					: infrastructure::dataType::Trilean::T_UNKNOWN;
				std::ostringstream oss;
				oss << getDescription().toString() << ": " << underDeliveryQuotaVal << " > " << underDeliveryQuotaLimit << " => " << relevance;
				BLOG_DEBUG(LoggerPool::getLoggerDomModules(), oss.str());

				return relevance;
			}

		} // end namespace relevantRule
	} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
