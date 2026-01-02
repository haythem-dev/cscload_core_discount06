#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSESQLMAPPER_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSESQLMAPPER_H

#include "transmissionresponsemapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace msv3 {

class TransmissionResponseSQLMapper	: public TransmissionResponseMapperBase
{
public:
	TransmissionResponseSQLMapper(TransmissionResponsePtr transmissionResponse, const basar::db::sql::ResultsetRef resultSet);
	TransmissionResponseSQLMapper(TransmissionResponsePtr transmissionResponse);
	virtual ~TransmissionResponseSQLMapper();

	static const basar::VarString getSelectSQL();
	static const basar::VarString getSelectByInternalHashSQL();
	static const basar::VarString getInsertSQL();
	static const basar::VarString getUpdateSQL();

	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::VarString& transmissionUuid);
	static const libcsc::persistence::ISqlParameterBinderPtr getSelectByInternalHashSqlParameterBinder(const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& internalHash, const basar::DateTime& checkFrom);
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder(const TransmissionResponsePtr transmissionResponse);
	static const libcsc::persistence::ISqlParameterBinderPtr getUpdateSqlParameterBinder(const TransmissionResponsePtr transmissionResponse);

	static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::VarString& transmissionUuid);
	static void bindSelectByInternalHashSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& internalHash, const basar::DateTime& checkFrom);
	static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const TransmissionResponsePtr transmissionResponse);
	static void bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, const TransmissionResponsePtr transmissionResponse);


protected:
	virtual void doMap();
	virtual void doMapSerial(const basar::Int32& id);

private:
	TransmissionResponseSQLMapper(const TransmissionResponseSQLMapper&);
	TransmissionResponseSQLMapper& operator=(const TransmissionResponseSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSESQLMAPPER_H
