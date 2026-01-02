#include "cool.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    Cool::Cool( basar::Int32 coolBorder )
        : m_CoolBorder( coolBorder )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: coolBorder=" << m_CoolBorder << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    Cool::~Cool()
    {
    }

    RuleDescription Cool::getDescription() const
    {
        return RuleDescription( RuleDescription::COOL );
    }

    infrastructure::dataType::Trilean Cool::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::Int32 articleCoolMode = articleData->getString( properties::COOL_ARTICLE_MODE ).stoi();
        infrastructure::dataType::Trilean relevance; // unknown

        if( m_CoolBorder > 4 || m_CoolBorder < 0 )
        {
			BLOG_WARN( LoggerPool::getLoggerDomModules(), "invalid cool border set at exclusion!" );
        }

		if( 0 == articleCoolMode || 0 == m_CoolBorder ) // no cool article at all / no exclusion at all
        {
            // keep unknown
        }
		else if( 4 == articleCoolMode ) // 4=Kühlkette
        {
			relevance = infrastructure::dataType::Trilean::T_FALSE; // cold chain article always excluded as coolBorder != 0
        }
		else if( 4 == m_CoolBorder ) // 4=Kühlkette
        {
            // keep unknown
        }
        else
        {
            relevance = m_CoolBorder >= articleCoolMode ? infrastructure::dataType::Trilean::T_FALSE 
                                                        : infrastructure::dataType::Trilean::T_UNKNOWN; // 1=8; 2=20; 3=25 Grad
        }

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Article cool mode "  << articleCoolMode << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
