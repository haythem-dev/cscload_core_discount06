#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>
#include "transmissionresponseptr.h"

namespace libcsc {
namespace msv3 {

	class TransmissionResponseSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	TransmissionResponseSelectSqlParameterBinder(const basar::VarString& transmissionUuid);
	virtual ~TransmissionResponseSelectSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	basar::VarString	m_TransmissionUuid;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_SELECT_SQL_PARAMETER_BINDER_H
