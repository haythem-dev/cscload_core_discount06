#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_INSERT_SQL_PARAMETER_BINDER_H

#include "documentprintinfoptr.h"
#include <persistence/isqlparameterbinder.h>

namespace libcsc {
namespace document {

class DocumentPrintInfoInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DocumentPrintInfoInsertSqlParameterBinder(const DocumentPrintInfoPtr documentPrintInfo);
	virtual ~DocumentPrintInfoInsertSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	DocumentPrintInfoPtr m_DocumentPrintInfo;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_INSERT_SQL_PARAMETER_BINDER_H
