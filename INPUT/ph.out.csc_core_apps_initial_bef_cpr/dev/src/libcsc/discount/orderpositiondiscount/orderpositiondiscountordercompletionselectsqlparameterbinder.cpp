#include "orderpositiondiscountordercompletionselectsqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountOrderCompletionSelectSqlParameterBinder::OrderPositionDiscountOrderCompletionSelectSqlParameterBinder( const basar::Int32 orderNo )
: m_OrderNo( orderNo )
{
}

OrderPositionDiscountOrderCompletionSelectSqlParameterBinder::~OrderPositionDiscountOrderCompletionSelectSqlParameterBinder()
{
}

void OrderPositionDiscountOrderCompletionSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindOrderCompletionSelectSQL( preparedStatement, m_OrderNo );
}

} // end namespace discount
} // end namespace libcsc

