#include "orderpositiondiscountprocessedselectsqlparameterbinder.h"
#include "orderpositiondiscountprocessedsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessedSelectSqlParameterBinder::OrderPositionDiscountProcessedSelectSqlParameterBinder( const basar::Int32 orderNo )
: m_OrderNo( orderNo )
{
}

OrderPositionDiscountProcessedSelectSqlParameterBinder::~OrderPositionDiscountProcessedSelectSqlParameterBinder()
{
}

void OrderPositionDiscountProcessedSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountProcessedSQLMapper::bindSelectSQL( preparedStatement, m_OrderNo );
}

} // end namespace discount
} // end namespace libcsc

