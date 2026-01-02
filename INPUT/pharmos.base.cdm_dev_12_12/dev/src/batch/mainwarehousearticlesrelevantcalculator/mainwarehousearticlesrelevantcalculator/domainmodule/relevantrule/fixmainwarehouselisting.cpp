#include "fixmainwarehouselisting.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    FixMainWarehouseListing::FixMainWarehouseListing()
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << "> created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    FixMainWarehouseListing::~FixMainWarehouseListing()
    {
    }

    RuleDescription FixMainWarehouseListing::getDescription() const
    {
        return RuleDescription( RuleDescription::FIX_MAINWAREHOUSE_LISTING );
    }

    infrastructure::dataType::Trilean FixMainWarehouseListing::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        infrastructure::dataType::Trilean relevance; // set to unknown

        const basar::Int32 manualSignedZDP = articleData->getString( properties::MANUAL_SIGNED_ZDP ).stoi();
        switch( manualSignedZDP )
        {
        case 0: // keine Steuerung über dieses Feld = unknown
            break; 
        case 8: // fix vom SH ausgeschlossen
            relevance = infrastructure::dataType::Trilean::T_FALSE;
            break;
        default: // fix auf SH verschlüsselt
            relevance = infrastructure::dataType::Trilean::T_TRUE;
            break;
        }

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Value is " << manualSignedZDP << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
