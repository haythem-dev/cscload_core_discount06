#include "orderresponseinsertsqlparameterbinder.h"
#include "orderresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

OrderResponseInsertSqlParameterBinder::OrderResponseInsertSqlParameterBinder(const OrderResponsePtr orderResponse) :
	m_OrderResponse(orderResponse)
{
}

OrderResponseInsertSqlParameterBinder::~OrderResponseInsertSqlParameterBinder()
{
}

void OrderResponseInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderResponseSQLMapper::bindInsertSQL(preparedStatement, m_OrderResponse);
}

} // end namespace msv3
} // end namespace libcsc

