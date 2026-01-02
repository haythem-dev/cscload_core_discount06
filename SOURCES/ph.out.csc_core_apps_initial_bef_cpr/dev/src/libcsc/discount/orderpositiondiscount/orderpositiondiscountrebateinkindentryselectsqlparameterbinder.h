#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REBATEINKIND_ENTRY_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REBATEINKIND_ENTRY_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder( const basar::Int32 rebatinkindorderNo, const basar::Int32 rebateinkindpositionNo );
	virtual ~OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder();

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

private:
	basar::Int32	m_RebateInKindOrderNo;
	basar::Int32	m_RebateInKindPositionNo;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REBATEINKIND_ENTRY_SELECT_SQL_PARAMETER_BINDER_H



