#include "outoftradearticle.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include <libutil/misc/datetime/datetime.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    OutOfTradeArticle::OutOfTradeArticle( basar::Int32 month )
    {
        libutil::misc::DateTime checkDate = basar::Date::getCurrent();

		checkDate.addMonths( month * -1 );

        m_CheckDate = checkDate.getDate();

		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: checkDate=" << m_CheckDate.getDate() << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    OutOfTradeArticle::~OutOfTradeArticle()
    {
    }

    RuleDescription OutOfTradeArticle::getDescription() const
    {
        return RuleDescription( RuleDescription::OUTOFTRADEARTICLE );
    }

    infrastructure::dataType::Trilean OutOfTradeArticle::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Date outsaleDate = articleData->getDate( properties::OUTSALE_DATE );
        infrastructure::dataType::Trilean relevance; // set to unknown

        if( outsaleDate.isValid() )
        {
            relevance = outsaleDate.getDate() <= m_CheckDate.getDate() ? infrastructure::dataType::Trilean::T_FALSE 
                                                                       : infrastructure::dataType::Trilean::T_UNKNOWN;
        }

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << outsaleDate << " <= " << m_CheckDate << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
