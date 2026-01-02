//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.PHARMOSBATCHORDERPOS
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#include "cmndm.h"
#include "pharmosbatchorderposacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "pharmosbatchorderposacc_definitions.h"
#include "csc_phabor_table_definitions.h"
#include "batchorderdm_definitions.h"
#include "log_macros.h"
#include <loggerpool.h>
#include <iostream>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_pharmosbatchorderpos
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_pharmosbatchorderpos::ACC_PHARMOSBATCHORDERPOS)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::BRANCHNO 						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::CREATIONDATETIME 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::VSEOFFSET 						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::PROCESSINGSTATE 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP 			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::TRANSFERREDTIMESTAMP			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::TRANSFERORDERNO 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::TRANSFERORDERPOSNO 			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::BATCHORDERNO 					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::BATCHORDERPOSNO 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::BATCHSTATE						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ARTICLENO						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ORDERQTY						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::QTYINKIND 						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ORIGINBRANCHNO 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ORIGINCUSTOMERNO 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::POSITIONTEXT 					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::IBTRECORDTYPE					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::IBTPARTNER2					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::IBTPARTNER3 					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::SALEINCREASEFLAG 				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO 			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::IBTTYPE 						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY 			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::NOBOOKINGFLAG					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::EDIBATCHORDERNO				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ARTICLECODE 					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::ARTICLETYPE 					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::RECORDTYPE                     )
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::INVOICEPRICE					)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::LINEVALUE						)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE				)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmosbatchorderpos::PRICEZERO						)

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_pharmosbatchorderpos::SELECT_PHARMOSBATCHORDERPOS_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectPharmosBatchOrderPosByPattern)
		SQL_BUILDER_PUSH_BACK(SelectPharmosBatchOrderPosByPattern)

	ACCESS_METHOD( lit::acc_pharmosbatchorderpos::SELECT_LAST_KEY )
		SQL_BUILDER_CREATE(SelectLastKey)
		SQL_BUILDER_PUSH_BACK(SelectLastKey)

	ACCESS_METHOD( lit::acc_pharmosbatchorderpos::SAVE_PHARMOSBATCHORDERPOS )
		SQL_BUILDER_CREATE(InsertPharmosBatchOrderPos)
		SQL_BUILDER_PUSH_BACK(InsertPharmosBatchOrderPos)
		SQL_BUILDER_CREATE(UpdatePharmosBatchOrderPos)
		SQL_BUILDER_PUSH_BACK(UpdatePharmosBatchOrderPos)
	
