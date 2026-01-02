#include "deliveryadvicelinediscount.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineDiscount::DeliveryAdviceLineDiscount()
{
}

DeliveryAdviceLineDiscount::~DeliveryAdviceLineDiscount()
{
}

const basar::Int16& DeliveryAdviceLineDiscount::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLineDiscount::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLineDiscount::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::Int32& DeliveryAdviceLineDiscount::getPharmosOrderNo() const
{
	return m_PharmosOrderNo;
}

const basar::Int32& DeliveryAdviceLineDiscount::getPharmosOrderPosNo() const
{
	return m_PharmosOrderPosNo;
}

const basar::Int16& DeliveryAdviceLineDiscount::getDiscountMode() const
{
	return m_DiscountMode;
}

const basar::VarString& DeliveryAdviceLineDiscount::getDiscountModeName() const
{
	return m_DiscountModeName;
}

const basar::Decimal& DeliveryAdviceLineDiscount::getDiscount() const
{
	return m_Discount;
}

const basar::VarString& DeliveryAdviceLineDiscount::getOrigin() const
{
	return m_Origin;
}

const basar::Int16& DeliveryAdviceLineDiscount::getDeleteReason() const
{
	return m_DeleteReason;
}

const basar::Decimal& DeliveryAdviceLineDiscount::getDiscountValue() const
{
	return m_DiscountValue;
}

const basar::Int16& DeliveryAdviceLineDiscount::getDiscountType() const
{
	return m_DiscountType;
}

const basar::Int16& DeliveryAdviceLineDiscount::getHierarchy() const
{
	return m_Hierarchy;
}

const basar::Int16& DeliveryAdviceLineDiscount::getCalculationBasis() const
{
	return m_CalculationBasis;
}

const enum KindOfDiscountEnum& DeliveryAdviceLineDiscount::getKindOfDiscount() const
{
	return m_KindOfDiscount;
}

} // namespace document
} // namespace libcsc
