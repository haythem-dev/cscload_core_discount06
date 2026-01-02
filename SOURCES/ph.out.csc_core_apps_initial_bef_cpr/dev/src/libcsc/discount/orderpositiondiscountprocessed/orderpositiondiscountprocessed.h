#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_H

#include <datatypes/datetime.h>
#include <datatypes/int32.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessed
{
	// because of OR mapping
	friend class OrderPositionDiscountProcessedMapperBase;

public:
	OrderPositionDiscountProcessed();

	const libcsc::Int32 & getOrderNo() const;
	const libcsc::Int32 & getPositionNo() const;
	const libcsc::DateTime & getProcessingTime() const;

	void setOrderNo( const libcsc::Int32 & orderNo );
	void setPositionNo( const libcsc::Int32 & positionNo );
	void setProcessingTime( const libcsc::DateTime & processingTime );

private:
	libcsc::Int32		m_OrderNo;
	libcsc::Int32		m_PositionNo;
	libcsc::DateTime	m_ProcessingTime;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_H
