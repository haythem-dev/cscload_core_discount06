#include "orderpositiondiscount.h"
#include "orderpositiondiscountmodemapper.h"

namespace libcsc
{
namespace discount
{
OrderPositionDiscount::OrderPositionDiscount()
: m_DiscountMode( DM_UNSET )
{
}

OrderPositionDiscount::~OrderPositionDiscount()
{
}


const libcsc::Int32 & OrderPositionDiscount::getOrderNo() const
{
	return m_OrderNo;
}

const libcsc::Int32 & OrderPositionDiscount::getPositionNo() const
{
	return m_PositionNo;
}

const OrderPositionDiscountMode & OrderPositionDiscount::getDiscountMode() const
{
	return m_DiscountMode;
}

const libcsc::Decimal & OrderPositionDiscount::getDiscountValue() const
{
	return m_DiscountValue;
}

const libcsc::Decimal & OrderPositionDiscount::getDiscountPercent() const
{
	return m_DiscountPercent;
}

const libcsc::Int32 & OrderPositionDiscount::getDiscountQty() const
{
	return m_DiscountQty;
}

const libcsc::Int32 & OrderPositionDiscount::getRebateInKindPositionNo() const
{
	return m_RebateInKindPositionNo;
}

const libcsc::Int32 & OrderPositionDiscount::getRebateInKindOrderNo() const
{
	return m_RebateInKindOrderNo;
}

const libcsc::VarString& OrderPositionDiscount::getPharmacyGroupId() const
{
	return m_PharmacyGroupId;
}

void OrderPositionDiscount::setOrderNo( const libcsc::Int32 & orderNo )
{
	m_OrderNo = orderNo;
}

void OrderPositionDiscount::setPositionNo( const libcsc::Int32 & positionNo )
{
	m_PositionNo = positionNo;
}

void OrderPositionDiscount::setDiscountMode( const OrderPositionDiscountMode & discountMode )
{
	m_DiscountMode = discountMode;
}

void OrderPositionDiscount::setDiscountValue( const libcsc::Decimal & discountValue )
{
	m_DiscountValue = discountValue;
}

void OrderPositionDiscount::setDiscountPercent( const libcsc::Decimal & discountPercent )
{
	m_DiscountPercent = discountPercent;
}

void OrderPositionDiscount::setDiscountQty( const libcsc::Int32 & discountQty )
{
	m_DiscountQty = discountQty;
}

void OrderPositionDiscount::setRebateInKindPositionNo( const libcsc::Int32 & rebateInKindPositionNo )
{
	m_RebateInKindPositionNo = rebateInKindPositionNo;
}

void OrderPositionDiscount::setRebateInKindOrderNo(const libcsc::Int32 & rebateInKindOrderNo)
{
	m_RebateInKindOrderNo = rebateInKindOrderNo;
}

void OrderPositionDiscount::setPharmacyGroupId(const libcsc::VarString& pharmacyGroup)
{
	m_PharmacyGroupId = pharmacyGroup;
}

bool OrderPositionDiscount::isDiscountValid() const
{
	// if this property is unset, OrderPositionDiscountRepository::getOrderPositionDiscount delivered just an empty / default OrderPositionDiscount
	// this must be overwritten by any calculated discount result, even if discountvalue is worse (e.g. fixed price > item price --> discountvalue < 0)
	return !m_OrderNo.isUnset();  // --> can´t be used in addition, as setArticleNo is not called by OrderPositionDiscountSQLMapper::doMap
}

bool OrderPositionDiscount::isRebateInKind() const
{
	return getDiscountMode().get() == libcsc::discount::DM_WHOLESALE_REBATE_IN_KIND_MODE
		|| getDiscountMode().get() == libcsc::discount::DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE;
}

bool OrderPositionDiscount::isRebateInKindExtraPosition() const
{
	return isRebateInKind() && getRebateInKindPositionNo() > 0 && getRebateInKindPositionNo() != getPositionNo();
}

bool OrderPositionDiscount::isDiscountFixedPrice() const
{
	return getDiscountMode().get() == libcsc::discount::DM_FIXED_PRICE_MODE
		|| getDiscountMode().get() == libcsc::discount::DM_FIXED_PRICE_CONCEPT_DEAP_MODE; // not MVDA_MODE!
}

bool OrderPositionDiscount::isDiscountValuePercent() const
{
	return getDiscountPercent().get() > basar::Decimal(0.0) &&
		getDiscountMode().get() != libcsc::discount::DM_SURCHARGE_EXF_MODE;
}

std::ostream & OrderPositionDiscount::toStream( std::ostream & strm /*= std::cout*/ ) const
{
	strm << "discountMode=<";
	OrderPositionDiscountModeMapper::toStream( strm, m_DiscountMode );
	strm << ">";
	strm << ", orderNo=<" << m_OrderNo << ">";
	strm << ", positionNo=<" << m_PositionNo << ">";
	strm << ", discountValue=<" << m_DiscountValue << ">";
	strm << ", discountPercent=<" << m_DiscountPercent << ">";
	strm << ", discountQty=<" << m_DiscountQty << ">";
	strm << ", rebateInKindPositionNo=<" << m_RebateInKindPositionNo << ">";
	strm << ", rebateInKindOrderNo=<" << m_RebateInKindOrderNo << ">";
	strm << ", pharmacyGroup=<" << m_PharmacyGroupId << ">";
	return strm;
}

} // end namespace discount
} // end namespace libcsc

