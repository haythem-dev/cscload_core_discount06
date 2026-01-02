//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/mainwarehouse/mainwarehouseacc.h"
#include "infrastructure/accessor/mainwarehouse/mainwarehouseacc_definitions.h"

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
namespace mainwarehouse
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::MAINWAREHOUSE_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO_MAINWAREHOUSE	)

            ACCESS_METHOD( lit::SELECT_MAINWAREHOUSE_BY_BRANCH )
                SQL_BUILDER_CREATE   ( SelectMainwarehouseByBranch )
                SQL_BUILDER_PUSH_BACK( SelectMainwarehouseByBranch )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectMainwarehouseByBranch )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectMainwarehouseByBranch )

        bool SelectMainwarehouseByBranch::isExecutable() const
        {
            METHODNAME_DEF( SelectMainwarehouseByBranch, isExecutable );
            static const log4cplus::Logger& logger = LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectMainwarehouseByBranch::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT mainbranchno AS "                                            + properties::BRANCH_NO_MAINWAREHOUSE.getName()  +
                " FROM pusatellite2mainbranch"
                " WHERE satellitebranchno = "                                        + properties::BRANCH_NO.toSQLReplacementString() 
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( LoggerPool::getLoggerAccessors() );
        }

} // end namespace mainwarehouse
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
