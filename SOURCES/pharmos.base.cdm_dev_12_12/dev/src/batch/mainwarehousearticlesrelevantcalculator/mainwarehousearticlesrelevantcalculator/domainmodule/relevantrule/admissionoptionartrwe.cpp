#include "admissionoptionartrwe.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
	AdmissionOptionArtrwe::AdmissionOptionArtrwe( )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

	AdmissionOptionArtrwe::~AdmissionOptionArtrwe()
    {
    }

    RuleDescription AdmissionOptionArtrwe::getDescription() const
    {
        return RuleDescription( RuleDescription::ADMISSION_OPTION_ARTRWE );
    }

    infrastructure::dataType::Trilean AdmissionOptionArtrwe::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
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
