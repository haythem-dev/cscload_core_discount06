#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSE_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSE_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include "orderresponseptr.h"

namespace libcsc {
namespace msv3 {

	class OrderResponseInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderResponseInsertSqlParameterBinder(const OrderResponsePtr orderResponse);
	virtual ~OrderResponseInsertSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	OrderResponsePtr	m_OrderResponse;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSE_INSERT_SQL_PARAMETER_BINDER_H
