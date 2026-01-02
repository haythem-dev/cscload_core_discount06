#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSE_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSE_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace msv3 {

	class OrderResponseSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderResponseSelectSqlParameterBinder(const basar::VarString& transmissionUuid);
	virtual ~OrderResponseSelectSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	basar::VarString	m_OrderUuid;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSE_SELECT_SQL_PARAMETER_BINDER_H
