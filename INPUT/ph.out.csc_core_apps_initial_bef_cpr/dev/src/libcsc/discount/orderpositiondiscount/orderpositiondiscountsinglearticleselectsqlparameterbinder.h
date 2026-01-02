#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SINGLE_ARTICLE_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SINGLE_ARTICLE_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountSingleArticleSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountSingleArticleSelectSqlParameterBinder( const basar::Int32 orderNo, const basar::Int32 positionNo );
	virtual ~OrderPositionDiscountSingleArticleSelectSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	basar::Int32	m_OrderNo;
	basar::Int32	m_PositionNo;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_SINGLE_ARTICLE_SELECT_SQL_PARAMETER_BINDER_H



