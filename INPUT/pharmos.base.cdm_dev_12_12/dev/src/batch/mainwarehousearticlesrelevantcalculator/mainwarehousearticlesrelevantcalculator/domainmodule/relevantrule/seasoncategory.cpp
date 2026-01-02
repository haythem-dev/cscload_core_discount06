#include "seasoncategory.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    SeasonCategory::SeasonCategory( const basar::VarString& seasonGroup )
        : m_SeasonGroup( seasonGroup )
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << ">: group=" << m_SeasonGroup << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    SeasonCategory::~SeasonCategory()
    {
    }

    RuleDescription SeasonCategory::getDescription() const
    {
        return RuleDescription( RuleDescription::SEASONCATEGORY );
    }

    infrastructure::dataType::Trilean SeasonCategory::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::VarString sg1 = articleData->getString( properties::SEASON_GROUP_1 );
        const basar::VarString sg2 = articleData->getString( properties::SEASON_GROUP_2 );
        const basar::VarString sg3 = articleData->getString( properties::SEASON_GROUP_3 );

        const bool isSeasonGroup = sg1 == m_SeasonGroup || sg2 == m_SeasonGroup || sg3 == m_SeasonGroup;
        const infrastructure::dataType::Trilean relevance = isSeasonGroup ? infrastructure::dataType::Trilean::T_FALSE 
                                                                          : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Season group  " << m_SeasonGroup << " in [" << sg1 << ", " << sg2 << ", " << sg3 << "]"
            << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
