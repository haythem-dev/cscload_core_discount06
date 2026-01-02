#include "phadextransactionacc.h"
#include "phadextransactionacc_definitions.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "loggerpool/csc_phadex_loggerpool.h"

namespace infrastructure
{
namespace accessor
{
namespace phadex_transaction
{
BEGIN_ACCESSOR_DEFINITION( lit::PHADEX_TRANSACTION_ACC )

BEGIN_PROPERTY_DESCRIPTION_LIST
    PROPERTY_DESCRIPTION_LIST_ADD( properties::DATABASE_NAME );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::RECORD_NO );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::RECORD_TYPE );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::CREATION_DATETIME );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::TRANSFER_DATETIME );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::PROCESS_DATETIME );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::PROCESSED_FLAG );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::DATA );
    END_PROPERTY_DESCRIPTION_LIST

    ACCESS_METHOD( lit::SELECT_LAST_PHADEX_TRANSACTION_BY_PATTERN )	
    SQL_BUILDER_CREATE( SelectLastPhadexTransactionByPattern )
    SQL_BUILDER_PUSH_BACK( SelectLastPhadexTransactionByPattern )			

    ACCESS_METHOD( lit::SELECT_PHADEX_TRANSACTION_BY_PATTERN )	
    SQL_BUILDER_CREATE( SelectPhadexTransactionByPattern )
    SQL_BUILDER_PUSH_BACK( SelectPhadexTransactionByPattern )			

    ACCESS_METHOD( lit::SAVE_PHADEX_TRANSACTION )
    SQL_BUILDER_CREATE( UpdatePhadexTransaction )
    SQL_BUILDER_PUSH_BACK( UpdatePhadexTransaction )
    SQL_BUILDER_CREATE( InsertPhadexTransaction )
    SQL_BUILDER_PUSH_BACK( InsertPhadexTransaction )
END_ACCESSOR_DEFINITION


BUILDER_DEFINITION( SelectLastPhadexTransactionByPattern )

bool SelectLastPhadexTransactionByPattern::isExecutable() const
{
    return isContainedAndSet( properties::BRANCH_NO );
}

void SelectLastPhadexTransactionByPattern::buildSQLString()
{
    basar::VarString sql(
    "SELECT FIRST 1 "			
        "branchno AS "			+ properties::BRANCH_NO.getName() + ", "
        "recordno AS "			+ properties::RECORD_NO.getName() + ", "
        "recordtype AS "		+ properties::RECORD_TYPE.getName() + ", "
        "creationdatetime AS "	+ properties::CREATION_DATETIME.getName() + ", "
        "transferdatetime AS "	+ properties::TRANSFER_DATETIME.getName() + ", "
        "processdatetime AS "	+ properties::PROCESS_DATETIME.getName() + ", "
        "processedflag AS "		+ properties::PROCESSED_FLAG.getName() + ", "
        "data AS "				+ properties::DATA.getName() + " "
    "FROM ");
	if (isContainedAndSet(properties::DATABASE_NAME))
	{
		sql.append(properties::DATABASE_NAME.toSQLReplacementString() + ":");
	}
	sql.append(
        "phadextransaction "
    "WHERE "
        "branchno=" + properties::BRANCH_NO.toSQLReplacementString() + " "
    "ORDER BY "
        "recordno DESC "
		//"creationdatetime DESC, recordno DESC "
        //TODO FN????
	);

    resolve( sql );

    BLOG_DEBUG( csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString() );		
}

BUILDER_DEFINITION( SelectPhadexTransactionByPattern )
bool SelectPhadexTransactionByPattern::isExecutable() const
{
    const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() );
    return executable;
}

void SelectPhadexTransactionByPattern::buildSQLString()
{
	basar::VarString sql(
	"SELECT "
		"branchno AS "			+ properties::BRANCH_NO.getName() + ", "
		"recordno AS "			+ properties::RECORD_NO.getName() + ", "
		"recordtype AS "		+ properties::RECORD_TYPE.getName() + ", "
		"creationdatetime AS "	+ properties::CREATION_DATETIME.getName() + ", "
		"transferdatetime AS "	+ properties::TRANSFER_DATETIME.getName() + ", "
		"processdatetime AS "	+ properties::PROCESS_DATETIME.getName() + ", "
		"processedflag AS "		+ properties::PROCESSED_FLAG.getName() + ", "
		"data AS "				+ properties::DATA.getName() + " "
	"FROM ");
	if (isContainedAndSet(properties::DATABASE_NAME))
	{
		sql.append(properties::DATABASE_NAME.toSQLReplacementString() + ":");
	}
	sql.append(
		"phadextransaction "
	"WHERE "
		"branchno = " + properties::BRANCH_NO.toSQLReplacementString() + " "
		"AND "
		"processedflag = 0 "
	"ORDER BY "
		"creationdatetime, recordno "
    );
    resolve( sql );

    BLOG_DEBUG( csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString() );
}