END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectPharmosBatchOrderPosByPattern)

	bool SelectPharmosBatchOrderPosByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;		
		searchValues.push_back( properties::pharmosbatchorderpos::BATCHORDERNO.getName() );
		searchValues.push_back( properties::pharmosbatchorderpos::BRANCHNO.getName() );
		searchValues.push_back( properties::pharmosbatchorderpos::VSEOFFSET.getName() );		
		searchValues.push_back( properties::pharmosbatchorderpos::PROCESSINGSTATE.getName() );		
		
		return arePropertiesSet( searchValues );
	}
		
	void SelectPharmosBatchOrderPosByPattern::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::pharmosbatchorderpos::BRANCHNO 					+ " AS " + properties::pharmosbatchorderpos::BRANCHNO.getName() 				+ " "	
				", " + columnnames::pharmosbatchorderpos::CREATIONDATETIME 			+ " AS " + properties::pharmosbatchorderpos::CREATIONDATETIME.getName() 		+ " "			
				", " + columnnames::pharmosbatchorderpos::VSEOFFSET 				+ " AS " + properties::pharmosbatchorderpos::VSEOFFSET.getName() 				+ " "			
				", " + columnnames::pharmosbatchorderpos::PROCESSINGSTATE 			+ " AS " + properties::pharmosbatchorderpos::PROCESSINGSTATE.getName() 			+ " "		
				", " + columnnames::pharmosbatchorderpos::PROCESSEDTIMESTAMP 		+ " AS " + properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.getName() 		+ " "		
				", " + columnnames::pharmosbatchorderpos::TRANSFERREDTIMESTAMP		+ " AS " + properties::pharmosbatchorderpos::TRANSFERREDTIMESTAMP.getName()		+ " "		
				", " + columnnames::pharmosbatchorderpos::TRANSFERORDERNO 			+ " AS " + properties::pharmosbatchorderpos::TRANSFERORDERNO.getName() 			+ " "		
				", " + columnnames::pharmosbatchorderpos::TRANSFERORDERPOSNO 		+ " AS " + properties::pharmosbatchorderpos::TRANSFERORDERPOSNO.getName() 		+ " "		
				", " + columnnames::pharmosbatchorderpos::BATCHORDERNO 				+ " AS " + properties::pharmosbatchorderpos::BATCHORDERNO.getName() 			+ " "		
				", " + columnnames::pharmosbatchorderpos::BATCHORDERPOSNO 			+ " AS " + properties::pharmosbatchorderpos::BATCHORDERPOSNO.getName() 			+ " "		
				", " + columnnames::pharmosbatchorderpos::BATCHSTATE				+ " AS " + properties::pharmosbatchorderpos::BATCHSTATE.getName()				+ " "		
				", " + columnnames::pharmosbatchorderpos::ARTICLENO					+ " AS " + properties::pharmosbatchorderpos::ARTICLENO.getName()				+ " "		
				", " + columnnames::pharmosbatchorderpos::ORDERQTY					+ " AS " + properties::pharmosbatchorderpos::ORDERQTY.getName()					+ " "		
				", " + columnnames::pharmosbatchorderpos::QTYINKIND 				+ " AS " + properties::pharmosbatchorderpos::QTYINKIND.getName() 				+ " "	
				", " + columnnames::pharmosbatchorderpos::ORIGINBRANCHNO 			+ " AS " + properties::pharmosbatchorderpos::ORIGINBRANCHNO.getName() 			+ " "	
				", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERNO 			+ " AS " + properties::pharmosbatchorderpos::ORIGINCUSTOMERNO.getName() 		+ " "		
				", " + columnnames::pharmosbatchorderpos::POSITIONTEXT 				+ " AS " + properties::pharmosbatchorderpos::POSITIONTEXT.getName() 			+ " "			
				", " + columnnames::pharmosbatchorderpos::IBTRECORDTYPE				+ " AS " + properties::pharmosbatchorderpos::IBTRECORDTYPE.getName()			+ " "		
				", " + columnnames::pharmosbatchorderpos::IBTPARTNER2				+ " AS " + properties::pharmosbatchorderpos::IBTPARTNER2.getName()				+ " "			
				", " + columnnames::pharmosbatchorderpos::IBTPARTNER3 				+ " AS " + properties::pharmosbatchorderpos::IBTPARTNER3.getName() 				+ " "			
				", " + columnnames::pharmosbatchorderpos::SALEINCREASEFLAG 			+ " AS " + properties::pharmosbatchorderpos::SALEINCREASEFLAG.getName() 		+ " "		
				", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO 	+ " AS " + properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO.getName() 	+ " "		
				", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO	+ " AS " + properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO.getName()	+ " "		
				", " + columnnames::pharmosbatchorderpos::IBTTYPE 					+ " AS " + properties::pharmosbatchorderpos::IBTTYPE.getName() 					+ " "	
				", " + columnnames::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY 	+ " AS " + properties::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY.getName() 	+ " "	
				", " + columnnames::pharmosbatchorderpos::NOBOOKINGFLAG				+ " AS " + properties::pharmosbatchorderpos::NOBOOKINGFLAG.getName()			+ " "	
				", " + columnnames::pharmosbatchorderpos::EDIBATCHORDERNO			+ " AS " + properties::pharmosbatchorderpos::EDIBATCHORDERNO.getName()			+ " "	
				", " + columnnames::pharmosbatchorderpos::ARTICLECODE 				+ " AS " + properties::pharmosbatchorderpos::ARTICLECODE.getName()				+ " "	
				", " + columnnames::pharmosbatchorderpos::ARTICLETYPE 				+ " AS " + properties::pharmosbatchorderpos::ARTICLETYPE.getName() 				+ " "	
				", " + columnnames::pharmosbatchorderpos::RECORDTYPE                + " AS " + properties::pharmosbatchorderpos::RECORDTYPE.getName()               + " "
				", " + columnnames::pharmosbatchorderpos::PHARMACYPURCHASEPRICE     + " AS " + properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE.getName()    + " "
				", " + columnnames::pharmosbatchorderpos::DISCOUNTPERCENTAGE        + " AS " + properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE.getName()       + " "
				", " + columnnames::pharmosbatchorderpos::INVOICEPRICE 	            + " AS " + properties::pharmosbatchorderpos::INVOICEPRICE.getName()             + " "
				", " + columnnames::pharmosbatchorderpos::LINEVALUE 		        + " AS " + properties::pharmosbatchorderpos::LINEVALUE.getName()                + " "
				", " + columnnames::pharmosbatchorderpos::PIECEDISCOUNTVALUE	    + " AS " + properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE.getName()       + " "
				", " + columnnames::pharmosbatchorderpos::PRICEZERO 		        + " AS " + properties::pharmosbatchorderpos::PRICEZERO.getName()                + " "
				" FROM " + domMod::TABLE_PHARMOSBATCHORDERPOS + " "
