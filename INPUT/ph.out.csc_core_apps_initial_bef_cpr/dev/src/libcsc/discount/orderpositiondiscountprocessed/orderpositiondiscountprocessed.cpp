#include "orderpositiondiscountprocessed.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessed::OrderPositionDiscountProcessed()
{
}

const libcsc::Int32 & OrderPositionDiscountProcessed::getOrderNo() const
{
	return m_OrderNo;
}

const libcsc::Int32 & OrderPositionDiscountProcessed::getPositionNo() const
{
	return m_PositionNo;
}

const libcsc::DateTime & OrderPositionDiscountProcessed::getProcessingTime() const
{
	return m_ProcessingTime;
}

void OrderPositionDiscountProcessed::setOrderNo( const libcsc::Int32 & orderNo )
{
	m_OrderNo = orderNo;
}

void OrderPositionDiscountProcessed::setPositionNo( const libcsc::Int32 & positionNo )
{
	m_PositionNo = positionNo;
}

void OrderPositionDiscountProcessed::setProcessingTime( const libcsc::DateTime & processingTime )
{
	m_ProcessingTime = processingTime;
}

} // end namespace discount
} // end namespace libcsc

