#include "orderpositiondiscountrebateinkindentryselectsqlparameterbinder.h"
#include "orderpositiondiscountsqlmapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder::OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder( const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo )
: m_RebateInKindOrderNo( rebateinkindorderNo ),
  m_RebateInKindPositionNo( rebateinkindpositionNo )
{
}

OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder::~OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder()
{
}

void OrderPositionDiscountRebateInKindEntrySelectSQLParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	OrderPositionDiscountSQLMapper::bindRebateInKindEntrySelectSQL( preparedStatement, m_RebateInKindOrderNo, m_RebateInKindPositionNo );
}

} // end namespace discount
} // end namespace libcsc

