//----------------------------------------------------------------------------
/*! \file		pharmostransactionacc.cpp
 *  \brief		stringbuilder definition for pharmostransaction
 *  \author		Julian Machata
 *  \date		28.06.2012
 */
//----------------------------------------------------------------------------

#include "pharmostransactionacc.h"
#include "property_definitions.h"
#include "pharmostransactionacc_definitions.h"
#include "csc_phatra_table_definitions.h"
#include "columnname_definitions.h"
#include <loggerpool.h>
#include <iostream>
#include <classinfo_macros.h>
#include <log_macros.h>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_pharmostransaction
{
    using namespace properties::pharmostransaction;

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_pharmostransaction::ACC_PHARMOSTRANSACTION)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::BRANCHNO							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CREATIONDATETIME					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::VSEOFFSET						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PROCESSINGSTATUS					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PROCESSEDTIMESTAMP				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::TRANSFERREDTIMESTAMP				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::DATASETSEQUENCENO				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::RECORDTYPE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CUSTOMERNO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::BOOKINGTYPE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::USERID							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::INVOICENO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::INVOICETIMESTAMP					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CUSTOMERORDERNO					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CSCORDERNO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::TURNOVER							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PAYMENTDATE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PAYMENTTYPE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PRICETYPE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CHAINNO							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::REMAININGDISCACCVALUE			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::INVOICEVALUE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::DISCACCOPERATIONNO				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PRIORITY							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::VOUCHERTYPE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::ARTICLENO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::BATCH							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::EXPIRYDATE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::QUANTITY							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::DEBITVALUE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::LIMITVALUE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::SUPPLIERNO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PURCHASEORDERNO					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::COSTPRICE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::STORAGELOCATION					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::STORAGEAREA						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::STATIONNO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::EXPIRYDATECHANGEFLAG				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::COSTPRICECHANGEFLAG				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG	);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG		);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PHARMACYPURCHASEPRICE			);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::PHARMACYSELLPRICE				);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::IBTBRANCHNO						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::CODEBLOCAGE						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::QUANTITYNATRA					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::ORDERPOSITIONNO					);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::DAILYCLOSING						);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::ORIGIN							);
		PROPERTY_DESCRIPTION_LIST_ADD( properties::pharmostransaction::ORDERSUPPLIERNO					);

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_pharmostransaction::SELECT_LAST_KEY )
		SQL_BUILDER_CREATE(SelectLastKey)
		SQL_BUILDER_PUSH_BACK(SelectLastKey)

    ACCESS_METHOD( lit::acc_pharmostransaction::SELECT_OPEN_TRANSACTIONS )
		SQL_BUILDER_CREATE( SelectOpenTransactions )
		SQL_BUILDER_PUSH_BACK( SelectOpenTransactions )

	ACCESS_METHOD( lit::acc_pharmostransaction::SAVE_PHARMOSTRANSACTION )
		SQL_BUILDER_CREATE(InsertPharmosTransaction)
		SQL_BUILDER_PUSH_BACK(InsertPharmosTransaction)
		SQL_BUILDER_CREATE(UpdatePharmosTransaction)
		SQL_BUILDER_PUSH_BACK(UpdatePharmosTransaction)

END_ACCESSOR_DEFINITION


