#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_BY_INTERNALHASH_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_BY_INTERNALHASH_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_datetime.h>
#include "transmissionresponseptr.h"

namespace libcsc {
namespace msv3 {

	class TransmissionResponseSelectByInternalHashSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	TransmissionResponseSelectByInternalHashSqlParameterBinder(
		const basar::Int16& branchNo,
		const basar::Int32& customerNo,
		const basar::VarString& internalHash,
		const basar::DateTime& checkFrom);
	virtual ~TransmissionResponseSelectByInternalHashSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	basar::Int16		m_BranchNo;
	basar::Int32		m_CustomerNo;
	basar::VarString	m_InternalHash;
	basar::DateTime		m_CheckFrom;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_BY_INTERNALHASH_SQL_PARAMETER_BINDER_H
