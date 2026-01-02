//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/assignmentparameter/mainwarehouseassignmentparameteracc.h"
#include "infrastructure/accessor/assignmentparameter/mainwarehouseassignmentparameteracc_definitions.h"
#include "infrastructure/accessor/assignmentparameter/assignmentparameteracc_definitions.h"

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
namespace assignmentParameter
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::MAINWAREHOUSE_ASSIGNMENTPARAMETER_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO				)
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CONTEXT_NAME				)
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_INT        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_DEC        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_STR        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::INT_INTERVAL_START       )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::INT_INTERVAL_END		    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::RULEID                   )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::STRING_INTERVAL_START    )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::STRING_INTERVAL_END		)

            ACCESS_METHOD( lit::SELECT_ASSIGNMENT_PARAMETER_BY_BRANCH )
                SQL_BUILDER_CREATE   ( SelectMainwarehouseAssignmentParameterByBranch )
                SQL_BUILDER_PUSH_BACK( SelectMainwarehouseAssignmentParameterByBranch )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectMainwarehouseAssignmentParameterByBranch )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectMainwarehouseAssignmentParameterByBranch )

        bool SelectMainwarehouseAssignmentParameterByBranch::isExecutable() const
        {
            METHODNAME_DEF( SelectMainwarehouseAssignmentParameterByBranch, isExecutable );
            static const log4cplus::Logger& logger = LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectMainwarehouseAssignmentParameterByBranch::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT p.branchno AS "                                              + properties::BRANCH_NO.getName()                +
                     ", r.contextname AS "                                           + properties::CONTEXT_NAME.getName()             +
                     ", r.ruleid AS "                                                + properties::RULEID.getName()                   +
					 ", p.comparevalue AS "                                          + properties::COMPARE_VALUE_INT.getName()        +
					 ", p.comparevaluedecimal AS "                                   + properties::COMPARE_VALUE_DEC.getName()        +
					 ", p.comparevaluestring AS "                                    + properties::COMPARE_VALUE_STR.getName()        +
					 ", p.startvaluestring AS "                                      + properties::STRING_INTERVAL_START.getName()    +
					 ", p.endvaluestring AS "                                        + properties::STRING_INTERVAL_END.getName()      +
                     ", p.startvalueinteger AS "                                     + properties::INT_INTERVAL_START.getName()       +
                     ", p.endvalueinteger AS "                                       + properties::INT_INTERVAL_END.getName()         +
                     ", CASE WHEN p.branchno = "                                     + properties::BRANCH_NO.toSQLReplacementString() +
                      " THEN 1 ELSE 0 END AS precedence"              // used to give mainwarehouse rule preference over satellite rule
                " FROM pumainwarehouseassignmentrule r"
                " JOIN pumainwarehouseassignmentparam p ON p.ruleid = r.ruleid"
                " WHERE p.activationflag = 1 AND (p.branchno = "                     + properties::BRANCH_NO.toSQLReplacementString() +
                " OR p.branchno = (SELECT mainbranchno from pusatellite2mainbranch "
                "WHERE satellitebranchno = "                                         + properties::BRANCH_NO.toSQLReplacementString() + 
                "))"
                " ORDER BY r.ruleid ASC, precedence ASC"
            );

            resolve( constSQL );
            basar::VarString sql = getSQLString();
            BLOG_TRACE_SQLSTRING( LoggerPool::getLoggerAccessors() );
        }

} // end namespace assignmentParameter
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
