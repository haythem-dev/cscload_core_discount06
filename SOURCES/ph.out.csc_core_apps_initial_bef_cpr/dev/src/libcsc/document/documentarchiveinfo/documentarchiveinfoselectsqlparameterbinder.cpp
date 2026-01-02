#include "documentarchiveinfoselectsqlparameterbinder.h"
#include "documentarchiveinfosqlmapper.h"

namespace libcsc {
namespace document {

DocumentArchiveInfoSelectSqlParameterBinder::DocumentArchiveInfoSelectSqlParameterBinder (const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType, const basar::VarString & documentNo, const basar::Int32 documentDate ):
	m_BranchNo(branchNo), m_CustomerNo(customerNo), m_DocumentType(documentType), m_DocumentNo(documentNo), m_DocumentDate( documentDate )
{
}

DocumentArchiveInfoSelectSqlParameterBinder::~DocumentArchiveInfoSelectSqlParameterBinder()
{
}

void DocumentArchiveInfoSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DocumentArchiveInfoSQLMapper::bindSelectSQL(preparedStatement, m_BranchNo, m_CustomerNo, m_DocumentType, m_DocumentNo, m_DocumentDate );
}

} // end namespace document
} // end namespace libcsc
