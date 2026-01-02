#include "customerdatasqlmapper.h"
#include "customerdata.h"
#include "customerdataselectsqlparameterbinder.h"

namespace libcsc {
namespace msv3 {

CustomerDataSQLMapper::CustomerDataSQLMapper(CustomerDataPtr customerData, const basar::db::sql::ResultsetRef resultSet)
	: CustomerDataMapperBase(customerData),	m_ResultSet(resultSet)
{
}

CustomerDataSQLMapper::CustomerDataSQLMapper(CustomerDataPtr customerData)
	: CustomerDataMapperBase(customerData)
{
}

CustomerDataSQLMapper::~CustomerDataSQLMapper()
{
}

//----------------------------------------------------------------------------------
// SELECT
//----------------------------------------------------------------------------------
const basar::VarString CustomerDataSQLMapper::getSelectSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
			"SELECT filialnr, idfnr, "
			"CASE xmlinfolevel WHEN '1' THEN 1 WHEN '2' THEN 2 WHEN '3' THEN 3 WHEN '4' THEN 4 ELSE 0 END as xmlinfolevel "
			"FROM kunde WHERE filialnr=? AND idfnr=?";
	}
	return sql;
}

void CustomerDataSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16& branchno, const basar::Int32& customerno)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int16 _branchNo = branchno;
	static basar::Int32 _customerNo = customerno;

	basar::UInt32 counter = 0;

	prepStmt.setInt16(counter++, _branchNo);
	prepStmt.setInt32(counter++, _customerNo);
}

const libcsc::persistence::ISqlParameterBinderPtr CustomerDataSQLMapper::getSelectSqlParameterBinder(const basar::Int16& branchno, const basar::Int32& customerno)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new CustomerDataSelectSqlParameterBinder(branchno, customerno));
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void CustomerDataSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setXmlInfoLevel(m_ResultSet.getInt32("xmlinfolevel"));
}

} // end namespace msv3
} // end namespace libcsc
