#include "creationdate.h"
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
    CreationDate::CreationDate( basar::Int32 month )
    {
        libutil::misc::DateTime checkDate = basar::Date::getCurrent();
        
		checkDate.addMonths( month * -1 ); // subtract month

        m_CheckDate = checkDate.getDateTime().getDate();

		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: checkDate=" << m_CheckDate.getDate() << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
	}

    CreationDate::~CreationDate()
    {
    }

    RuleDescription CreationDate::getDescription() const
    {
        return RuleDescription( RuleDescription::CREATION_DATE );
    }

    infrastructure::dataType::Trilean CreationDate::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Date creationDate = articleData->getDate( properties::CREATION_DATE );

        infrastructure::dataType::Trilean relevance;
        if( creationDate.isValid() && creationDate.getDate() > m_CheckDate.getDate() )
        {
            relevance = infrastructure::dataType::Trilean::T_FALSE;
        }

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << creationDate << " > " << m_CheckDate << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
