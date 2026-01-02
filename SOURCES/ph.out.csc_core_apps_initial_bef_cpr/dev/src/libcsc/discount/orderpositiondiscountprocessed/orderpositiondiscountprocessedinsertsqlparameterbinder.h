#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_INSERT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_INSERT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedInsertSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountProcessedInsertSqlParameterBinder( const OrderPositionDiscountProcessedPtr positionDiscountProcessed );
	virtual ~OrderPositionDiscountProcessedInsertSqlParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	OrderPositionDiscountProcessedPtr	m_PositionDiscountProcessed;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_INSERT_SQL_PARAMETER_BINDER_H



