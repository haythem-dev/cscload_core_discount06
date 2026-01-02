#include "documentarchiveinfoinsertsqlparameterbinder.h"
#include "documentarchiveinfosqlmapper.h"

namespace libcsc {
namespace document {

DocumentArchiveInfoInsertSqlParameterBinder::DocumentArchiveInfoInsertSqlParameterBinder(const DocumentArchiveInfoPtr documentArchiveInfo) :
	m_DocumentArchiveInfo(documentArchiveInfo)
{
}

DocumentArchiveInfoInsertSqlParameterBinder::~DocumentArchiveInfoInsertSqlParameterBinder()
{
}

void DocumentArchiveInfoInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DocumentArchiveInfoSQLMapper::bindInsertSQL(preparedStatement, m_DocumentArchiveInfo);
}

} // end namespace document
} // end namespace libcsc

