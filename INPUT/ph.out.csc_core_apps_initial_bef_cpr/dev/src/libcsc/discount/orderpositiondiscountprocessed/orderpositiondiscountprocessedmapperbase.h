#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_MAPPER_BASE_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_MAPPER_BASE_H

#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedMapperBase
{
public:
	OrderPositionDiscountProcessedMapperBase( OrderPositionDiscountProcessedPtr positionDiscountProcessed );

	void map();

protected:
	virtual ~OrderPositionDiscountProcessedMapperBase();

	virtual void doMap() = 0;

	void setOrderNo( const basar::Int32 orderNo );
	void setPositionNo( const basar::Int32 positionNo );
	void setProcessingTime( const basar::DateTime & processingTime );

private:
	OrderPositionDiscountProcessedPtr	m_PositionDiscountProcessed;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_MAPPER_BASE_H
