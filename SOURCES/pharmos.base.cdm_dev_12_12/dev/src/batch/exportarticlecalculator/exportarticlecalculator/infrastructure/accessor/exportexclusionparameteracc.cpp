//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/exportexclusionparameteracc.h"
#include "loggerpool/exportarticlecalculator_loggerpool.h"
#include "domainmodule/exportarticlecalculator_property_definitions.h"
#include "infrastructure/accessor/exportexclusionparameteracc_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
namespace infrastructure
{
namespace accessor
{
    namespace exportexclusionparameter
    {

    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( accessor::exportexclusionparameter::lit::EXPORT_EXCLUSION_CRITERIA_ACC )

            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PSEUDO_STORAGE_LOCATION  )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_START        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPARE_END        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::ACTIVATION_FLAG        )
				PROPERTY_DESCRIPTION_LIST_ADD( properties::RULE_ID           )
			END_PROPERTY_DESCRIPTION_LIST

                ACCESS_METHOD( accessor::exportexclusionparameter::lit::SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY );
                SQL_BUILDER_CREATE( SelectExportExclusionParamByCountry )
                SQL_BUILDER_PUSH_BACK( SelectExportExclusionParamByCountry )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectExportExclusionParamByCountry )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectExportExclusionParamByCountry )

        bool SelectExportExclusionParamByCountry::isExecutable() const
        {
            METHODNAME_DEF( SelectExportExclusionParamByCountry, isExecutable );
            static const log4cplus::Logger& logger = exportarticlecalculator::LoggerPool::getLoggerDomModules();
            BLOG_TRACE_METHOD( logger, fun );

			const bool executable = arePropertiesSet(	properties::COUNTRY_CODE.toPropertyString() + 
														properties::BRANCH_NO.toPropertyString()) ;

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );

            return executable;
        }

        void SelectExportExclusionParamByCountry::buildSQLString()
        {
            METHODNAME_DEF( SelectExportExclusionParamByCountry, buildSQLString );

            /////////////////////////////////////////////////////////////////////////////////////////////////
            // const attributes
            /////////////////////////////////////////////////////////////////////////////////////////////////
            static const basar::VarString constSQL(

				"SELECT  "
					"f.pseudolagerort AS "      + properties::PSEUDO_STORAGE_LOCATION.getName()     + ", "
					"p.comparestartvalue AS "   + properties::COMPARE_START.getName()               + ", "
					"p.compareendvalue AS "		+ properties::COMPARE_END.getName()					+ ", "
					"p.ruleid AS "				+ properties::RULE_ID.getName()						+ ", "
					"p.activationflag AS "      + properties::ACTIVATION_FLAG.getName()  +             
                " FROM cexportexclusionparam p, rfiliale f "
                " WHERE p.country_ifacode = '"	+ properties::COUNTRY_CODE.toSQLReplacementString() + "' "
				" and f.filialnr = "			+ properties::BRANCH_NO.toSQLReplacementString() 
                );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( exportarticlecalculator::LoggerPool::getLoggerDomModules() );
        }

    } 
} // end namespace accessor

}   // end namespace infrastructure
}   
