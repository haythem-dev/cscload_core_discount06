#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include "transmissionresponseptr.h"

namespace libcsc {
namespace msv3 {

	class TransmissionResponseInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	TransmissionResponseInsertSqlParameterBinder(const TransmissionResponsePtr transmissionResponse);
	virtual ~TransmissionResponseInsertSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	TransmissionResponsePtr	m_TransmissionResponse;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_INSERT_SQL_PARAMETER_BINDER_H
