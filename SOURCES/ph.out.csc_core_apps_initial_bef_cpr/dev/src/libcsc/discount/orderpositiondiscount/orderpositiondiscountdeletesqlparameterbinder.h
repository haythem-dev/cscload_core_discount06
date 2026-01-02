#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_DELETE_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_DELETE_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscountptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountDeleteSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountDeleteSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	virtual ~OrderPositionDiscountDeleteSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	OrderPositionDiscountPtr	m_PositionDiscount;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_DELETE_SQL_PARAMETER_BINDER_H



