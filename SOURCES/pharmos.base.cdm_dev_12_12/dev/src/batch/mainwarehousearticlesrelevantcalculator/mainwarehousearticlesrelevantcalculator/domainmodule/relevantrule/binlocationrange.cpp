#include "binlocationrange.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"


namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    BinLocationRange::BinLocationRange( const StringInterval& binLocRange )
        : m_BinLocationRange( binLocRange )
    {
		std::ostringstream oss;
        oss << "rule <" << getDescription().toString() << ">: from=" << m_BinLocationRange.from() << ", to=" << m_BinLocationRange.to() << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    BinLocationRange::~BinLocationRange()
    {
    }

    RuleDescription BinLocationRange::getDescription() const
    {
        return RuleDescription( RuleDescription::BINLOCATIONRANGE );
    }

    infrastructure::dataType::Trilean BinLocationRange::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::VarString prop = properties::STORAGE_LOCATION;
        const basar::VarString storLoc = articleData->getString( prop );
        const infrastructure::dataType::Trilean relevance = m_BinLocationRange.contains( storLoc ) ? infrastructure::dataType::Trilean::T_FALSE 
                                                                                                   : infrastructure::dataType::Trilean::T_UNKNOWN;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "[" << m_BinLocationRange.from() << ", " << m_BinLocationRange.to()  << "]"
            << " contains " << storLoc << " => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
