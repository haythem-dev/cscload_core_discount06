#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_UPDATE_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_UPDATE_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscountptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountUpdateSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountUpdateSqlParameterBinder( const OrderPositionDiscountPtr positionDiscount );
	virtual ~OrderPositionDiscountUpdateSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	OrderPositionDiscountPtr	m_PositionDiscount;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_UPDATE_SQL_PARAMETER_BINDER_H



