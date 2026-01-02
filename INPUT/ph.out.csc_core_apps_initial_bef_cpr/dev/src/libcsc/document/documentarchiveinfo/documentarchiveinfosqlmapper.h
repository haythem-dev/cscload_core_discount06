#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOSQLMAPPER_H

#include "documentarchiveinfomapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace document {

class DocumentArchiveInfoSQLMapper : public DocumentArchiveInfoMapperBase
{
public:
	DocumentArchiveInfoSQLMapper(DocumentArchiveInfoPtr documentArchiveInfo, const basar::db::sql::ResultsetRef resultSet);
	DocumentArchiveInfoSQLMapper(DocumentArchiveInfoPtr documentArchiveInfo);
	virtual ~DocumentArchiveInfoSQLMapper();

	static const basar::VarString getSelectSQL(const basar::VarString & dbName, const basar::Int32 documentDate);
	static const basar::VarString getSelectByGuidSQL(const basar::VarString & dbName);
	static const basar::VarString getInsertSQL( const basar::VarString & dbName );
	static const basar::VarString getUpdateSQL( const basar::VarString & dbName , const DocumentArchiveInfoPtr documentArchiveInfo );

	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, const basar::VarString& documentNo, const basar::Int32 documentDate);
	static const libcsc::persistence::ISqlParameterBinderPtr getSelectByGuidSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentGuid);
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder(const DocumentArchiveInfoPtr documentArchiveInfo);

	static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, const basar::VarString& documentNo, basar::Int32 doumentDate);
	static void bindSelectByGuidSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentGuid);
	static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const DocumentArchiveInfoPtr documentArchiveInfo);

protected:
	virtual void doMap();

private:
	DocumentArchiveInfoSQLMapper(const DocumentArchiveInfoSQLMapper&);
	DocumentArchiveInfoSQLMapper & operator=(const DocumentArchiveInfoSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOSQLMAPPER_H
