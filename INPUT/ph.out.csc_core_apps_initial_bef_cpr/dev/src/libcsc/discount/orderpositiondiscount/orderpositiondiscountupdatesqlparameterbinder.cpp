#include "orderpositiondiscountupdatesqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountUpdateSqlParameterBinder::OrderPositionDiscountUpdateSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount )
: m_PositionDiscount( positionDiscount )
{
}

OrderPositionDiscountUpdateSqlParameterBinder::~OrderPositionDiscountUpdateSqlParameterBinder()
{
}

void OrderPositionDiscountUpdateSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindUpdateSQL( preparedStatement, m_PositionDiscount );
}

} // end namespace discount
} // end namespace libcsc

