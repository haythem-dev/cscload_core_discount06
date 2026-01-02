#include "orderpositiondiscountinsertsqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountInsertSqlParameterBinder::OrderPositionDiscountInsertSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
: m_PositionDiscount( positionDiscount )
{
}

OrderPositionDiscountInsertSqlParameterBinder::~OrderPositionDiscountInsertSqlParameterBinder()
{
}

void OrderPositionDiscountInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindInsertSQL( preparedStatement, m_PositionDiscount );
}

} // end namespace discount
} // end namespace libcsc

