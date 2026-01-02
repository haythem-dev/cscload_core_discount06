#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SINGLE_ARTICLE_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SINGLE_ARTICLE_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueSingleArticleSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	DiscountBaseValueSingleArticleSqlParameterBinder( const IOrderBaseValueGetterPtr orderBaseValue );
	virtual ~DiscountBaseValueSingleArticleSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	IOrderBaseValueGetterPtr	m_OrderBaseValue;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_SINGLE_ARTICLE_SQL_PARAMETER_BINDER_H



