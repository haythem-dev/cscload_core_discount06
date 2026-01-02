#include "orderpositiondiscountprocessedinsertsqlparameterbinder.h"
#include "orderpositiondiscountprocessedsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessedInsertSqlParameterBinder::OrderPositionDiscountProcessedInsertSqlParameterBinder( const OrderPositionDiscountProcessedPtr positionDiscountProcessed )
: m_PositionDiscountProcessed( positionDiscountProcessed )
{
}

OrderPositionDiscountProcessedInsertSqlParameterBinder::~OrderPositionDiscountProcessedInsertSqlParameterBinder()
{
}

void OrderPositionDiscountProcessedInsertSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountProcessedSQLMapper::bindInsertSQL( preparedStatement, m_PositionDiscountProcessed );
}

} // end namespace discount
} // end namespace libcsc

