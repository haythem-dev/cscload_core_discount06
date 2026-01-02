#include "documentprintinfoinsertsqlparameterbinder.h"
#include "documentprintinfosqlmapper.h"

namespace libcsc {
namespace document {

DocumentPrintInfoInsertSqlParameterBinder::DocumentPrintInfoInsertSqlParameterBinder(const DocumentPrintInfoPtr documentPrintInfo) :
	m_DocumentPrintInfo(documentPrintInfo)
{
}

DocumentPrintInfoInsertSqlParameterBinder::~DocumentPrintInfoInsertSqlParameterBinder()
{
}

void DocumentPrintInfoInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DocumentPrintInfoSQLMapper::bindInsertSQL(preparedStatement, m_DocumentPrintInfo);
}

} // end namespace document
} // end namespace libcsc

