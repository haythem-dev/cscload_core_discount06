#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATASQLMAPPER_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATASQLMAPPER_H

#include "customerdatamapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace msv3 {

class CustomerDataSQLMapper : public CustomerDataMapperBase
{
public:
    CustomerDataSQLMapper(CustomerDataPtr customerData, const basar::db::sql::ResultsetRef resultSet);
    CustomerDataSQLMapper(CustomerDataPtr customerData);
    virtual ~CustomerDataSQLMapper();

    static const basar::VarString getSelectSQL();

	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::Int16& branchno, const basar::Int32& customerno);

	static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16& branchno, const basar::Int32& customerno);

protected:
	virtual void doMap();

private:
	CustomerDataSQLMapper(const CustomerDataSQLMapper&);
	CustomerDataSQLMapper& operator=(const CustomerDataSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATASQLMAPPER_H
