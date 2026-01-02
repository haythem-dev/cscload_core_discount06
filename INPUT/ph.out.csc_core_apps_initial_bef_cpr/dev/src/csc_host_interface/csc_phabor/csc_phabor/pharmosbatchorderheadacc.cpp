//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.PharmosBatchOrderHead
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#include "cmndm.h"
#include "pharmosbatchorderheadacc.h"
#include "property_definitions.h"
#include "batchorderdm_definitions.h"
#include "columnname_definitions.h"
#include "pharmosbatchorderheadacc_definitions.h"
#include "csc_phabor_table_definitions.h"
#include "log_macros.h"
#include <loggerpool.h>
#include <iostream>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_pharmosbatchorderhead
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_pharmosbatchorderhead::ACC_PHARMOSBATCHORDERHEAD)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::BRANCHNO					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::CREATIONDATETIME			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::VSEOFFSET					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::PROCESSINGSTATUS			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::TRANSFERREDTIMESTAMP		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::POSITIONCOUNT				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::TRANSFERORDERNO			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::BATCHORDERNO				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::ORDERTYPE					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::PICKINGTYPE				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::BOOKINGTYPE				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::CUSTOMERNO				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::INTERNALCUSTOMERNO		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::INFOTEXT					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::ORIGINTYPE				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::ORIGINBRANCHNO			);	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::CUSTOMERFLAG				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::VALUEDATE					);	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::VALDATADDMONTH			);	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::DELIVERYDATE				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::SAPDELIVERYNOTE			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::PARENTCOMPANYFLAG 		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderhead::CSCORDERNO				);

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_pharmosbatchorderhead::SELECT_PHARMOSBATCHORDERHEAD_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectPharmosBatchOrderHeadByPattern)
		SQL_BUILDER_PUSH_BACK(SelectPharmosBatchOrderHeadByPattern)

	ACCESS_METHOD( lit::acc_pharmosbatchorderhead::SELECT_LAST_KEY )
		SQL_BUILDER_CREATE(SelectLastKey)
		SQL_BUILDER_PUSH_BACK(SelectLastKey)

	ACCESS_METHOD( lit::acc_pharmosbatchorderhead::SAVE_PHARMOSBATCHORDERHEAD )
		SQL_BUILDER_CREATE(InsertPharmosBatchOrderHead)
		SQL_BUILDER_PUSH_BACK(InsertPharmosBatchOrderHead)
		SQL_BUILDER_CREATE(UpdatePharmosBatchOrderHead)
		SQL_BUILDER_PUSH_BACK(UpdatePharmosBatchOrderHead)
	
