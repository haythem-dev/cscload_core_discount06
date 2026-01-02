//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.DKOTO
 *  \author		Steffen Heinlein
 *  \date		24.05.2013
 */
//----------------------------------------------------------------------------

#include "dkotoacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "dkotoacc_definitions.h"
#include "csc_corpha_table_definitions.h"
#include "loggerpool.h"
#include <iostream>
#include <libbasardbaspect.h>

//----------------------------------------------------------------------------

namespace acc_dkoto
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkoto::ACC_DKOTO)

	BEGIN_PROPERTY_DESCRIPTION_LIST					

		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::TIME );		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::KSCANR );		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::LFDNR );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::SA );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::DIRECTION );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::STATUS );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::ZEIT );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkoto::BUFFER );			

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkoto::SAVE_DKOTO )
		SQL_BUILDER_CREATE(InsertDKOTO)
		SQL_BUILDER_PUSH_BACK(InsertDKOTO)	

	ACCESS_METHOD( lit::acc_dkoto::SAVE_DKOTO_STATUS )
		SQL_BUILDER_CREATE(UpdateDKOTO)
		SQL_BUILDER_PUSH_BACK(UpdateDKOTO)	

	ACCESS_METHOD( lit::acc_dkoto::SELECT_DKOTO_BY_PATTERN )	
		SQL_BUILDER_CREATE(SelectDKOTOByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKOTOByPattern)				

	ACCESS_METHOD( lit::acc_dkoto::SELECT_DKOTO_COUNT_BY_PATTERN )	
		SQL_BUILDER_CREATE(SelectDKOTOCountByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKOTOCountByPattern)				

END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKOTOByPattern)

	bool SelectDKOTOByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;				
		searchValues.push_back( properties::dkoto::KSCANR.getName() );
		searchValues.push_back( properties::dkoto::DIRECTION.getName() );		
		searchValues.push_back( properties::dkoto::STATUS.getName() );		
		
		return arePropertiesSet( searchValues );		
	}
		
	void SelectDKOTOByPattern::buildSQLString()
	{			
		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::dkoto::OTO_TIME 		+ " AS " + properties::dkoto::TIME.getName() + " "
				", " + columnnames::dkoto::OTO_KSCANR 		+ " AS " + properties::dkoto::KSCANR.getName() + " "
				", " + columnnames::dkoto::OTO_LFDNR 		+ " AS " + properties::dkoto::LFDNR.getName() + " "
				", " + columnnames::dkoto::OTO_SA 			+ " AS " + properties::dkoto::SA.getName() + " "
				", " + columnnames::dkoto::OTO_DIRECTION	+ " AS " + properties::dkoto::DIRECTION.getName() + " "
				", " + columnnames::dkoto::OTO_STATUS 		+ " AS " + properties::dkoto::STATUS.getName() + " "
				", " + columnnames::dkoto::OTO_ZEIT 		+ " AS " + properties::dkoto::ZEIT.getName() + " " 
				", " + columnnames::dkoto::OTO_BUFFER 		+ " AS " + properties::dkoto::BUFFER.getName() + " " 				
				" FROM " 	+ domMod::TABLE_DKOTO2 + " "
				" WHERE " 	+ columnnames::dkoto::OTO_KSCANR	+ " = " + properties::dkoto::KSCANR.toSQLReplacementString() + " "
				" AND " 	+ columnnames::dkoto::OTO_DIRECTION + " = '" + properties::dkoto::DIRECTION.toSQLReplacementString() + "' " 
				" AND "     + columnnames::dkoto::OTO_STATUS    + " = '" + properties::dkoto::STATUS.toSQLReplacementString() + "' "
				" ;"				
			);		

		resolve(stmt);			
	}
//----------------------------------------------------------------------------

