#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_ORDER_COMPLETION_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_ORDER_COMPLETION_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountOrderCompletionSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountOrderCompletionSelectSqlParameterBinder( const basar::Int32 orderNo );
	virtual ~OrderPositionDiscountOrderCompletionSelectSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	basar::Int32	m_OrderNo;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_ORDER_COMPLETION_SELECT_SQL_PARAMETER_BINDER_H



