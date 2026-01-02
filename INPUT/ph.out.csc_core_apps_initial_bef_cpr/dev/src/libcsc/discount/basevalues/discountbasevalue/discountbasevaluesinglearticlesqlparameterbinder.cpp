#include "discountbasevaluesinglearticlesqlparameterbinder.h"
#include "discountbasevaluesqlmapper.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace discount
{
DiscountBaseValueSingleArticleSqlParameterBinder::DiscountBaseValueSingleArticleSqlParameterBinder( const IOrderBaseValueGetterPtr orderBaseValue )
: m_OrderBaseValue( orderBaseValue )
{
}

DiscountBaseValueSingleArticleSqlParameterBinder::~DiscountBaseValueSingleArticleSqlParameterBinder()
{
}

void DiscountBaseValueSingleArticleSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueSingleArticleSqlParameterBinder::bind()" );

	DiscountBaseValueSQLMapper::bindSingleArticleSelectSQL( preparedStatement, m_OrderBaseValue );
}

} // end namespace discount
} // end namespace libcsc