BUILDER_DEFINITION(SelectDKOTOCountByPattern)

	bool SelectDKOTOCountByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;				
		searchValues.push_back( properties::dkoto::TIME.getName() );
		searchValues.push_back( properties::dkoto::KSCANR.getName() );
		searchValues.push_back( properties::dkoto::DIRECTION.getName() );		
		
		return arePropertiesSet( searchValues );		
	}
		
	void SelectDKOTOCountByPattern::buildSQLString()
	{			
		static const basar::I18nString	stmt(
			"SELECT COUNT(*) "
				"FROM "		+ domMod::TABLE_DKOTO + " "
				"WHERE " 	+ columnnames::dkoto::OTO_TIME		+ " = " + properties::dkoto::TIME.toSQLReplacementString() + " "
				"AND "		+ columnnames::dkoto::OTO_KSCANR	+ " = " + properties::dkoto::KSCANR.toSQLReplacementString() + " "
				"AND "		+ columnnames::dkoto::OTO_DIRECTION + " = '" + properties::dkoto::DIRECTION.toSQLReplacementString() + "' " 
			);		

		resolve(stmt);			
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(InsertDKOTO)

    bool InsertDKOTO::isExecutable() const
    {
		using namespace properties::dkoto;

		static const basar::VarString properties(	TIME.toPropertyString() +
													KSCANR.toPropertyString() +
													LFDNR.toPropertyString() +
													SA.toPropertyString() + 
													DIRECTION.toPropertyString() );

		const bool executable = arePropertiesSetAndAllInState( properties, basar::SS_INSERT ); 

		return executable;
    }

	void InsertDKOTO::buildSQLString()
	{
        static const basar::VarString constAttributes(	columnnames::dkoto::OTO_TIME + "," +
														columnnames::dkoto::OTO_KSCANR + "," +
														columnnames::dkoto::OTO_LFDNR + "," +
														columnnames::dkoto::OTO_SA + "," +
														columnnames::dkoto::OTO_DIRECTION + "," +
														columnnames::dkoto::OTO_TIME2);

        static const basar::VarString constValues(	properties::dkoto::TIME.toSQLReplacementString() + "," + 
													properties::dkoto::KSCANR.toSQLReplacementString() + "," + 
													properties::dkoto::LFDNR.toSQLReplacementString() + "," + 
													"'" + properties::dkoto::SA.toSQLReplacementString() + "'," + 
													"'" + properties::dkoto::DIRECTION.toSQLReplacementString() + "'," +
													properties::dkoto::TIME.toSQLReplacementString()); 

		basar::VarString variableAttributes; 
		basar::VarString variableValues;

		if( isContainedAndSet( properties::dkoto::STATUS.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkoto::OTO_STATUS );
			variableValues.append( ",'" + properties::dkoto::STATUS.toSQLReplacementString() + "'" );
		}

		if (isContainedAndSet( properties::dkoto::ZEIT.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkoto::OTO_ZEIT );
			variableValues.append( "," + properties::dkoto::ZEIT.toSQLReplacementString() );
		}
		
		if( isContainedAndSet( properties::dkoto::BUFFER.getName() ) )
		{
			variableAttributes.append( "," + columnnames::dkoto::OTO_BUFFER );
			variableValues.append( ",'" + properties::dkoto::BUFFER.toSQLReplacementString() + "'" );
		}		

		const basar::VarString sqlStatement( "INSERT INTO " + domMod::TABLE_DKOTO + " (" + constAttributes + variableAttributes + 
												") VALUES (" + constValues + variableValues + ");" );

		resolve( sqlStatement );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdateDKOTO)

    bool UpdateDKOTO::isExecutable() const
    {
		using namespace properties::dkoto;
		
		static const basar::VarString properties(	TIME.toPropertyString() +
													KSCANR.toPropertyString() );

		const bool executable = arePropertiesSet( properties ); 		

		return executable;
    }

	void UpdateDKOTO::buildSQLString()
	{
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;				

		static const basar::I18nString	stmt(
			"UPDATE " + domMod::TABLE_DKOTO + " "
			" SET " + columnnames::dkoto::OTO_STATUS + " = " + "'" + domMod::STATUS_TRANSFER_COMPLETED + "' "
			" WHERE " + columnnames::dkoto::OTO_TIME + " = " + properties::dkoto::TIME.toSQLReplacementString() + " "
			" AND " + columnnames::dkoto::OTO_KSCANR + " = " + properties::dkoto::KSCANR.toSQLReplacementString() + " "
			" ;"			
			);
			
		resolve(stmt);			

		BLOG_TRACE( logger, getSQLString() );	
	}



} // namespace acc_dkoto
