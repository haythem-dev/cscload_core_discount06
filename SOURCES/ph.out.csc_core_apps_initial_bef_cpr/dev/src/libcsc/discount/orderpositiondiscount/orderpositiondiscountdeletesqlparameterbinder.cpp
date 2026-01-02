#include "orderpositiondiscountdeletesqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountDeleteSqlParameterBinder::OrderPositionDiscountDeleteSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
: m_PositionDiscount( positionDiscount )
{
}

OrderPositionDiscountDeleteSqlParameterBinder::~OrderPositionDiscountDeleteSqlParameterBinder()
{
}

void OrderPositionDiscountDeleteSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindDeleteSQL( preparedStatement, m_PositionDiscount );
}

} // end namespace discount
} // end namespace libcsc

