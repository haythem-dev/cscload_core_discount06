//----------------------------------------------------------------------------
/*! \file	  dkkulacc.cpp
 *  \brief  string builder definition for VSAM.DKKUL
 *  \author	Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#include "commonheader.h"
#include "dkkulacc.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//----------------------------------------------------------------------------

namespace acc_dkkul {

//---------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKKULByPattern)

ENSURE_PROPERTIES_ARE_SET(SelectDKKULByPattern,
  lit::zpldcust::KUL_FIL1.toPropertyString()
  )
	
void SelectDKKULByPattern::buildSQLString()
{
  VarString sql;
  sql = "SELECT "
    "KUL_FIL1 AS "   + lit::zpldcust::KUL_FIL1.getName()   + ", "
    "KUL_IDF AS "    + lit::zpldcust::KUL_IDF.getName()    + ", "
    "KUL_FIL2 AS "   + lit::zpldcust::KUL_FIL2.getName()   + ", "
    "KUL_KUBZ AS "   + lit::zpldcust::KUL_KUBZ.getName()   + ", "
    "KUL_FIL3 AS "   + lit::zpldcust::KUL_FIL3.getName()   + ", "
    "KUL_NAM1 AS "   + lit::zpldcust::KUL_NAM1.getName()   + ", "
    "KUL_ORT AS "    + lit::zpldcust::KUL_ORT.getName()    + ", "
    "KUL_PLZ AS "    + lit::zpldcust::KUL_PLZ.getName()    + ", "
    "KUL_AEDAT AS "  + lit::zpldcust::KUL_AEDAT.getName()  + ", "
    "KUL_KUSEIT AS " + lit::zpldcust::KUL_KUSEIT.getName() + ", "
    "KUL_VFIL AS "   + lit::zpldcust::KUL_VFIL.getName()   + ", "
    "KUL_GRP AS "    + lit::zpldcust::KUL_GRP.getName()    + " "

    "FROM VSAM.DKKUL "
    "WHERE KUL_FIL1=" + lit::zpldcust::KUL_FIL1.toSQLReplacementString();

  if (isContainedAndSet(lit::zpldcust::KUL_AEDAT))
  {
    sql += " AND (KUL_AEDAT>=" + lit::zpldcust::KUL_AEDAT.toSQLReplacementString() + " AND KUL_AEDAT<600000";
    sql += " OR KUL_KUSEIT>=" + lit::zpldcust::KUL_AEDAT.toSQLReplacementString() + " AND KUL_KUSEIT<600000)";
  }

  if (isContainedAndSet(lit::zpldcust::KUL_GRP_SEARCH))
  {
    sql += " AND KUL_GRP IN (" + lit::zpldcust::KUL_GRP_SEARCH.toSQLReplacementString() + ")";
  }
  resolve(sql);
  BLOG_TRACE(zpldcust::LoggerPool::zpldcust, getSQLString());
}

//---------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION("AccDefinitionDKKUL")

  BEGIN_PROPERTY_DESCRIPTION_LIST
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_FIL1)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_IDF)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_FIL2)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_KUBZ)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_FIL3)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_NAM1)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_ORT)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_PLZ)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_AEDAT)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_KUSEIT)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_GRP)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_GRP_SEARCH)
	PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::KUL_VFIL)
  END_PROPERTY_DESCRIPTION_LIST

  ACCESS_METHOD("amSelectDKKULByPattern")
    SQL_BUILDER_CREATE(SelectDKKULByPattern)
    SQL_BUILDER_PUSH_BACK(SelectDKKULByPattern)

END_ACCESSOR_DEFINITION
				
//----------------------------------------------------------------------------

} // namespace acc_dkkul

//----------------------------------------------------------------------------
