#include "orderresponseupdatesqlparameterbinder.h"
#include "orderresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

OrderResponseUpdateSqlParameterBinder::OrderResponseUpdateSqlParameterBinder(const OrderResponsePtr orderResponse) :
	m_OrderResponse(orderResponse)
{
}

OrderResponseUpdateSqlParameterBinder::~OrderResponseUpdateSqlParameterBinder()
{
}

void OrderResponseUpdateSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	OrderResponseSQLMapper::bindUpdateSQL(preparedStatement, m_OrderResponse);
}

} // end namespace msv3
} // end namespace libcsc