//				" WHERE " + columnnames::pharmosbatchorderpos::VSEOFFSET + " > " + properties::pharmosbatchorderpos::VSEOFFSET.toSQLReplacementString() + " "
                " WHERE " + columnnames::pharmosbatchorderpos::BATCHORDERNO + " = '" + properties::pharmosbatchorderpos::BATCHORDERNO.toSQLReplacementString() + "' " 
				" AND " + columnnames::pharmosbatchorderpos::PROCESSINGSTATE + " = '" + properties::pharmosbatchorderpos::PROCESSINGSTATE.toSQLReplacementString() + "' " 
				" AND " + columnnames::pharmosbatchorderpos::BRANCHNO + " = '" + properties::pharmosbatchorderpos::BRANCHNO.toSQLReplacementString() + "' "
				" ORDER BY " + columnnames::pharmosbatchorderpos::VSEOFFSET + " ASC "
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
		
		return isContainedAndSet( properties::pharmosbatchorderpos::BRANCHNO.getName() );
	}

	void SelectLastKey::buildSQLString()
	{	
        METHODNAME_DEF( SelectLastKey, buildSQLString );
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		static const basar::VarString stmt(
			"SELECT NVL(MAX(" + columnnames::pharmosbatchorderpos::VSEOFFSET + "), 0) "
			"FROM " + domMod::TABLE_PHARMOSBATCHORDERPOS + " WHERE "			
			" " + columnnames::pharmosbatchorderpos::BRANCHNO + " = " + properties::pharmosbatchorderpos::BRANCHNO.toSQLReplacementString() + ";" );

		resolve(stmt);			

		BLOG_TRACE_SQLSTRING( logger );
	}

	//----------------------------------------------------------------------------
