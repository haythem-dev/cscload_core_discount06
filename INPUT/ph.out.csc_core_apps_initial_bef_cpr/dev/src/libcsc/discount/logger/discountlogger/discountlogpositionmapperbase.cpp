#include "discountlogpositionmapperbase.h"
#include "discountlogposition.h"

namespace libcsc
{
namespace discount
{
DiscountLogPositionMapperBase::DiscountLogPositionMapperBase( DiscountLogPositionPtr discountLogPosition )
: m_DiscountLogPosition( discountLogPosition )
{
}

DiscountLogPositionMapperBase::~DiscountLogPositionMapperBase()
{
}

void DiscountLogPositionMapperBase::map()
{
	doMap();
}

void DiscountLogPositionMapperBase::setOrderNo( const basar::Int32 orderNo )
{
	m_DiscountLogPosition->m_OrderNo = orderNo;
	m_DiscountLogPosition->m_OrderNo.setClean();
}

void DiscountLogPositionMapperBase::setPositionNo( const basar::Int32 positionNo )
{
	m_DiscountLogPosition->m_PositionNo = positionNo;
	m_DiscountLogPosition->m_PositionNo.setClean();
}

void DiscountLogPositionMapperBase::setDiscountCalculatorType( const DiscountCalculatorTypeEnum discountCalculatorType )
{
	m_DiscountLogPosition->m_DiscountCalculatorType = discountCalculatorType;
	m_DiscountLogPosition->m_DiscountCalculatorType.setClean();
}

void DiscountLogPositionMapperBase::setDiscountValue( const basar::Decimal & discountValue )
{
	m_DiscountLogPosition->m_DiscountValue = discountValue;
	m_DiscountLogPosition->m_DiscountValue.setClean();
}

void DiscountLogPositionMapperBase::setDiscountPercent( const basar::Decimal & discountPercent )
{
	m_DiscountLogPosition->m_DiscountPercent = discountPercent;
	m_DiscountLogPosition->m_DiscountPercent.setClean();
}

void DiscountLogPositionMapperBase::setDiscountQty( const basar::Int32 discountQty )
{
	m_DiscountLogPosition->m_DiscountQty = discountQty;
	m_DiscountLogPosition->m_DiscountQty.setClean();
}

} // end namespace discount
} // end namespace libcsc

