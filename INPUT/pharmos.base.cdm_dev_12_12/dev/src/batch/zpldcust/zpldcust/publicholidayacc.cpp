//----------------------------------------------------------------------------
/*! \file   publicholidayacc.cpp
 *  \brief  string builder definitions for publicholiday
 *  \author Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#include "commonheader.h"
#include "publicholidayacc.h"
#include "generalbranchparameterdm_definitions.h"
#include "loggerpool.h"

//----------------------------------------------------------------------------

namespace acc_publicholiday {

//----------------------------------------------------------------------------

BUILDER_DEFINITION(SelectAllPublicHolidaysByBranchno)

ENSURE_PROPERTIES_ARE_SET(SelectAllPublicHolidaysByBranchno, 
  lit::pdm_generalbranchparameter::BRANCHNO.toPropertyString()
  )
  
void SelectAllPublicHolidaysByBranchno::buildSQLString()
{
  I18nString sqlStatement;

  sqlStatement.append("SELECT ");
  sqlStatement.append("filialnr AS " + lit::pdm_generalbranchparameter::BRANCHNO.getName() + ", " );
  sqlStatement.append("modus AS " + lit::pdm_generalbranchparameter::MODE.getName() + ", " );
  sqlStatement.append("tag AS " + lit::pdm_generalbranchparameter::DAY.getName() + ", " );
  sqlStatement.append("von_jahr AS " + lit::pdm_generalbranchparameter::YEAR_FROM.getName() + ", " );
  sqlStatement.append("bis_jahr AS " + lit::pdm_generalbranchparameter::YEAR_TO.getName() + ", " );
  sqlStatement.append("tagname AS " + lit::pdm_generalbranchparameter::DAY_DESCRIPTION.getName() + ", " );
  sqlStatement.append("anteil AS " + lit::pdm_generalbranchparameter::PROPORTION.getName() + ", " );
  sqlStatement.append("prognosenja AS " + lit::pdm_generalbranchparameter::PREDICTION_START_FLAG.getName() + ", " );
  sqlStatement.append("bestvorja AS " + lit::pdm_generalbranchparameter::PROPOSAL_START_FLAG.getName() + " " );
  sqlStatement.append("FROM feiertag " );
  sqlStatement.append("WHERE filialnr = " + lit::pdm_generalbranchparameter::BRANCHNO.toSQLReplacementString() + " ");
  sqlStatement.append("ORDER BY modus, tag");
  resolve(sqlStatement);

  BLOG_TRACE(zpldcust::LoggerPool::zpldcust, getSQLString());
}

//---------------------------------------------------------------------------

BEGIN_ACCESSOR_DEFINITION("AccDefinitionPublicHoliday")

  BEGIN_PROPERTY_DESCRIPTION_LIST
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::BRANCHNO);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::MODE);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::DAY);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::YEAR_FROM);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::YEAR_TO);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::DAY_DESCRIPTION);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::PROPORTION);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::PREDICTION_START_FLAG);
    PROPERTY_DESCRIPTION_LIST_ADD(lit::pdm_generalbranchparameter::PROPOSAL_START_FLAG);
  END_PROPERTY_DESCRIPTION_LIST

  ACCESS_METHOD("amSelectAllPublicHolidaysByBranchno")
    SQL_BUILDER_CREATE(SelectAllPublicHolidaysByBranchno)
    SQL_BUILDER_PUSH_BACK(SelectAllPublicHolidaysByBranchno)	

END_ACCESSOR_DEFINITION
				
//----------------------------------------------------------------------------

} // namespace acc_publicholiday 

//----------------------------------------------------------------------------
