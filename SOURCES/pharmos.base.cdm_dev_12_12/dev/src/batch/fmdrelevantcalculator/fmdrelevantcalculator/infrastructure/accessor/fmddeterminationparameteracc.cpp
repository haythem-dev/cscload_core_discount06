//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/fmddeterminationparameteracc.h"
#include "loggerpool/fmdrelevantcalculator_loggerpool.h"
#include "domainmodule/fmdrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/fmddeterminationparameteracc_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
    namespace fmddeterminationparameter
    {

    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( accessor::fmddeterminationparameter::lit::FMD_DETERMINATION_CRITERIA_ACC )

            BEGIN_PROPERTY_DESCRIPTION_LIST
				PROPERTY_DESCRIPTION_LIST_ADD( properties::RULE_ID         )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SEQUENCE_NO     )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_START   )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_END     )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::ACTIVATION_FLAG )		
			END_PROPERTY_DESCRIPTION_LIST

                ACCESS_METHOD( accessor::fmddeterminationparameter::lit::SELECT_FMD_DETERMINATION_PARAM );
                SQL_BUILDER_CREATE( SelectFmdDeterminationParam )
                SQL_BUILDER_PUSH_BACK( SelectFmdDeterminationParam )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectFmdDeterminationParam )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectFmdDeterminationParam )

        bool SelectFmdDeterminationParam::isExecutable() const
        {
			return true;
        }

        void SelectFmdDeterminationParam::buildSQLString()
        {
            METHODNAME_DEF( SelectFmdDeterminationParam, buildSQLString );

            /////////////////////////////////////////////////////////////////////////////////////////////////
            // const attributes
            /////////////////////////////////////////////////////////////////////////////////////////////////
            static const basar::VarString constSQL(

				"SELECT  "
					"p.ruleid AS "				+ properties::RULE_ID.getName()			 + ", "
					"p.sequenceno AS "          + properties::SEQUENCE_NO.getName()		 + ", "
					"p.comparestartvalue AS "   + properties::COMPARE_START.getName()    + ", "
					"p.compareendvalue AS "		+ properties::COMPARE_END.getName()		 + ", "
					"p.activationflag AS "      + properties::ACTIVATION_FLAG.getName()  +             
                " FROM cfmddeterminationparam p " +
				" ORDER BY p.RULEID " 
                );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( fmdrelevantcalculator::LoggerPool::getLoggerDomModules() );
        }

    } 
} // end namespace accessor

}   // end namespace infrastructure
}   
