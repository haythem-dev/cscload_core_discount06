#include "withoutactivebinlocation.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "domainmodule/storagelocation/istoragelocationslotchecker.h"
#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    WithoutActiveBinLocation::WithoutActiveBinLocation( storageLocation::IStorageLocationSlotCheckerPtr storageLocChecker )
        : m_StorageLocationSlotChecker( storageLocChecker )
    {
		std::ostringstream oss;
		oss << "rule <" << getDescription().toString() << ">: pseudo=" << m_StorageLocationSlotChecker->getPseudoStorageLocation() << " created." ;
        BLOG_INFO( LoggerPool::getLoggerDomModules(), oss.str() );
    }

    WithoutActiveBinLocation::~WithoutActiveBinLocation()
    {
    }

    bool WithoutActiveBinLocation::hasStorageLocation( const basar::VarString& storageLocationSlot ) const
    {
        return m_StorageLocationSlotChecker->hasStorageLocation( storageLocationSlot );
    }

    basar::VarString WithoutActiveBinLocation::getPseudoStorageLocation() const
    {
        return m_StorageLocationSlotChecker->getPseudoStorageLocation();
    }

    RuleDescription WithoutActiveBinLocation::getDescription() const
    {
        return RuleDescription( RuleDescription::WITHOUT_ACTIVE_BINLOCATION );
    }

    infrastructure::dataType::Trilean WithoutActiveBinLocation::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        const basar::VarString storageloc = articleData->getString( properties::STORAGE_LOCATION );
        const infrastructure::dataType::Trilean relevance = hasStorageLocation( storageloc ) ? infrastructure::dataType::Trilean::T_UNKNOWN 
                                                                                             : infrastructure::dataType::Trilean::T_FALSE;

        std::ostringstream oss;
        oss << getDescription().toString() << ": " << "Storage location slot is " << storageloc 
            << ". Pseudo storage location slot is " << getPseudoStorageLocation() << ". => " << relevance;
        BLOG_DEBUG( LoggerPool::getLoggerDomModules(), oss.str() );

        return relevance;
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