END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectPharmosBatchOrderHeadByPattern)

	bool SelectPharmosBatchOrderHeadByPattern::isExecutable() const
	{   						
		basar::cmnutil::ParameterList searchValues;		
		searchValues.push_back( properties::pharmosbatchorderhead::VSEOFFSET.getName() );
		searchValues.push_back( properties::pharmosbatchorderhead::BRANCHNO.getName() );
		searchValues.push_back( properties::pharmosbatchorderhead::PROCESSINGSTATUS.getName() );
		
		return arePropertiesSet( searchValues );
	}
		
	void SelectPharmosBatchOrderHeadByPattern::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::pharmosbatchorderhead::BRANCHNO					+ " AS " + properties::pharmosbatchorderhead::BRANCHNO.getName() + " "	
				", " + columnnames::pharmosbatchorderhead::CREATIONDATETIME			+ " AS " + properties::pharmosbatchorderhead::CREATIONDATETIME.getName() + " "			
				", " + columnnames::pharmosbatchorderhead::VSEOFFSET				+ " AS " + properties::pharmosbatchorderhead::VSEOFFSET.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS			+ " AS " + properties::pharmosbatchorderhead::PROCESSINGSTATUS.getName() + " "			
				", " + columnnames::pharmosbatchorderhead::PROCESSEDTIMESTAMP		+ " AS " + properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP.getName() + " "		
				", " + columnnames::pharmosbatchorderhead::TRANSFERREDTIMESTAMP		+ " AS " + properties::pharmosbatchorderhead::TRANSFERREDTIMESTAMP.getName() + " "		
				", " + columnnames::pharmosbatchorderhead::POSITIONCOUNT			+ " AS " + properties::pharmosbatchorderhead::POSITIONCOUNT.getName() + " "			
				", " + columnnames::pharmosbatchorderhead::TRANSFERORDERNO			+ " AS " + properties::pharmosbatchorderhead::TRANSFERORDERNO.getName() + " "			
				", " + columnnames::pharmosbatchorderhead::BATCHORDERNO				+ " AS " + properties::pharmosbatchorderhead::BATCHORDERNO.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::ORDERTYPE				+ " AS " + properties::pharmosbatchorderhead::ORDERTYPE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::PICKINGTYPE				+ " AS " + properties::pharmosbatchorderhead::PICKINGTYPE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::BOOKINGTYPE				+ " AS " + properties::pharmosbatchorderhead::BOOKINGTYPE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::CUSTOMERNO				+ " AS " + properties::pharmosbatchorderhead::CUSTOMERNO.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::INTERNALCUSTOMERNO		+ " AS " + properties::pharmosbatchorderhead::INTERNALCUSTOMERNO.getName() + " "		
				", " + columnnames::pharmosbatchorderhead::INFOTEXT					+ " AS " + properties::pharmosbatchorderhead::INFOTEXT.getName() + " "					
				", " + columnnames::pharmosbatchorderhead::ORIGINTYPE				+ " AS " + properties::pharmosbatchorderhead::ORIGINTYPE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::ORIGINBRANCHNO			+ " AS " + properties::pharmosbatchorderhead::ORIGINBRANCHNO.getName() + " "			
				", " + columnnames::pharmosbatchorderhead::CUSTOMERFLAG				+ " AS " + properties::pharmosbatchorderhead::CUSTOMERFLAG.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::VALUEDATE				+ " AS " + properties::pharmosbatchorderhead::VALUEDATE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::DELIVERYDATE				+ " AS " + properties::pharmosbatchorderhead::DELIVERYDATE.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::SAPDELIVERYNOTE			+ " AS " + properties::pharmosbatchorderhead::SAPDELIVERYNOTE.getName() + " "	
				", " + columnnames::pharmosbatchorderhead::PARENTCOMPANYFLAG		+ " AS " + properties::pharmosbatchorderhead::PARENTCOMPANYFLAG.getName() + " "				
				", " + columnnames::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG		+ " AS " + properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG.getName() + " "	
				", " + columnnames::pharmosbatchorderhead::CSCORDERNO				+ " AS " + properties::pharmosbatchorderhead::CSCORDERNO.getName() + " "	
				" FROM " + domMod::TABLE_PHARMOSBATCHORDERHEAD + " "
				" WHERE " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS + " = '" + properties::pharmosbatchorderhead::PROCESSINGSTATUS.toSQLReplacementString() + "' "
				" AND " + columnnames::pharmosbatchorderhead::BRANCHNO + " = '" + properties::pharmosbatchorderhead::BRANCHNO.toSQLReplacementString() + "' "
				" ORDER BY " + columnnames::pharmosbatchorderhead::VSEOFFSET + " ASC "
				";"
				);

		resolve(stmt);

		BLOG_TRACE( logger, getSQLString() );
	}

	//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectLastKey)

	bool SelectLastKey::isExecutable() const
	{   
        METHODNAME_DEF( SelectLastKey, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		
		
		return isContainedAndSet( properties::pharmosbatchorderhead::BRANCHNO.getName() );
	}

	void SelectLastKey::buildSQLString()
	{	
        METHODNAME_DEF( SelectLastKey, buildSQLString );
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		static const basar::VarString stmt(
			"SELECT NVL(MAX(" + columnnames::pharmosbatchorderhead::VSEOFFSET + "), 0) "
			"FROM " + domMod::TABLE_PHARMOSBATCHORDERHEAD + " "
			"WHERE " + columnnames::pharmosbatchorderhead::BRANCHNO + " = " + properties::pharmosbatchorderhead::BRANCHNO.toSQLReplacementString() + " "
				"AND " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS + " = '" + domMod::batchOrder::processing::batchOrderDM::STATUS_CLOSED + "' "
			 );

		resolve(stmt);			

		BLOG_TRACE_SQLSTRING( logger );
	}

	//----------------------------------------------------------------------------
BUILDER_DEFINITION(InsertPharmosBatchOrderHead)

    bool InsertPharmosBatchOrderHead::isExecutable() const
    {
        METHODNAME_DEF( InsertPharmosBatchOrderHead, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		if ( getPropertyList().getState() != basar::SS_INSERT ){
			return false;
		}

		using namespace properties::pharmosbatchorderhead;

		static const basar::VarString properties(	BRANCHNO.toPropertyString() +
													VSEOFFSET.toPropertyString()  +
													TRANSFERREDTIMESTAMP.toPropertyString()  +
													BATCHORDERNO.toPropertyString()  +
													TRANSFERORDERNO.toPropertyString() );

		bool executable = arePropertiesSetAndAllInState( properties, basar::SS_INSERT ); 

		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		return executable;
    }

	void InsertPharmosBatchOrderHead::buildSQLString()
	{
        METHODNAME_DEF( InsertPharmosBatchOrderHead, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		
		
        static const basar::VarString constAttributes(  " " + columnnames::pharmosbatchorderhead::BRANCHNO + ", "
														" " + columnnames::pharmosbatchorderhead::CREATIONDATETIME + ", "
														" " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS + ", "
														" " + columnnames::pharmosbatchorderhead::VSEOFFSET + ", "
														" " + columnnames::pharmosbatchorderhead::TRANSFERREDTIMESTAMP + ", "
														" " + columnnames::pharmosbatchorderhead::BATCHORDERNO + ", "
														" " + columnnames::pharmosbatchorderhead::TRANSFERORDERNO + " " );

        static const basar::VarString constValues(  " " + properties::pharmosbatchorderhead::BRANCHNO.toSQLReplacementString() + ", " + 
													" " + "CURRENT YEAR TO DAY" + ", " + 
													" '" + domMod::batchOrder::processing::batchOrderDM::STATUS_OPEN + "', " + 
													" " + properties::pharmosbatchorderhead::VSEOFFSET.toSQLReplacementString() + ", " + 
													"'" + properties::pharmosbatchorderhead::TRANSFERREDTIMESTAMP.toSQLReplacementString() + "', " + 
													" " + properties::pharmosbatchorderhead::BATCHORDERNO.toSQLReplacementString() + ", " + 
													" " + properties::pharmosbatchorderhead::TRANSFERORDERNO.toSQLReplacementString() + " " );													                                                    

		basar::VarString variableAttributes; 
		basar::VarString variableValues;

		if( isContainedAndSet( properties::pharmosbatchorderhead::PROCESSINGSTATUS.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::PROCESSINGSTATUS.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::POSITIONCOUNT.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::POSITIONCOUNT + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::POSITIONCOUNT.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::ORDERTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::ORDERTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::ORDERTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::PICKINGTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::PICKINGTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::PICKINGTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::BOOKINGTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::BOOKINGTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::BOOKINGTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::CUSTOMERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::CUSTOMERNO + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::CUSTOMERNO.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::INTERNALCUSTOMERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::INTERNALCUSTOMERNO + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::INTERNALCUSTOMERNO	.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::INFOTEXT.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::INFOTEXT + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::INFOTEXT.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::ORIGINTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::ORIGINTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::ORIGINTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::ORIGINBRANCHNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::ORIGINBRANCHNO + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::ORIGINBRANCHNO.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::CUSTOMERFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::CUSTOMERFLAG + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::CUSTOMERFLAG.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::PARENTCOMPANYFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::PARENTCOMPANYFLAG + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::PARENTCOMPANYFLAG.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::VALUEDATE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::VALUEDATE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::VALUEDATE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::DELIVERYDATE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::DELIVERYDATE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::DELIVERYDATE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderhead::SAPDELIVERYNOTE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderhead::SAPDELIVERYNOTE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderhead::SAPDELIVERYNOTE.toSQLReplacementString() + "' " );
		}

		const basar::VarString sqlStatement( "INSERT INTO " + domMod::TABLE_PHARMOSBATCHORDERHEAD + " (" + constAttributes + variableAttributes + 
												") VALUES (" + constValues + variableValues + ");" );

		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdatePharmosBatchOrderHead)

    bool UpdatePharmosBatchOrderHead::isExecutable() const
    {
        METHODNAME_DEF( UpdatePharmosBatchOrderHead, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		if ( getPropertyList().getState() != basar::SS_UPDATE ){
			return false;
		}

		static const basar::VarString propertiesSet( 
			properties::pharmosbatchorderhead::BRANCHNO.toPropertyString() + 
			properties::pharmosbatchorderhead::VSEOFFSET.toPropertyString() );

		static const basar::VarString propertiesUpdateable( 
			properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP.toPropertyString() + 
			properties::pharmosbatchorderhead::PROCESSINGSTATUS.toPropertyString() );

		bool executable = are1stPropertiesSetAnd2ndOneInState( propertiesSet, propertiesUpdateable, basar::SS_UPDATE );
		
		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		return executable;
    }

	void UpdatePharmosBatchOrderHead::buildSQLString()
	{		
        METHODNAME_DEF( UpdatePharmosBatchOrderHead, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		static const basar::VarString updateStatement( "UPDATE " + domMod::TABLE_PHARMOSBATCHORDERHEAD + " SET " );			

		static const basar::VarString whereStatement( "WHERE " + columnnames::pharmosbatchorderhead::BRANCHNO + "=" + properties::pharmosbatchorderhead::BRANCHNO.toSQLReplacementString() + " "
			                                          "AND " + columnnames::pharmosbatchorderhead::VSEOFFSET + "=" + properties::pharmosbatchorderhead::VSEOFFSET.toSQLReplacementString() + " " );

		basar::VarString variableSetStatement;

		if( arePropertiesSetAndOneMustBeInState( properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP.toPropertyString(), basar::SS_UPDATE ) )
		{
			variableSetStatement.append( " " + columnnames::pharmosbatchorderhead::PROCESSEDTIMESTAMP+ "='" + properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP.toSQLReplacementString() + "', " );
		}
        		
        if( arePropertiesSetAndOneMustBeInState(properties::pharmosbatchorderhead::PROCESSINGSTATUS.toPropertyString(), basar::SS_UPDATE) )
		{
            variableSetStatement.append( " " + columnnames::pharmosbatchorderhead::PROCESSINGSTATUS + "='" + properties::pharmosbatchorderhead::PROCESSINGSTATUS.toSQLReplacementString() + "', " );
        }

		if( arePropertiesSetAndOneMustBeInState( properties::pharmosbatchorderhead::CSCORDERNO.toPropertyString(), basar::SS_UPDATE ) )
		{
			variableSetStatement.append( " " + columnnames::pharmosbatchorderhead::CSCORDERNO+ "='" + properties::pharmosbatchorderhead::CSCORDERNO.toSQLReplacementString() + "', " );
		}

		// remove last , from variableSetStatement
		variableSetStatement.trim();
		variableSetStatement = variableSetStatement.substr( 0, variableSetStatement.length() - 1 );		

		const basar::VarString sqlStatement( updateStatement + " " + variableSetStatement + " " + whereStatement );

		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );		
	}

} // namespace acc_pharmosbatchorderhead

//----------------------------------------------------------------------------