//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectLastKey)

	bool SelectLastKey::isExecutable() const
	{
        METHODNAME_DEF( SelectLastKey, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		return isContainedAndSet( properties::pharmostransaction::BRANCHNO.getName() );
	}

	void SelectLastKey::buildSQLString()
	{
        METHODNAME_DEF( SelectLastKey, buildSQLString );
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		static const basar::VarString stmt(
			"SELECT NVL(MAX(" + columnnames::pharmostransaction::VSEOFFSET + "), 0) "
			"FROM " + domMod::TABLE_PHARMOSTRANSACTION + " WHERE "
			" " + columnnames::pharmostransaction::BRANCHNO + " = " + properties::pharmostransaction::BRANCHNO.toSQLReplacementString() + ";" );

		resolve(stmt);

		BLOG_TRACE_SQLSTRING( logger );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION( SelectOpenTransactions )

	bool SelectOpenTransactions::isExecutable() const
	{
        METHODNAME_DEF( SelectOpenTransactions, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

        bool executable = arePropertiesSet( properties::pharmostransaction::PROCESSINGSTATUS.toPropertyString() ) ;
        executable &= arePropertiesSet( properties::pharmostransaction::BRANCHNO.toPropertyString() );
        CHECK_EXECUTABILITY( getPropertyList(), logger, fun );

        return executable;
	}


    void SelectOpenTransactions::buildSQLString()
    {
        METHODNAME_DEF( SelectOpenTransactions, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

        /////////////////////////////////////////////////////////////////////////////////////////////////
        // const attributes
        /////////////////////////////////////////////////////////////////////////////////////////////////
        static const basar::VarString stmt(
			"SELECT "
            " " + columnnames::pharmostransaction::BRANCHNO							+ " AS " + properties::pharmostransaction::BRANCHNO.getName() + ", "
            " " + columnnames::pharmostransaction::CREATIONDATETIME					+ " AS " + properties::pharmostransaction::CREATIONDATETIME.getName() + ", "
            " " + columnnames::pharmostransaction::VSEOFFSET						+ " AS " + properties::pharmostransaction::VSEOFFSET.getName() + ", "
            " " + columnnames::pharmostransaction::PROCESSINGSTATUS					+ " AS " + properties::pharmostransaction::PROCESSINGSTATUS.getName() + ", "
            " " + columnnames::pharmostransaction::PROCESSEDTIMESTAMP				+ " AS " + properties::pharmostransaction::PROCESSEDTIMESTAMP.getName() + ", "
            " " + columnnames::pharmostransaction::TRANSFERREDTIMESTAMP 			+ " AS " + properties::pharmostransaction::TRANSFERREDTIMESTAMP.getName() + ", "
            " " + columnnames::pharmostransaction::DATASETSEQUENCENO				+ " AS " + properties::pharmostransaction::DATASETSEQUENCENO.getName() + ", "
            " " + columnnames::pharmostransaction::RECORDTYPE						+ " AS " + properties::pharmostransaction::RECORDTYPE.getName() + ", "
            " " + columnnames::pharmostransaction::CUSTOMERNO						+ " AS " + properties::pharmostransaction::CUSTOMERNO.getName() + ", "
            " " + columnnames::pharmostransaction::BOOKINGTYPE						+ " AS " + properties::pharmostransaction::BOOKINGTYPE.getName() + ", "
            " " + columnnames::pharmostransaction::USERID							+ " AS " + properties::pharmostransaction::USERID.getName() + ", "
            " " + columnnames::pharmostransaction::INVOICENO						+ " AS " + properties::pharmostransaction::INVOICENO.getName() + ", "
            " " + columnnames::pharmostransaction::INVOICETIMESTAMP					+ " AS " + properties::pharmostransaction::INVOICETIMESTAMP.getName() + ", "
            " " + columnnames::pharmostransaction::CUSTOMERORDERNO					+ " AS " + properties::pharmostransaction::CUSTOMERORDERNO.getName() + ", "
            " " + columnnames::pharmostransaction::CSCORDERNO						+ " AS " + properties::pharmostransaction::CSCORDERNO.getName() + ", "
            " " + columnnames::pharmostransaction::TURNOVER							+ " AS " + properties::pharmostransaction::TURNOVER.getName() + ", "
            " " + columnnames::pharmostransaction::PAYMENTDATE						+ " AS " + properties::pharmostransaction::PAYMENTDATE.getName() + ", "
            " " + columnnames::pharmostransaction::PAYMENTTYPE						+ " AS " + properties::pharmostransaction::PAYMENTTYPE.getName() + ", "
            " " + columnnames::pharmostransaction::PRICETYPE						+ " AS " + properties::pharmostransaction::PRICETYPE.getName() + ", "
            " " + columnnames::pharmostransaction::CHAINNO							+ " AS " + properties::pharmostransaction::CHAINNO.getName() + ", "
            " " + columnnames::pharmostransaction::REMAININGDISCACCVALUE			+ " AS " + properties::pharmostransaction::REMAININGDISCACCVALUE.getName() + ", "
            " " + columnnames::pharmostransaction::INVOICEVALUE						+ " AS " + properties::pharmostransaction::INVOICEVALUE.getName() + ", "
            " " + columnnames::pharmostransaction::DISCACCOPERATIONNO				+ " AS " + properties::pharmostransaction::DISCACCOPERATIONNO.getName() + ", "
            " " + columnnames::pharmostransaction::PRIORITY							+ " AS " + properties::pharmostransaction::PRIORITY.getName() + ", "
            " " + columnnames::pharmostransaction::VOUCHERTYPE						+ " AS " + properties::pharmostransaction::VOUCHERTYPE.getName() + ", "
            " " + columnnames::pharmostransaction::ARTICLENO						+ " AS " + properties::pharmostransaction::ARTICLENO.getName() + ", "
            " " + columnnames::pharmostransaction::BATCH							+ " AS " + properties::pharmostransaction::BATCH.getName() + ", "
            " " + columnnames::pharmostransaction::EXPIRYDATE						+ " AS " + properties::pharmostransaction::EXPIRYDATE.getName() + ", "
            " " + columnnames::pharmostransaction::QUANTITY							+ " AS " + properties::pharmostransaction::QUANTITY.getName() + ", "
            " " + columnnames::pharmostransaction::DEBITVALUE						+ " AS " + properties::pharmostransaction::DEBITVALUE.getName() + ", "
            " " + columnnames::pharmostransaction::LIMITVALUE						+ " AS " + properties::pharmostransaction::LIMITVALUE.getName() + ", "
            " " + columnnames::pharmostransaction::SUPPLIERNO						+ " AS " + properties::pharmostransaction::SUPPLIERNO.getName() + ", "
            " " + columnnames::pharmostransaction::PURCHASEORDERNO					+ " AS " + properties::pharmostransaction::PURCHASEORDERNO.getName() + ", "
            " " + columnnames::pharmostransaction::COSTPRICE						+ " AS " + properties::pharmostransaction::COSTPRICE.getName() + ", "
            " " + columnnames::pharmostransaction::STORAGELOCATION					+ " AS " + properties::pharmostransaction::STORAGELOCATION.getName() + ", "
			" " + columnnames::pharmostransaction::STORAGEAREA						+ " AS " + properties::pharmostransaction::STORAGEAREA.getName() + ", "
            " " + columnnames::pharmostransaction::STATIONNO						+ " AS " + properties::pharmostransaction::STATIONNO.getName() + ", "
            " " + columnnames::pharmostransaction::EXPIRYDATECHANGEFLAG				+ " AS " + properties::pharmostransaction::EXPIRYDATECHANGEFLAG.getName() + ", "
            " " + columnnames::pharmostransaction::STORAGELOCATIONCHANGEFLAG		+ " AS " + properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG.getName() + ", "
            " " + columnnames::pharmostransaction::COSTPRICECHANGEFLAG				+ " AS " + properties::pharmostransaction::COSTPRICECHANGEFLAG.getName() + ", "
            " " + columnnames::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG	+ " AS " + properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG.getName() + ", "
			" " + columnnames::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG		+ " AS " + properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG.getName() + ", "
            " " + columnnames::pharmostransaction::PHARMACYPURCHASEPRICE			+ " AS " + properties::pharmostransaction::PHARMACYPURCHASEPRICE.getName() + ", "
            " " + columnnames::pharmostransaction::PHARMACYSELLPRICE				+ " AS " + properties::pharmostransaction::PHARMACYSELLPRICE.getName() + ", "
            " " + columnnames::pharmostransaction::IBTBRANCHNO 						+ " AS " + properties::pharmostransaction::IBTBRANCHNO.getName() + ", "
            " " + columnnames::pharmostransaction::CODEBLOCAGE 						+ " AS " + properties::pharmostransaction::CODEBLOCAGE.getName() + ", "
			" " + columnnames::pharmostransaction::QUANTITYNATRA					+ " AS " + properties::pharmostransaction::QUANTITYNATRA.getName() + ", "
			" " + columnnames::pharmostransaction::ORDERPOSITIONNO					+ " AS " + properties::pharmostransaction::ORDERPOSITIONNO.getName() + ", "
			" " + columnnames::pharmostransaction::DAILYCLOSING						+ " AS " + properties::pharmostransaction::DAILYCLOSING.getName() + ", "
			" " + columnnames::pharmostransaction::ORDERSUPPLIERNO					+ " AS " + properties::pharmostransaction::ORDERSUPPLIERNO.getName() + " "
            "FROM " + domMod::TABLE_PHARMOSTRANSACTION + " "
		    "WHERE "
			" " + columnnames::pharmostransaction::PROCESSINGSTATUS + " = '" + properties::pharmostransaction::PROCESSINGSTATUS.toSQLReplacementString() + "' "
            " AND "
            " " + columnnames::pharmostransaction::BRANCHNO + " = " + properties::pharmostransaction::BRANCHNO.toSQLReplacementString() + ";" );

		resolve( stmt );

        BLOG_TRACE_SQLSTRING( logger );
    }

//----------------------------------------------------------------------------
BUILDER_DEFINITION(InsertPharmosTransaction)

    bool InsertPharmosTransaction::isExecutable() const
    {
        METHODNAME_DEF( InsertPharmosTransaction, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		using namespace properties::pharmostransaction;

		static const basar::VarString properties(	BRANCHNO.toPropertyString() +
													CREATIONDATETIME.toPropertyString() +
													VSEOFFSET.toPropertyString() +
													DAILYCLOSING.toPropertyString() +
													ORIGIN.toPropertyString() );

		const bool executable = arePropertiesSetAndAllInState( properties, basar::SS_INSERT );

		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		BLOG_TRACE_SQLSTRING( logger );
		return executable;
    }

	void InsertPharmosTransaction::buildSQLString()
	{
        METHODNAME_DEF( InsertPharmosTransaction, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

        static const basar::VarString constAttributes(  " " + columnnames::pharmostransaction::BRANCHNO + ", " +
														" " + columnnames::pharmostransaction::CREATIONDATETIME + ", " +
														" " + columnnames::pharmostransaction::VSEOFFSET + ", " +
														" " + columnnames::pharmostransaction::DAILYCLOSING + ", "
														" " + columnnames::pharmostransaction::ORIGIN + " "
														 );

        static const basar::VarString constValues(  " " + properties::pharmostransaction::BRANCHNO.toSQLReplacementString() + ", " +
													"'" + properties::pharmostransaction::CREATIONDATETIME.toSQLReplacementString() + "', " +
                                                    " " + properties::pharmostransaction::VSEOFFSET.toSQLReplacementString() + ", " +
													" " + properties::pharmostransaction::DAILYCLOSING.toSQLReplacementString() + ", "
													" " + properties::pharmostransaction::ORIGIN.toSQLReplacementString() + " "
													 );

		basar::VarString variableAttributes;
		basar::VarString variableValues;

		if( isContainedAndSet( properties::pharmostransaction::RECORDTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::RECORDTYPE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::RECORDTYPE.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::DATASETSEQUENCENO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::DATASETSEQUENCENO + " " );
			variableValues.append( ", " + properties::pharmostransaction::DATASETSEQUENCENO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::TRANSFERREDTIMESTAMP.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::TRANSFERREDTIMESTAMP + " " );
			variableValues.append( ", '" + properties::pharmostransaction::TRANSFERREDTIMESTAMP.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PROCESSINGSTATUS.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PROCESSINGSTATUS + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PROCESSINGSTATUS.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PROCESSEDTIMESTAMP.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PROCESSEDTIMESTAMP + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PROCESSEDTIMESTAMP.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::CUSTOMERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::CUSTOMERNO + " " );
			variableValues.append( ", '" + properties::pharmostransaction::CUSTOMERNO.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::BOOKINGTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::BOOKINGTYPE + " " );
			variableValues.append( ", " + properties::pharmostransaction::BOOKINGTYPE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::USERID.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::USERID + " " );
			variableValues.append( ", " + properties::pharmostransaction::USERID.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::INVOICENO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::INVOICENO + " " );
			variableValues.append( ", '" + properties::pharmostransaction::INVOICENO.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::INVOICETIMESTAMP.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::INVOICETIMESTAMP + " " );
			variableValues.append( ", '" + properties::pharmostransaction::INVOICETIMESTAMP.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::CUSTOMERORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::CUSTOMERORDERNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::CUSTOMERORDERNO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::CSCORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::CSCORDERNO + " " );
			variableValues.append( ", '" + properties::pharmostransaction::CSCORDERNO.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::TURNOVER.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::TURNOVER + " " );
			variableValues.append( ", " + properties::pharmostransaction::TURNOVER.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PAYMENTDATE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PAYMENTDATE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PAYMENTDATE.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::PAYMENTTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PAYMENTTYPE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PAYMENTTYPE.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::PRICETYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PRICETYPE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PRICETYPE.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::CHAINNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::CHAINNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::CHAINNO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::REMAININGDISCACCVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::REMAININGDISCACCVALUE + " " );
			variableValues.append( ", " + properties::pharmostransaction::REMAININGDISCACCVALUE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::INVOICEVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::INVOICEVALUE + " " );
			variableValues.append( ", " + properties::pharmostransaction::INVOICEVALUE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::DISCACCOPERATIONNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::DISCACCOPERATIONNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::DISCACCOPERATIONNO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PRIORITY.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PRIORITY + " " );
			variableValues.append( ", " + properties::pharmostransaction::PRIORITY.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::VOUCHERTYPE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::VOUCHERTYPE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::VOUCHERTYPE.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::ARTICLENO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::ARTICLENO + " " );
			variableValues.append( ", " + properties::pharmostransaction::ARTICLENO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::BATCH.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::BATCH + " " );
			variableValues.append( ", '" + properties::pharmostransaction::BATCH.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::EXPIRYDATE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::EXPIRYDATE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::EXPIRYDATE.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::QUANTITY.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::QUANTITY + " " );
			variableValues.append( ", " + properties::pharmostransaction::QUANTITY.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::DEBITVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::DEBITVALUE + " " );
			variableValues.append( ", " + properties::pharmostransaction::DEBITVALUE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::LIMITVALUE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::LIMITVALUE + " " );
			variableValues.append( ", " + properties::pharmostransaction::LIMITVALUE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::SUPPLIERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::SUPPLIERNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::SUPPLIERNO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PURCHASEORDERNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PURCHASEORDERNO + " " );
			variableValues.append( ", '" + properties::pharmostransaction::PURCHASEORDERNO.toSQLReplacementString() + "' " );
		}

		if( isContainedAndSet( properties::pharmostransaction::COSTPRICE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::COSTPRICE + " " );
			variableValues.append( ", " + properties::pharmostransaction::COSTPRICE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::STORAGELOCATION.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::STORAGELOCATION + " " );
			variableValues.append( ", '" + properties::pharmostransaction::STORAGELOCATION.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::STORAGEAREA.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::STORAGEAREA + " " );
			variableValues.append( ", '" + properties::pharmostransaction::STORAGEAREA.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::STATIONNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::STATIONNO + " " );
			variableValues.append( ", '" + properties::pharmostransaction::STATIONNO.toSQLReplacementString() + "'" );
		}

		if( isContainedAndSet( properties::pharmostransaction::EXPIRYDATECHANGEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::EXPIRYDATECHANGEFLAG + " " );
			variableValues.append( ", " + properties::pharmostransaction::EXPIRYDATECHANGEFLAG.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::STORAGELOCATIONCHANGEFLAG + " " );
			variableValues.append( ", " + properties::pharmostransaction::STORAGELOCATIONCHANGEFLAG.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::COSTPRICECHANGEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::COSTPRICECHANGEFLAG + " " );
			variableValues.append( ", " + properties::pharmostransaction::COSTPRICECHANGEFLAG.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG + " " );
			variableValues.append( ", " + properties::pharmostransaction::PHARMACYPURCHASEPRICECHANGEFLAG.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG + " " );
			variableValues.append( ", " + properties::pharmostransaction::PHARMACYSELLPRICECHANGEFLAG.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PHARMACYPURCHASEPRICE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PHARMACYPURCHASEPRICE + " " );
			variableValues.append( ", " + properties::pharmostransaction::PHARMACYPURCHASEPRICE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::PHARMACYSELLPRICE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::PHARMACYSELLPRICE + " " );
			variableValues.append( ", " + properties::pharmostransaction::PHARMACYSELLPRICE.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::IBTBRANCHNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::IBTBRANCHNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::IBTBRANCHNO.toSQLReplacementString() + " " );
		}

		if( isContainedAndSet( properties::pharmostransaction::CODEBLOCAGE.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::CODEBLOCAGE + " " );
			variableValues.append( ", '" + properties::pharmostransaction::CODEBLOCAGE.toSQLReplacementString() + "' " );
		}

		if (isContainedAndSet( properties::pharmostransaction::QUANTITYNATRA.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::QUANTITYNATRA + " " );
			variableValues.append( ", " + properties::pharmostransaction::QUANTITYNATRA.toSQLReplacementString() + " " );
		}

		if (isContainedAndSet( properties::pharmostransaction::ORDERPOSITIONNO.getName() ) )
		{
			variableAttributes.append( ", " + columnnames::pharmostransaction::ORDERPOSITIONNO + " " );
			variableValues.append( ", " + properties::pharmostransaction::ORDERPOSITIONNO.toSQLReplacementString() + " " );
		}

		if (isContainedAndSet(properties::pharmostransaction::ORDERSUPPLIERNO.getName()))
		{
			variableAttributes.append(", " + columnnames::pharmostransaction::ORDERSUPPLIERNO + " ");
			variableValues.append(", " + properties::pharmostransaction::ORDERSUPPLIERNO.toSQLReplacementString() + " ");
		}

		const basar::VarString sqlStatement( "INSERT INTO " + domMod::TABLE_PHARMOSTRANSACTION + " (" + constAttributes + variableAttributes +
												") VALUES (" + constValues + variableValues + ");" );

        BLOG_TRACE( logger, sqlStatement.c_str() );
		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );
	}

//----------------------------------------------------------------------------
BUILDER_DEFINITION(UpdatePharmosTransaction)

    bool UpdatePharmosTransaction::isExecutable() const
    {
        METHODNAME_DEF( UpdatePharmosTransaction, isExecutable );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		static const basar::VarString propertiesSet(
			properties::pharmostransaction::BRANCHNO.toPropertyString() +
			properties::pharmostransaction::VSEOFFSET.toPropertyString() );

		static const basar::VarString propertiesUpdateable(
			properties::pharmostransaction::PROCESSEDTIMESTAMP.toPropertyString() +
			properties::pharmostransaction::PROCESSINGSTATUS.toPropertyString() );

		const bool executable = are1stPropertiesSetAnd2ndOneInState( propertiesSet, propertiesUpdateable, basar::SS_UPDATE );

		CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
		BLOG_TRACE_SQLSTRING( logger );
		return executable;
    }

	void UpdatePharmosTransaction::buildSQLString()
	{
        METHODNAME_DEF( UpdatePharmosTransaction, buildSQLString );
        static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
        BLOG_TRACE_METHOD( logger, fun );

		static const basar::VarString updateStatement( "UPDATE " + domMod::TABLE_PHARMOSTRANSACTION + " SET " );

		static const basar::VarString whereStatement( "WHERE " + columnnames::pharmostransaction::BRANCHNO + "=" + properties::pharmostransaction::BRANCHNO.toSQLReplacementString() + " "
			                                          "AND " + columnnames::pharmostransaction::VSEOFFSET + "=" + properties::pharmostransaction::VSEOFFSET.toSQLReplacementString() + " " );

		basar::VarString variableSetStatement;

		if( arePropertiesSetAndOneMustBeInState( properties::pharmostransaction::PROCESSEDTIMESTAMP.toPropertyString(), basar::SS_UPDATE ) )
		{
			variableSetStatement.append( " " + columnnames::pharmostransaction::PROCESSEDTIMESTAMP+ "='" + properties::pharmostransaction::PROCESSEDTIMESTAMP.toSQLReplacementString() + "', " );
		}

        if( arePropertiesSetAndOneMustBeInState(properties::pharmostransaction::PROCESSINGSTATUS.toPropertyString(), basar::SS_UPDATE) )
		{
            variableSetStatement.append( " " + columnnames::pharmostransaction::PROCESSINGSTATUS + "='" + properties::pharmostransaction::PROCESSINGSTATUS.toSQLReplacementString() + "', " );
        }

		// remove last , from variableSetStatement
		variableSetStatement.trim();
		variableSetStatement = variableSetStatement.substr( 0, variableSetStatement.length() - 1 );

		const basar::VarString sqlStatement( updateStatement + " " + variableSetStatement + " " + whereStatement );

		resolve( sqlStatement );
		BLOG_TRACE_SQLSTRING( logger );
	}

} // namespace acc_dkbvz

//----------------------------------------------------------------------------
