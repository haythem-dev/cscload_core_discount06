#include "orderpositiondiscountsinglearticleselectsqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountSingleArticleSelectSqlParameterBinder::OrderPositionDiscountSingleArticleSelectSqlParameterBinder( const basar::Int32 orderNo, const basar::Int32 positionNo )
: m_OrderNo( orderNo ),
  m_PositionNo( positionNo )
{
}

OrderPositionDiscountSingleArticleSelectSqlParameterBinder::~OrderPositionDiscountSingleArticleSelectSqlParameterBinder()
{
}

void OrderPositionDiscountSingleArticleSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindSingleArticleSelectSQL( preparedStatement, m_OrderNo, m_PositionNo );
}

} // end namespace discount
} // end namespace libcsc