BUILDER_DEFINITION(InsertPharmosBatchOrderPos)

    bool InsertPharmosBatchOrderPos::isExecutable() const
    {
        METHODNAME_DEF( InsertPharmosBatchOrderPos, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		if ( getPropertyList().getState() != basar::SS_INSERT ){
			return false;
		}

		using namespace properties::pharmosbatchorderpos;

		static const basar::VarString properties(	BRANCHNO.toPropertyString() +
													VSEOFFSET.toPropertyString()  +
													TRANSFERREDTIMESTAMP.toPropertyString()  + //
													BATCHORDERNO.toPropertyString()  +
													ARTICLENO.toPropertyString() +
													ORDERQTY.toPropertyString() +
													QTYINKIND.toPropertyString() 
													);

		bool executable = arePropertiesSetAndAllInState( properties, basar::SS_INSERT ); 

		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		return executable;
    }

	void InsertPharmosBatchOrderPos::buildSQLString()
	{
        METHODNAME_DEF( InsertPharmosTransaction, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		
		 
        static const basar::VarString constAttributes(  " " + columnnames::pharmosbatchorderpos::BRANCHNO + ", "
													    " " + columnnames::pharmosbatchorderpos::CREATIONDATETIME + ", "
														" " + columnnames::pharmosbatchorderpos::PROCESSINGSTATE + ", "
														" " + columnnames::pharmosbatchorderpos::VSEOFFSET + ", "
														" " + columnnames::pharmosbatchorderpos::TRANSFERREDTIMESTAMP + ", "
														" " + columnnames::pharmosbatchorderpos::BATCHORDERNO + ", "
														" " + columnnames::pharmosbatchorderpos::ARTICLENO + ", "
														" " + columnnames::pharmosbatchorderpos::ORDERQTY + ", "
														" " + columnnames::pharmosbatchorderpos::QTYINKIND + " " );

        static const basar::VarString constValues(  " " + properties::pharmosbatchorderpos::BRANCHNO.toSQLReplacementString() + ", " + 
													" " + "CURRENT YEAR TO DAY" + ", " + 
													"'" + domMod::batchOrder::processing::batchOrderDM::STATUS_OPEN + "', " + 
													" " + properties::pharmosbatchorderpos::VSEOFFSET.toSQLReplacementString() + ", " + 
													"'" + properties::pharmosbatchorderpos::TRANSFERREDTIMESTAMP.toSQLReplacementString() + "', " + 
													" " + properties::pharmosbatchorderpos::BATCHORDERNO.toSQLReplacementString() + ", " + 
													" " + properties::pharmosbatchorderpos::ARTICLENO.toSQLReplacementString() + ", " +
													" " + properties::pharmosbatchorderpos::ORDERQTY.toSQLReplacementString() + ", " +
													" " + properties::pharmosbatchorderpos::QTYINKIND.toSQLReplacementString() + " " );

		basar::VarString variableAttributes; 
		basar::VarString variableValues;

		if( isContainedAndSet( properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::PROCESSEDTIMESTAMP + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::TRANSFERORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::TRANSFERORDERNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::TRANSFERORDERNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::TRANSFERORDERPOSNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::TRANSFERORDERPOSNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::TRANSFERORDERPOSNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::BATCHORDERPOSNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::BATCHORDERPOSNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::BATCHORDERPOSNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::BATCHSTATE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::BATCHSTATE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::BATCHSTATE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::ORIGINBRANCHNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ORIGINBRANCHNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::ORIGINBRANCHNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::ORIGINCUSTOMERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::ORIGINCUSTOMERNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::POSITIONTEXT.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::POSITIONTEXT + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::POSITIONTEXT.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::IBTRECORDTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::IBTRECORDTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::IBTRECORDTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::IBTPARTNER2.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::IBTPARTNER2 + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::IBTPARTNER2.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::IBTPARTNER3.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::IBTPARTNER3 + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::IBTPARTNER3.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::SALEINCREASEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::SALEINCREASEFLAG + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::SALEINCREASEFLAG.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::IBTTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::IBTTYPE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::IBTTYPE.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::NOBOOKINGFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::NOBOOKINGFLAG + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::NOBOOKINGFLAG.toSQLReplacementString() + "' " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::EDIBATCHORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::EDIBATCHORDERNO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::EDIBATCHORDERNO.toSQLReplacementString() + " " );
		} 			
		if( isContainedAndSet( properties::pharmosbatchorderpos::ARTICLECODE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ARTICLECODE + " " );
			variableValues.append( ", '" + properties::pharmosbatchorderpos::ARTICLECODE.toSQLReplacementString() + "' " );
		}			
		if( isContainedAndSet( properties::pharmosbatchorderpos::ARTICLETYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::ARTICLETYPE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::ARTICLETYPE.toSQLReplacementString() + " " );
		}	
		if( isContainedAndSet( properties::pharmosbatchorderpos::RECORDTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::RECORDTYPE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::RECORDTYPE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::PHARMACYPURCHASEPRICE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::DISCOUNTPERCENTAGE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::INVOICEPRICE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::INVOICEPRICE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::INVOICEPRICE.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::LINEVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::LINEVALUE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::LINEVALUE.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::PIECEDISCOUNTVALUE + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE.toSQLReplacementString() + " " );
		}
		if( isContainedAndSet( properties::pharmosbatchorderpos::PRICEZERO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmosbatchorderpos::PRICEZERO + " " );
			variableValues.append( ", " + properties::pharmosbatchorderpos::PRICEZERO.toSQLReplacementString() + " " );
		}

		const basar::VarString sqlStatement( "INSERT INTO " + domMod::TABLE_PHARMOSBATCHORDERPOS + " (" + constAttributes + variableAttributes + 
												") VALUES (" + constValues + variableValues + ");" );

		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdatePharmosBatchOrderPos)

    bool UpdatePharmosBatchOrderPos::isExecutable() const
    {
        METHODNAME_DEF( UpdatePharmosTransaction, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		if ( getPropertyList().getState() != basar::SS_UPDATE ){
			return false;
		}

		static const basar::VarString propertiesSet( 
			properties::pharmosbatchorderpos::BRANCHNO.toPropertyString() + 
			properties::pharmosbatchorderpos::VSEOFFSET.toPropertyString() );

		static const basar::VarString propertiesUpdateable( 
			properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.toPropertyString() + 
			properties::pharmosbatchorderpos::PROCESSINGSTATE.toPropertyString() );

		bool executable = are1stPropertiesSetAnd2ndOneInState( propertiesSet, propertiesUpdateable, basar::SS_UPDATE );
		
		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		return executable;
    }

	void UpdatePharmosBatchOrderPos::buildSQLString()
	{		
        METHODNAME_DEF( UpdatePharmosTransaction, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );		

		static const basar::VarString updateStatement( "UPDATE " + domMod::TABLE_PHARMOSBATCHORDERPOS + " SET " );			

		static const basar::VarString whereStatement( "WHERE " + columnnames::pharmosbatchorderpos::BRANCHNO + "=" + properties::pharmosbatchorderpos::BRANCHNO.toSQLReplacementString() + " "
			                                          "AND " + columnnames::pharmosbatchorderpos::VSEOFFSET + "=" + properties::pharmosbatchorderpos::VSEOFFSET.toSQLReplacementString() + " " );

		basar::VarString variableSetStatement;

		if( arePropertiesSetAndOneMustBeInState( properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.toPropertyString(), basar::SS_UPDATE ) )
		{
			variableSetStatement.append( " " + columnnames::pharmosbatchorderpos::PROCESSEDTIMESTAMP+ "='" + properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP.toSQLReplacementString() + "', " );
		}
        		
        if( arePropertiesSetAndOneMustBeInState(properties::pharmosbatchorderpos::PROCESSINGSTATE.toPropertyString(), basar::SS_UPDATE) )
		{
            variableSetStatement.append( " " + columnnames::pharmosbatchorderpos::PROCESSINGSTATE + "='" + properties::pharmosbatchorderpos::PROCESSINGSTATE.toSQLReplacementString() + "', " );
        }

		// remove last , from variableSetStatement
		variableSetStatement.trim();
		variableSetStatement = variableSetStatement.substr( 0, variableSetStatement.length() - 1 );		

		const basar::VarString sqlStatement( updateStatement + " " + variableSetStatement + " " + whereStatement );

		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );		
	}

} // namespace acc_pharmosbatchorderpos

//----------------------------------------------------------------------------
