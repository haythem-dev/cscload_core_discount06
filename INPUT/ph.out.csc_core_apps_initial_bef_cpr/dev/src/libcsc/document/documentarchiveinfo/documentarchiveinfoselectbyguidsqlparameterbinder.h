#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_BY_GUID_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_BY_GUID_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace document {

class DocumentArchiveInfoSelectByGuidSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DocumentArchiveInfoSelectByGuidSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString & documentId);

	virtual ~DocumentArchiveInfoSelectByGuidSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:

	basar::Int16		m_BranchNo;
	basar::Int32		m_CustomerNo;
	basar::VarString	m_DocumentId;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_SELECT_BY_GUID_SQL_PARAMETER_BINDER_H

