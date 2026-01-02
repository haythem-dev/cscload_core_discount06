#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_SELECT_SQL_PARAMETER_BINDER_H

#include "documentprintinfoptr.h"
#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>
#include <types/documenttypeenum.inc>

namespace libcsc {
namespace document {

class DocumentPrintInfoSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DocumentPrintInfoSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType,
		const basar::Int32 documentDate, const basar::VarString & documentNo);

	virtual ~DocumentPrintInfoSelectSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	basar::Int16		m_BranchNo;
	basar::Int32		m_CustomerNo;
	DocumentTypeEnum	m_DocumentType;
	basar::Int32		m_DocumentDate;
	basar::VarString	m_DocumentNo;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_SELECT_SQL_PARAMETER_BINDER_H

