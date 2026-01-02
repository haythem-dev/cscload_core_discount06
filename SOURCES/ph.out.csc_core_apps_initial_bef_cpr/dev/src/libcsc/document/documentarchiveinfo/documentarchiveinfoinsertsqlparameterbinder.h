#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include "documentarchiveinfoptr.h"

namespace libcsc {
namespace document {

class DocumentArchiveInfoInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DocumentArchiveInfoInsertSqlParameterBinder(const DocumentArchiveInfoPtr documentArchiveInfo);
	virtual ~DocumentArchiveInfoInsertSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	DocumentArchiveInfoPtr	m_DocumentArchiveInfo;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_INSERT_SQL_PARAMETER_BINDER_H
