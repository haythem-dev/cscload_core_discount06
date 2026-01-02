#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSE_UPDATE_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSE_UPDATE_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include "orderresponseptr.h"

namespace libcsc {
namespace msv3 {

	class OrderResponseUpdateSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderResponseUpdateSqlParameterBinder(const OrderResponsePtr orderResponse);
	virtual ~OrderResponseUpdateSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	OrderResponsePtr	m_OrderResponse;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSE_UPDATE_SQL_PARAMETER_BINDER_H
