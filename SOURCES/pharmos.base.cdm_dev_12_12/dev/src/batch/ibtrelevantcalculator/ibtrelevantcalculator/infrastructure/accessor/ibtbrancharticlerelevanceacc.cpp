//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/ibtbrancharticlerelevanceacc.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/ibtbrancharticlerelevanceacc_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
    namespace ibtbrancharticlerelevanceparam
    {

    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( accessor::ibtbrancharticlerelevanceparam::lit::IBT_BRANCH_ARTICLE_RELEVANCE_PARAM_ACC )

            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::FIXREGIONALASSIGNMENTFLAG	)

            END_PROPERTY_DESCRIPTION_LIST

                ACCESS_METHOD( accessor::ibtbrancharticlerelevanceparam::lit::SELECT_IBT_BRANCH_ARTICLE_RELEVANCE_PARAM );
                SQL_BUILDER_CREATE( SelectIbtBranchArticleRelevanceParam )
                SQL_BUILDER_PUSH_BACK( SelectIbtBranchArticleRelevanceParam )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectIbtBranchArticleRelevanceParam )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectIbtBranchArticleRelevanceParam )

        bool SelectIbtBranchArticleRelevanceParam::isExecutable() const
        {
            METHODNAME_DEF( SelectIbtBranchArticleRelevanceParam, isExecutable );
            static const log4cplus::Logger& logger = ibtrelevantcalculator::LoggerPool::getLoggerDomModules();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet(properties::BRANCH_NO.toPropertyString()) ;

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );

            return executable;
        }

        void SelectIbtBranchArticleRelevanceParam::buildSQLString()
        {
            METHODNAME_DEF( SelectIbtBranchArticleRelevanceParam, buildSQLString );

            /////////////////////////////////////////////////////////////////////////////////////////////////
            // const attributes
            /////////////////////////////////////////////////////////////////////////////////////////////////
            static const basar::VarString constSQL(

				"SELECT "
				"considerfixregionalassignmentflag AS "         + properties::FIXREGIONALASSIGNMENTFLAG.getName()   +
				" FROM puibtbrancharticlerelevanceparam "
				" WHERE branchno = " + properties::BRANCH_NO.toSQLReplacementString() 
				);

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( ibtrelevantcalculator::LoggerPool::getLoggerDomModules() );
        }

    } 
} // end namespace accessor

}   // end namespace infrastructure
}   
