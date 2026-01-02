//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.DKOTE
 *  \author		Steffen Heinlein
 *  \date		24.05.2013
 */
//----------------------------------------------------------------------------

#include "dkoteacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "dkoteacc_definitions.h"
#include "csc_corpha_table_definitions.h"
#include "loggerpool.h"
#include <iostream>
#include <libbasardbaspect.h>
//----------------------------------------------------------------------------

namespace acc_dkote
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkote::ACC_DKOTE)

	BEGIN_PROPERTY_DESCRIPTION_LIST					

		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::TIME );		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::KSCANR );		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::LFDNR );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::SA );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::DIRECTION );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::STATUS );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::ZEIT );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkote::BUFFER );			

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkote::SAVE_DKOTE )
		SQL_BUILDER_CREATE(InsertDKOTE)
		SQL_BUILDER_PUSH_BACK(InsertDKOTE)	

	ACCESS_METHOD( lit::acc_dkote::SAVE_DKOTE_STATUS )
		SQL_BUILDER_CREATE(UpdateDKOTE)
		SQL_BUILDER_PUSH_BACK(UpdateDKOTE)	

	ACCESS_METHOD( lit::acc_dkote::SELECT_DKOTE_BY_PATTERN )	
		SQL_BUILDER_CREATE(SelectDKOTEByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKOTEByPattern)				

	ACCESS_METHOD( lit::acc_dkote::SELECT_DKOTE_COUNT_BY_PATTERN )	
		SQL_BUILDER_CREATE(SelectDKOTECountByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKOTECountByPattern)				

END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKOTEByPattern)

	bool SelectDKOTEByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;				
		searchValues.push_back( properties::dkote::KSCANR.getName() );
		searchValues.push_back( properties::dkote::DIRECTION.getName() );		
		searchValues.push_back( properties::dkote::STATUS.getName() );				

		return arePropertiesSet( searchValues );		
	}
		
	void SelectDKOTEByPattern::buildSQLString()
	{
		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::dkote::OTE_TIME 		+ " AS " + properties::dkote::TIME.getName() + " "
				", " + columnnames::dkote::OTE_KSCANR 		+ " AS " + properties::dkote::KSCANR.getName() + " "
				", " + columnnames::dkote::OTE_LFDNR 		+ " AS " + properties::dkote::LFDNR.getName() + " "
				", " + columnnames::dkote::OTE_SA 			+ " AS " + properties::dkote::SA.getName() + " "
				", " + columnnames::dkote::OTE_DIRECTION	+ " AS " + properties::dkote::DIRECTION.getName() + " "
				", " + columnnames::dkote::OTE_STATUS 		+ " AS " + properties::dkote::STATUS.getName() + " "
				", " + columnnames::dkote::OTE_ZEIT 		+ " AS " + properties::dkote::ZEIT.getName() + " " 
				", " + columnnames::dkote::OTE_BUFFER 		+ " AS " + properties::dkote::BUFFER.getName() + " " 				
				" FROM " 	+ domMod::TABLE_DKOTE2 + " "
				" WHERE " 	+ columnnames::dkote::OTE_KSCANR	+ " = " + properties::dkote::KSCANR.toSQLReplacementString() + " "
				" AND " 	+ columnnames::dkote::OTE_DIRECTION + " = '" + properties::dkote::DIRECTION.toSQLReplacementString() + "' " 
				" AND "     + columnnames::dkote::OTE_STATUS    + " = '" + properties::dkote::STATUS.toSQLReplacementString() + "' "
				" ;"				
			);		

		resolve(stmt);			
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKOTECountByPattern)

	bool SelectDKOTECountByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;				
		searchValues.push_back( properties::dkote::TIME.getName() );
		searchValues.push_back( properties::dkote::KSCANR.getName() );
		searchValues.push_back( properties::dkote::DIRECTION.getName() );		
		
		return arePropertiesSet( searchValues );		
	}
		
	void SelectDKOTECountByPattern::buildSQLString()
	{			
		static const basar::I18nString	stmt(
			"SELECT COUNT(*) "
				"FROM " 	+ domMod::TABLE_DKOTE + " "
				"WHERE " 	+ columnnames::dkote::OTE_TIME		+ " = "  + properties::dkote::TIME.toSQLReplacementString() + " "
				"AND "		+ columnnames::dkote::OTE_KSCANR	+ " = "  + properties::dkote::KSCANR.toSQLReplacementString() + " "
				"AND "		+ columnnames::dkote::OTE_DIRECTION + " = '" + properties::dkote::DIRECTION.toSQLReplacementString() + "' " 
			);		

		resolve(stmt);			
	}

