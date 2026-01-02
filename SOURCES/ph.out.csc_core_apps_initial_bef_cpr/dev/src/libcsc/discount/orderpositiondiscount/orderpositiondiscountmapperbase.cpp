#include "orderpositiondiscountmapperbase.h"
#include "orderpositiondiscount.h"
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscountMapperBase::OrderPositionDiscountMapperBase( OrderPositionDiscountPtr positionDiscount )
: m_PositionDiscount( positionDiscount )
{
}

OrderPositionDiscountMapperBase::~OrderPositionDiscountMapperBase()
{
}

void OrderPositionDiscountMapperBase::map()
{
	doMap();

	std::stringstream ss;
	ss << "OrderPositionDiscountMapperBase::map(), m_PositionDiscount:" << *m_PositionDiscount << std::endl;
	BLOG_TRACE( LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str() );
}

void OrderPositionDiscountMapperBase::setOrderNo( const basar::Int32 orderNo )
{
	m_PositionDiscount->m_OrderNo = orderNo;
	m_PositionDiscount->m_OrderNo.setClean();
}

void OrderPositionDiscountMapperBase::setPositionNo( const basar::Int32 positionNo )
{
	m_PositionDiscount->m_PositionNo = positionNo;
	m_PositionDiscount->m_PositionNo.setClean();
}

void OrderPositionDiscountMapperBase::setDiscountMode( const OrderPositionDiscountMode discountMode )
{
	m_PositionDiscount->m_DiscountMode = discountMode;
	m_PositionDiscount->m_DiscountMode.setClean();
}

void OrderPositionDiscountMapperBase::setDiscountValue( const basar::Decimal discountValue )
{
	m_PositionDiscount->m_DiscountValue = discountValue;
	m_PositionDiscount->m_DiscountValue.setClean();
}

void OrderPositionDiscountMapperBase::setDiscountPercent( const basar::Decimal discountPercent )
{
	m_PositionDiscount->m_DiscountPercent = discountPercent;
	m_PositionDiscount->m_DiscountPercent.setClean();
}

void OrderPositionDiscountMapperBase::setDiscountQty( const basar::Int16 discountQty )
{
	m_PositionDiscount->m_DiscountQty = discountQty;
	m_PositionDiscount->m_DiscountQty.setClean();
}

void OrderPositionDiscountMapperBase::setRebateInKindPositionNo( const basar::Int32 rebateInKindPositionNo )
{
	m_PositionDiscount->m_RebateInKindPositionNo = rebateInKindPositionNo;
	m_PositionDiscount->m_RebateInKindPositionNo.setClean();
}

void OrderPositionDiscountMapperBase::setRebateInKindOrderNo(const basar::Int32 rebateInKindOrderNo)
{
	m_PositionDiscount->m_RebateInKindOrderNo = rebateInKindOrderNo;
	m_PositionDiscount->m_RebateInKindOrderNo.setClean();
}

void OrderPositionDiscountMapperBase::setPharmacyGroupId(const basar::VarString pharmacyGroup)
{
	m_PositionDiscount->m_PharmacyGroupId = pharmacyGroup;
	m_PositionDiscount->m_PharmacyGroupId.setClean();
}


} // end namespace discount
} // end namespace libcsc

