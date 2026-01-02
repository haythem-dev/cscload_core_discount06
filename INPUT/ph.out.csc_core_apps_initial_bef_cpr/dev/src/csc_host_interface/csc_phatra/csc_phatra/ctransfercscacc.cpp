//----------------------------------------------------------------------------
/*! \file		ctransfercscacc.cpp
 *  \brief		string builder definition for ZPD table ctransfercsc
 *  \author		Frank Naumann
 *  \date		23.01.2015
 */
//----------------------------------------------------------------------------

#include "ctransfercscacc.h"
#include "ctransfercsc_definitions.h"
#include "property_definitions.h"
#include "csc_phatra_table_definitions.h"
#include <loggerpool.h>


//----------------------------------------------------------------------------

namespace acc_ctransfercsc { 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_ctransfercsc::ACC_CTRANSFERCSC)

	BEGIN_PROPERTY_DESCRIPTION_LIST
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::TRANSFERID);
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::ENTRYDATETIME);
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::ARTICLENO);
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::FIELDNAME);
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::FIELDVALUE);
		PROPERTY_DESCRIPTION_LIST_ADD(properties::ctransfercsc::PROCESSEDFLAG);
	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_ctransfercsc::SELECT_CTRANSFERCSC_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectChangeRecords)
		SQL_BUILDER_PUSH_BACK(SelectChangeRecords)
	
	ACCESS_METHOD( lit::acc_ctransfercsc::SAVE_CTRANSFERCSC )
		SQL_BUILDER_CREATE(UpdateChangeRecord)
		SQL_BUILDER_PUSH_BACK(UpdateChangeRecord)

END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectChangeRecords)

	bool SelectChangeRecords::isExecutable() const
	{   				
		return true;
	}
		
	void SelectChangeRecords::buildSQLString()
	{			
		static const basar::I18nString	stmt(
			"SELECT "
				"transferid AS " 		+ properties::ctransfercsc::TRANSFERID.getName() + ", "
				"entrydatetime AS " 	+ properties::ctransfercsc::ENTRYDATETIME.getName() + ", "
				"articleno AS " 		+ properties::ctransfercsc::ARTICLENO.getName() + ", "
				"fieldname AS " 		+ properties::ctransfercsc::FIELDNAME.getName() + ", "
				"fieldvalue AS " 		+ properties::ctransfercsc::FIELDVALUE.getName() + ", "
				"processedflag AS " 	+ properties::ctransfercsc::PROCESSEDFLAG.getName() + " "

			"FROM " 					+ properties::ctransfercsc::ZDPDATABASE.toSQLReplacementString() + "@"
										+ properties::ctransfercsc::ZDPHOST.toSQLReplacementString() + ":"
										+ domMod::TABLE_CTRANSFERCSC + " "
			"WHERE processedflag=0 "
				"AND transferid NOT IN (SELECT vseoffset FROM pharmostransactions WHERE branchno=0 AND origin=1) "
				"AND entrydatetime >= ('" + properties::ctransfercsc::ENTRYDATETIME.toSQLReplacementString() + "')::DATETIME YEAR TO FRACTION(3) "
			"ORDER BY transferid ASC"
			);

		resolve(stmt);

		BLOG_TRACE( libcsc_utils::LoggerPool::LoggerCSC, getSQLString() );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdateChangeRecord)

	bool UpdateChangeRecord::isExecutable() const
	{   				
		return true;
	}
		
	void UpdateChangeRecord::buildSQLString()
	{			
		static const basar::I18nString	stmt(
			"UPDATE " + domMod::TABLE_CTRANSFERCSC + " "
			"SET processedflag=1 "
			"WHERE transferid=" + properties::ctransfercsc::TRANSFERID.toSQLReplacementString()
			);

		resolve(stmt);

		BLOG_TRACE( libcsc_utils::LoggerPool::LoggerCSC, getSQLString() );
	}

} // namespace acc_ctransfercsc

//----------------------------------------------------------------------------
