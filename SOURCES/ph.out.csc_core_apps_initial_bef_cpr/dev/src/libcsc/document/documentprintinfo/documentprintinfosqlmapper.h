#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOSQLMAPPER_H

#include "documentprintinfomapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasarcmnutil_bstring.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc {
namespace document {

class DocumentPrintInfoSQLMapper : public DocumentPrintInfoMapperBase
{
public:
	DocumentPrintInfoSQLMapper(DocumentPrintInfoPtr documentPrintInfo, const basar::db::sql::ResultsetRef resultSet);
	DocumentPrintInfoSQLMapper(DocumentPrintInfoPtr documentPrintInfo);
	virtual ~DocumentPrintInfoSQLMapper();

	static const basar::VarString getInsertSQL( const basar::VarString & dbName );
	static const libcsc::persistence::ISqlParameterBinderPtr getInsertSqlParameterBinder(const DocumentPrintInfoPtr documentPrintInfo);
	static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const DocumentPrintInfoPtr documentPrintInfo);

	static const basar::VarString getSelectSQL(const basar::VarString & dbName);
	static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType,
		const basar::Int32 documentDate, const basar::VarString & documentNo);
	static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, basar::Int32 documentDate, const basar::VarString & documentNo);

protected:
	virtual void doMap();

private:
	DocumentPrintInfoSQLMapper(const DocumentPrintInfoSQLMapper&);
	DocumentPrintInfoSQLMapper & operator=(const DocumentPrintInfoSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOSQLMAPPER_H