//----------------------------------------------------------------------------

BUILDER_DEFINITION(InsertDKOTE)

    bool InsertDKOTE::isExecutable() const
    {
		using namespace properties::dkote;

		static const basar::VarString properties(	TIME.toPropertyString() +
													KSCANR.toPropertyString() +
													LFDNR.toPropertyString() +
													SA.toPropertyString() + 
													DIRECTION.toPropertyString() );

		const bool executable = arePropertiesSetAndAllInState( properties, basar::SS_INSERT ); 

		return executable;
    }

	void InsertDKOTE::buildSQLString()
	{
        static const basar::VarString constAttributes(  columnnames::dkote::OTE_TIME		+ "," +
														columnnames::dkote::OTE_KSCANR		+ "," +
														columnnames::dkote::OTE_LFDNR		+ "," +
														columnnames::dkote::OTE_SA			+ "," +
														columnnames::dkote::OTE_DIRECTION	+ "," +
														columnnames::dkote::OTE_TIME2 );

        static const basar::VarString constValues(  properties::dkote::TIME.toSQLReplacementString() + "," + 
													properties::dkote::KSCANR.toSQLReplacementString() + "," + 
													properties::dkote::LFDNR.toSQLReplacementString() + "," + 
													"'" + properties::dkote::SA.toSQLReplacementString() + "'," + 
                                                    "'" + properties::dkote::DIRECTION.toSQLReplacementString() + "'," +
													properties::dkote::TIME.toSQLReplacementString() );

		basar::VarString variableAttributes; 
		basar::VarString variableValues;

		if( isContainedAndSet( properties::dkote::STATUS.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkote::OTE_STATUS );
			variableValues.append( ",'" + properties::dkote::STATUS.toSQLReplacementString() + "'" );
		}

		if (isContainedAndSet( properties::dkote::ZEIT.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkote::OTE_ZEIT );
			variableValues.append( "," + properties::dkote::ZEIT.toSQLReplacementString() );
		}
		
		if( isContainedAndSet( properties::dkote::BUFFER.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkote::OTE_BUFFER );
			variableValues.append( ",'" + properties::dkote::BUFFER.toSQLReplacementString() + "'" );
		}		

		const basar::VarString sqlStatement( "INSERT INTO " + domMod::TABLE_DKOTE + " (" + constAttributes + variableAttributes + 
												") VALUES (" + constValues + variableValues + ");" );

		resolve( sqlStatement );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdateDKOTE)

    bool UpdateDKOTE::isExecutable() const
    {
		using namespace properties::dkote;
		
		static const basar::VarString properties(	TIME.toPropertyString() +
													KSCANR.toPropertyString() );		

		const bool executable = arePropertiesSet( properties ); 		

		return executable;
    }

	void UpdateDKOTE::buildSQLString()
	{
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;				

		static const basar::I18nString	stmt(
			"UPDATE " + domMod::TABLE_DKOTE + " "
			" SET " + columnnames::dkote::OTE_STATUS + " = " + "'" + domMod::STATUS_TRANSFER_COMPLETED + "' "
			" WHERE " + columnnames::dkote::OTE_TIME + " = " + properties::dkote::TIME.toSQLReplacementString() + " "
			" AND " + columnnames::dkote::OTE_KSCANR + " = " + properties::dkote::KSCANR.toSQLReplacementString() + " "
			" ;"			
			);
			
		resolve(stmt);			

		BLOG_TRACE( logger, getSQLString() );	
	}


} // namespace acc_dkote
