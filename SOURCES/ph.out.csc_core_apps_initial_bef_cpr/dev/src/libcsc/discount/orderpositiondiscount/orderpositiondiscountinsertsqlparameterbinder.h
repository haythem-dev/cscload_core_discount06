#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscountptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountInsertSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	virtual ~OrderPositionDiscountInsertSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	OrderPositionDiscountPtr	m_PositionDiscount;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_INSERT_SQL_PARAMETER_BINDER_H



