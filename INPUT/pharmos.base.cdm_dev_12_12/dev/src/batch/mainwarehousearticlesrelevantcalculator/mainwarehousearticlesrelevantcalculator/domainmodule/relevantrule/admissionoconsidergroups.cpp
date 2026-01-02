#include "admissionoconsidergroups.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    AdmissionConsiderGroups::AdmissionConsiderGroups(basar::Int16 flags):m_Flags( flags )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> flags =" << m_Flags << " created.";
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    AdmissionConsiderGroups::~AdmissionConsiderGroups()
    {
    }

    RuleDescription AdmissionConsiderGroups::getDescription() const
    {
        return RuleDescription( RuleDescription::ADMISSION_CONSIDER_GROUPS);
    }

    infrastructure::dataType::Trilean AdmissionConsiderGroups::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
		bool stammLagerFlag = (articleData->getString(properties::STAMMLAGER_FLAG) == "1");
		// from the documentation of this rule I think, that the relevance should be set to true,
		// but for many other rules it is set to false, so I'm not 100% sure
		const infrastructure::dataType::Trilean relevance = stammLagerFlag ? infrastructure::dataType::Trilean::T_TRUE
			: infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
		oss << getDescription().toString() << ": " << "Stammlagerkennz " << stammLagerFlag << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
