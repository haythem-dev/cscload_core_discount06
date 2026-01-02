//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/storagelocationslot/storagelocationslotacc.h"
#include "infrastructure/accessor/storagelocationslot/storagelocationslotacc_definitions.h"

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
namespace storageSlot
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::STORAGESLOT_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::STORAGE_LOCATION	)

            ACCESS_METHOD( lit::SELECT_PSEUDO_STORAGE_SLOT_BY_BRANCH )
                SQL_BUILDER_CREATE   ( SelectPseudoStorageSlotByBranch )
                SQL_BUILDER_PUSH_BACK( SelectPseudoStorageSlotByBranch )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectPseudoStorageSlotByBranch )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectPseudoStorageSlotByBranch )

        bool SelectPseudoStorageSlotByBranch::isExecutable() const
        {
            METHODNAME_DEF( SelectPseudoStorageSlotByBranch, isExecutable );
            static const log4cplus::Logger& logger = LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectPseudoStorageSlotByBranch::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT pseudolagerort AS "                                          + properties::STORAGE_LOCATION.getName()         +
                " FROM rfiliale"
                " WHERE filialnr = "                                                 + properties::BRANCH_NO.toSQLReplacementString() 
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( LoggerPool::getLoggerAccessors() );
        }

} // end namespace storageSlot
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
