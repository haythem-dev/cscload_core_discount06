#include "consignment.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Consignment::Consignment()
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Consignment::~Consignment()
    {
    }

    RuleDescription Consignment::getDescription() const
    {
        return RuleDescription( RuleDescription::CONSIGNMENT );
    }

    infrastructure::dataType::Trilean Consignment::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Int32 consigPartner = articleData->getInt32( properties::CONSIGNMENT_PARTNER_NO );
        const infrastructure::dataType::Trilean relevance = consigPartner != 0 ? infrastructure::dataType::Trilean::T_FALSE 
                                                                               : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Consignment partner no is " << consigPartner << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
