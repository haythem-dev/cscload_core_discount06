#include "documentprintinfoselectsqlparameterbinder.h"
#include "documentprintinfosqlmapper.h"

namespace libcsc {
namespace document {

DocumentPrintInfoSelectSqlParameterBinder::DocumentPrintInfoSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType,
	const basar::Int32 documentDate, const basar::VarString & documentNo):
	m_BranchNo(branchNo), m_CustomerNo(customerNo), m_DocumentType(documentType), m_DocumentDate(documentDate), m_DocumentNo(documentNo)
{
}

DocumentPrintInfoSelectSqlParameterBinder::~DocumentPrintInfoSelectSqlParameterBinder()
{
}

void DocumentPrintInfoSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	DocumentPrintInfoSQLMapper::bindSelectSQL(preparedStatement, m_BranchNo, m_CustomerNo, m_DocumentType, m_DocumentDate, m_DocumentNo);
}

} // end namespace document
} // end namespace libcsc
