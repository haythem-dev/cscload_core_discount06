#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>
#include <types/documenttypeenum.inc>

namespace libcsc {
namespace document {

class DocumentArchiveInfoSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DocumentArchiveInfoSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, const basar::VarString & documentNo, const basar::Int32 documentDate );

	virtual ~DocumentArchiveInfoSelectSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:

	basar::Int16		m_BranchNo;
	basar::Int32		m_CustomerNo;
	DocumentTypeEnum	m_DocumentType;
	basar::VarString	m_DocumentNo;
	basar::Int32		m_DocumentDate;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_SQL_PARAMETER_BINDER_H

