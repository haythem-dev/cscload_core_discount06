//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.DKBAZK
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#include "cmndm.h"
#include "dkbazkacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "dkbazkacc_definitions.h"
#include "csc_phabor_table_definitions.h"
#include <loggerpool.h>
#include <iostream>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_dkbazk
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkbazk::ACC_DKBAZK)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::RECORDOFFSET		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKLFDANR		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKANR			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKDX05DATE	);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKIDF			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKIKNR		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKUFIL		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKKUKZ		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKFIL			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKPOSLINES	);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKHART		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKSAPDELNO	);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKLIEFDAT		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKAVAL		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKADDMONTH	);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKAART		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKKART		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKBART		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKTEXT		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKEDILS		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKKZSHA		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazk::KBAZKSTATUS		);
		
	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkbazk::SELECT_DKBAZK_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectDKBAZKByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKBAZKByPattern)

	ACCESS_METHOD( lit::acc_dkbazk::SAVE_DKBAZK )
		SQL_BUILDER_CREATE(UpdateDKBAZK)
		SQL_BUILDER_PUSH_BACK(UpdateDKBAZK)
	
END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKBAZKByPattern)

	bool SelectDKBAZKByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;		
		searchValues.push_back( properties::dkbazk::RECORDOFFSET.getName() );
		
		return arePropertiesSet( searchValues );
	}
		
	void SelectDKBAZKByPattern::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::dkbazk::KBAZK_OFFSET		+ " AS " + properties::dkbazk::RECORDOFFSET.getName() + " "	
				", " + columnnames::dkbazk::KBAZK_LFDANR		+ " AS " + properties::dkbazk::KBAZKLFDANR.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_ANR			+ " AS " + properties::dkbazk::KBAZKANR.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_DX05DATE		+ " AS " + properties::dkbazk::KBAZKDX05DATE.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_IDF			+ " AS " + properties::dkbazk::KBAZKIDF.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_IKNR			+ " AS " + properties::dkbazk::KBAZKIKNR.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_UFIL			+ " AS " + properties::dkbazk::KBAZKUFIL.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_KUKZ			+ " AS " + properties::dkbazk::KBAZKKUKZ.getName() + " "	
				", " + columnnames::dkbazk::KBAZK_FIL			+ " AS " + properties::dkbazk::KBAZKFIL.getName() + " "		
				", " + columnnames::dkbazk::KBAZK_POSLINES		+ " AS " + properties::dkbazk::KBAZKPOSLINES.getName() + " "	
				", " + columnnames::dkbazk::KBAZK_HART			+ " AS " + properties::dkbazk::KBAZKHART.getName() + " "		
				", " + columnnames::dkbazk::KBAZK_SAPDELNO		+ " AS " + properties::dkbazk::KBAZKSAPDELNO.getName() + " "
				", " + columnnames::dkbazk::KBAZK_LIEFDAT		+ " AS " + properties::dkbazk::KBAZKLIEFDAT.getName() + " "		
				", " + columnnames::dkbazk::KBAZK_AVAL			+ " AS " + properties::dkbazk::KBAZKAVAL.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_ADDMONTH		+ " AS " + properties::dkbazk::KBAZKADDMONTH.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_AART			+ " AS " + properties::dkbazk::KBAZKAART.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_KART			+ " AS " + properties::dkbazk::KBAZKKART.getName() + " "		
				", " + columnnames::dkbazk::KBAZK_BART			+ " AS " + properties::dkbazk::KBAZKBART.getName() + " "			
				", " + columnnames::dkbazk::KBAZK_TEXT			+ " AS " + properties::dkbazk::KBAZKTEXT.getName() + " "
				", " + columnnames::dkbazk::KBAZK_KZSHA			+ " AS " + properties::dkbazk::KBAZKKZSHA.getName()		+ " "		
				", " + columnnames::dkbazk::KBAZK_EDILS			+ " AS " + properties::dkbazk::KBAZKEDILS.getName()		+ " "
				", " + columnnames::dkbazk::KBAZK_STATUS		+ " AS " + properties::dkbazk::KBAZKSTATUS.getName()		+ " "
				" FROM " + domMod::TABLE_DKBAZK + " "
				" WHERE NOT " + columnnames::dkbazk::KBAZK_STATUS + " = '" + lit::acc_dkbazk::KBAZK_STATUS_TRANSFERED + "' "
				" AND " + columnnames::dkbazk::KBAZK_SA + " = 1 "
				" ORDER BY " + columnnames::dkbazk::KBAZK_OFFSET + " ASC "
				";"
				);

		resolve(stmt);

		BLOG_TRACE( logger, getSQLString() );

	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdateDKBAZK)

	bool UpdateDKBAZK::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;		

		searchValues.push_back( properties::dkbazk::RECORDOFFSET.getName() );
		searchValues.push_back( properties::dkbazk::KBAZKSTATUS.getName() );
		
		return arePropertiesSet( searchValues );
	}
		
	void UpdateDKBAZK::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::VarString updateStatement( "UPDATE " + domMod::TABLE_DKBAZK + " SET " );			

		static const basar::VarString whereStatement( "WHERE " + columnnames::dkbazk::KBAZK_OFFSET + "=" + properties::dkbazk::RECORDOFFSET.toSQLReplacementString() + " " +
			                                          "AND " + columnnames::dkbazk::KBAZK_SA + "= 1 " );

		basar::VarString variableSetStatement;

		if( arePropertiesSetAndOneMustBeInState( properties::dkbazk::KBAZKSTATUS.toPropertyString(), basar::SS_UPDATE ) )
		{
			variableSetStatement.append( " " + columnnames::dkbazk::KBAZK_STATUS + "='" + properties::dkbazk::KBAZKSTATUS.toSQLReplacementString() + "' " );
		}

		const basar::VarString sqlStatement( updateStatement + " " + variableSetStatement + " " + whereStatement );

		resolve( sqlStatement );
		BLOG_TRACE( logger, getSQLString() );

	}

} // namespace acc_dkbazk

//----------------------------------------------------------------------------
