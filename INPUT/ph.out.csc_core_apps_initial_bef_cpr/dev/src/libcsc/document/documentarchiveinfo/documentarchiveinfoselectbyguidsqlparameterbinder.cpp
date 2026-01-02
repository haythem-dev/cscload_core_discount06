#include "documentarchiveinfoselectbyguidsqlparameterbinder.h"
#include "documentarchiveinfosqlmapper.h"

namespace libcsc {
namespace document {

DocumentArchiveInfoSelectByGuidSqlParameterBinder::DocumentArchiveInfoSelectByGuidSqlParameterBinder (const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString & documentId):
	m_BranchNo(branchNo), m_CustomerNo(customerNo), m_DocumentId(documentId)
{
}

DocumentArchiveInfoSelectByGuidSqlParameterBinder::~DocumentArchiveInfoSelectByGuidSqlParameterBinder()
{
}

void DocumentArchiveInfoSelectByGuidSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DocumentArchiveInfoSQLMapper::bindSelectByGuidSQL(preparedStatement, m_BranchNo, m_CustomerNo, m_DocumentId);
}

} // end namespace document
} // end namespace libcsc
