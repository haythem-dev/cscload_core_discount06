#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountProcessedSelectSqlParameterBinder( const basar::Int32 orderNo );
	virtual ~OrderPositionDiscountProcessedSelectSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	basar::Int32	m_OrderNo;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_SELECT_SQL_PARAMETER_BINDER_H



