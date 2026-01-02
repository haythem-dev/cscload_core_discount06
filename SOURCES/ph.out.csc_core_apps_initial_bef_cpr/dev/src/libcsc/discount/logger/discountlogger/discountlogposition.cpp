#include "discountlogposition.h"

namespace libcsc
{
namespace discount
{
DiscountLogPosition::DiscountLogPosition()
: m_DiscountCalculatorType( CT_UNSET )
{
}

const libcsc::Int32 & DiscountLogPosition::getOrderNo() const
{
	return m_OrderNo;
}

const libcsc::Int32 & DiscountLogPosition::getPositionNo() const
{
	return m_PositionNo;
}

const DiscountCalculatorType & DiscountLogPosition::getDiscountCalculatorType() const
{
	return m_DiscountCalculatorType;
}

const libcsc::Decimal & DiscountLogPosition::getDiscountValue() const
{
	return m_DiscountValue;
}

const libcsc::Decimal & DiscountLogPosition::getDiscountPercent() const
{
	return m_DiscountPercent;
}

const libcsc::Int32 & DiscountLogPosition::getDiscountQty() const
{
	return m_DiscountQty;
}

const libcsc::Int32 & DiscountLogPosition::getRebateInKindPosNo() const
{
	return m_RebateInKindPosNo;
}

void DiscountLogPosition::setOrderNo( const libcsc::Int32 & orderNo )
{
	m_OrderNo = orderNo;
}

void DiscountLogPosition::setPositionNo( const libcsc::Int32 & positionNo )
{
	m_PositionNo = positionNo;
}

void DiscountLogPosition::setDiscountCalculatorType( const DiscountCalculatorType & discountCalculatorType )
{
	m_DiscountCalculatorType = discountCalculatorType;
}

void DiscountLogPosition::setDiscountValue( const libcsc::Decimal & discountValue )
{
	m_DiscountValue = discountValue;
}

void DiscountLogPosition::setDiscountPercent( const libcsc::Decimal & discountPercent )
{
	m_DiscountPercent = discountPercent;
}

void DiscountLogPosition::setDiscountQty( const libcsc::Int32 & discountQty )
{
	m_DiscountQty = discountQty;
}

void DiscountLogPosition::setRebateInKindPosNo( const libcsc::Int32 & rebateInKindPosNo )
{
	m_RebateInKindPosNo = rebateInKindPosNo;
}


} // end namespace discount
} // end namespace libcsc

