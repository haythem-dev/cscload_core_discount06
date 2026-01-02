#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSESQLMAPPER_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSESQLMAPPER_H

#include "orderresponsemapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace msv3 {

class OrderResponseSQLMapper : public OrderResponseMapperBase
{
public:
    OrderResponseSQLMapper(OrderResponsePtr transmissionResponse, const basar::db::sql::ResultsetRef resultSet);
    OrderResponseSQLMapper(OrderResponsePtr transmissionResponse);
    virtual ~OrderResponseSQLMapper();

    static const basar::VarString getSelectSQL();
    static const basar::VarString getInsertSQL();
    static const basar::VarString getUpdateSQL();

	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::VarString& orderUuid);
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder(const OrderResponsePtr orderResponse);
	static const libcsc::persistence::ISqlParameterBinderPtr getUpdateSqlParameterBinder(const OrderResponsePtr orderResponse);

	static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::VarString& orderUuid);
	static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const OrderResponsePtr orderResponse);
	static void bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, const OrderResponsePtr orderResponse);

protected:
	virtual void doMap();
	virtual void doMapSerial(const basar::Int32& id);

private:
	OrderResponseSQLMapper(const OrderResponseSQLMapper&);
	OrderResponseSQLMapper& operator=(const OrderResponseSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSESQLMAPPER_H
