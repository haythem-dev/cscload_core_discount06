#include "orderresponseselectsqlparameterbinder.h"
#include "orderresponsesqlmapper.h"

namespace libcsc {
namespace msv3 {

OrderResponseSelectSqlParameterBinder::OrderResponseSelectSqlParameterBinder(const basar::VarString& orderUuid) :
	m_OrderUuid(orderUuid)
{
}

OrderResponseSelectSqlParameterBinder::~OrderResponseSelectSqlParameterBinder()
{
}

void OrderResponseSelectSqlParameterBinder::bind(basar::db::sql::PreparedStatementRef preparedStatement) const
{
	OrderResponseSQLMapper::bindSelectSQL(preparedStatement, m_OrderUuid);
}

} // end namespace msv3
} // end namespace libcsc
