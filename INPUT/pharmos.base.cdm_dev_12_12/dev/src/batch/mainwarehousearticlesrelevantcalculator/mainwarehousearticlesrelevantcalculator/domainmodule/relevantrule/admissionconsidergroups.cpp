#include "admissionconsidergroups.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
	AdmissionConsiderGroups::AdmissionConsiderGroups( )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

	AdmissionConsiderGroups::~AdmissionConsiderGroups()
    {
    }

    RuleDescription AdmissionConsiderGroups::getDescription() const
    {
        return RuleDescription( RuleDescription::ADMISSION_CONSIDER_GROUPS );
    }

    infrastructure::dataType::Trilean AdmissionConsiderGroups::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
		bool apg = (articleData->getInt16(properties::ADMISSION_PARAM_GROUPID) == 1);
        /*
		// from the documentation of this rule the relevance should be set to true, if a matching admission param group is found,
		// many other rules it is set to false, as they are exclusion rules
        // in this case an extra relevant_type T_ACG will be created as the final decision if its relevant or not cannot be given here
        // the admission param group conditions will be checked (and therefore the relevance) in the caller after all rules are run through
        // IMPORTANT INFO: this rule must be always the last in the prio order of rules, as no rule afterwards would be called because of this relevance type.
        */
        const infrastructure::dataType::Trilean relevance = infrastructure::dataType::Trilean::T_ACG;
        std::ostringstream oss;
		oss << getDescription().toString() << ": " << "Rule 24 ACG isRelevant ADMISSION_PARAM_GROUPID = " << apg << " relevance = " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
