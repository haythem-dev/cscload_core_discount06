#include "orderpositiondiscountprocessedmapperbase.h"
#include "orderpositiondiscountprocessed.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountProcessedMapperBase::OrderPositionDiscountProcessedMapperBase( OrderPositionDiscountProcessedPtr positionDiscountProcessed )
: m_PositionDiscountProcessed( positionDiscountProcessed )
{
}

OrderPositionDiscountProcessedMapperBase::~OrderPositionDiscountProcessedMapperBase()
{
}

void OrderPositionDiscountProcessedMapperBase::map()
{
	doMap();
}

void OrderPositionDiscountProcessedMapperBase::setOrderNo( const basar::Int32 orderNo )
{
	m_PositionDiscountProcessed->m_OrderNo = orderNo;
	m_PositionDiscountProcessed->m_OrderNo.setClean();
}

void OrderPositionDiscountProcessedMapperBase::setPositionNo( const basar::Int32 positionNo )
{
	m_PositionDiscountProcessed->m_PositionNo = positionNo;
	m_PositionDiscountProcessed->m_PositionNo.setClean();
}

void OrderPositionDiscountProcessedMapperBase::setProcessingTime( const basar::DateTime & processingTime )
{
	m_PositionDiscountProcessed->m_ProcessingTime = processingTime;
	m_PositionDiscountProcessed->m_ProcessingTime.setClean();
}

} // end namespace discount
} // end namespace libcsc