BUILDER_DEFINITION( UpdatePhadexTransaction )
bool UpdatePhadexTransaction::isExecutable() const
{
    const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() ) &&
                            arePropertiesSet( properties::RECORD_NO.toPropertyString() ) &&
                            arePropertiesSet( properties::CREATION_DATETIME.toPropertyString() ) &&
                            arePropertiesSetAndAllInState( properties::PROCESSED_FLAG.toPropertyString(), basar::SS_UPDATE );
    return executable;
}

void UpdatePhadexTransaction::buildSQLString()
{
	basar::VarString sql(
	"UPDATE ");
	if (isContainedAndSet(properties::DATABASE_NAME))
	{
		sql.append(properties::DATABASE_NAME.toSQLReplacementString() + ":");
	}
	sql.append(
		"phadextransaction "
    "SET "
		"processdatetime = CURRENT, "
		"processedflag = "		+ properties::PROCESSED_FLAG.toSQLReplacementString()   + " "
    "WHERE "
		"branchno = "			+ properties::BRANCH_NO.toSQLReplacementString()		+ " AND "
		"recordno = "			+ properties::RECORD_NO.toSQLReplacementString()		+ " AND "
		"creationdatetime = '"	+ properties::CREATION_DATETIME.toSQLReplacementString()	+ "' ;"
    );
    resolve( sql );
	BLOG_DEBUG(csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString());
}


BUILDER_DEFINITION( InsertPhadexTransaction )
bool InsertPhadexTransaction::isExecutable() const
{
    const bool executable = arePropertiesSetAndAllInState( properties::BRANCH_NO.toPropertyString(),basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::RECORD_NO.toPropertyString(),basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::RECORD_TYPE.toPropertyString(),basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::CREATION_DATETIME.toPropertyString(), basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::TRANSFER_DATETIME.toPropertyString(), basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::PROCESS_DATETIME.toPropertyString(), basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::PROCESSED_FLAG.toPropertyString(), basar::SS_INSERT) &&
                        arePropertiesSetAndAllInState( properties::DATA.toPropertyString(), basar::SS_INSERT);

    return executable;
}

void InsertPhadexTransaction::buildSQLString()
{
    using namespace properties;
    static const basar::VarString insertSQL ( "INSERT INTO phadextransaction"
            "(branchno,recordno,recordtype,creationdatetime,transferdatetime,processdatetime,processedflag,data) VALUES("
            + BRANCH_NO.toSQLReplacementString()                +", "
            + RECORD_NO.toSQLReplacementString()                +", "
            + RECORD_TYPE.toSQLReplacementString()              +", "
            " '" + CREATION_DATETIME.toSQLReplacementString()   +"', "
            " '" + TRANSFER_DATETIME.toSQLReplacementString()   +"', "
            " '" + PROCESS_DATETIME.toSQLReplacementString()    +"', "
            + PROCESSED_FLAG.toSQLReplacementString()           +" ,"
            " '" + DATA.toSQLReplacementString()                +"' "
            ")");

    resolve( insertSQL );
	BLOG_DEBUG(csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString());
}

}
}
}
/*
create table "informix".phadextransaction 
(
	branchno smallint default 0 not null,
	recordno integer default 0 not null,
	recordtype smallint default 0 not null,
	creationdatetime datetime year to fraction(3) default datetime (9999-12-31 23:59:59.000) year to fraction(3) not null,
	transferdatetime datetime year to fraction(3) default CURRENT year to fraction(3) not null,
	processdatetime datetime year to fraction(3) default datetime (9999-12-31 23:59:59.000) year to fraction(3) not null,
	processedflag smallint default 0 not null,
	data lvarchar default '' not null
);

create unique index "informix".phadextransaction_i1 on "informix".phadextransaction 
( branchno,recordno,creationdatetime ) using btree;
*/