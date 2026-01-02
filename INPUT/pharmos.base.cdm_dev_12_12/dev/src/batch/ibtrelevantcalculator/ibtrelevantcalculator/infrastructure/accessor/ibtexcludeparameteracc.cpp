//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/ibtexcludeparameteracc.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/ibtexcludeparameteracc_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
    namespace ibtexcludeparameter
    {

    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( accessor::ibtexcludeparameter::lit::IBT_EXCLUSION_CRITERIA_ACC )

            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CONTEXT_NAME				)
				PROPERTY_DESCRIPTION_LIST_ADD( properties::PSEUDO_STORAGE_LOCATION  )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_INT        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_DEC        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_VALUE_STR        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::INTERVAL_START           )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::INTERVAL_END				)
            END_PROPERTY_DESCRIPTION_LIST

                ACCESS_METHOD( accessor::ibtexcludeparameter::lit::SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH );
                SQL_BUILDER_CREATE( SelectIbtExcludeParamByBranch )
                SQL_BUILDER_PUSH_BACK( SelectIbtExcludeParamByBranch )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectIbtExcludeParamByBranch )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectIbtExcludeParamByBranch )

        bool SelectIbtExcludeParamByBranch::isExecutable() const
        {
            METHODNAME_DEF( SelectIbtExcludeParamByBranch, isExecutable );
            static const log4cplus::Logger& logger = ibtrelevantcalculator::LoggerPool::getLoggerDomModules();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet(properties::BRANCH_NO.toPropertyString()) ;

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );

            return executable;
        }

        void SelectIbtExcludeParamByBranch::buildSQLString()
        {
            METHODNAME_DEF( SelectIbtExcludeParamByBranch, buildSQLString );

            /////////////////////////////////////////////////////////////////////////////////////////////////
            // const attributes
            /////////////////////////////////////////////////////////////////////////////////////////////////
            static const basar::VarString constSQL(

				"SELECT  "
					"r.contextname AS "         + properties::CONTEXT_NAME.getName()                    + ", "
					"f.pseudolagerort AS "      + properties::PSEUDO_STORAGE_LOCATION.getName()         + ", "
					"p.comparevalue AS "        + properties::COMPARE_VALUE_INT.getName()               + ", "
					"p.comparevaluedecimal AS " + properties::COMPARE_VALUE_DEC.getName()               + ", "
					"p.comparevaluestring AS "  + properties::COMPARE_VALUE_STR.getName()               + ", "
					"p.startvalue AS "          + properties::INTERVAL_START.getName()                  + ", "
					"p.endvalue AS "            + properties::INTERVAL_END.getName()					+             
                " FROM puibtexcluderule r, puibtexcludeparam p, rfiliale f "
                " WHERE p.ruleid = r.ruleid and activationflag = 1 and p.branchno = f.filialnr "
				" and p.branchno = " + properties::BRANCH_NO.toSQLReplacementString() 
                
				);

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( ibtrelevantcalculator::LoggerPool::getLoggerDomModules() );
        }

    } 
} // end namespace accessor

}   // end namespace infrastructure
}   
