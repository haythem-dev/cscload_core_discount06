#include "deliveryadviceremarks.h"

namespace libcsc {
namespace document {

DeliveryAdviceRemarks::DeliveryAdviceRemarks()
{
}

DeliveryAdviceRemarks::~DeliveryAdviceRemarks()
{
}

const basar::Int16& DeliveryAdviceRemarks::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceRemarks::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceRemarks::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::Int32& DeliveryAdviceRemarks::getCSCOrderNo() const
{
	return m_CSCOrderNo;
}

const basar::Int32& DeliveryAdviceRemarks::getCSCOrderPosNo() const
{
	return m_CSCOrderPosNo;
}

const ::OrderRemarkTypeEnum& DeliveryAdviceRemarks::getRemarkType() const
{
	return m_RemarkType;
}

const basar::Int16& DeliveryAdviceRemarks::getSerialNo() const
{
	return m_SerialNo;
}

const basar::VarString& DeliveryAdviceRemarks::getRemarkText() const
{
	return m_RemarkText;
}


} // namespace document
} // namespace libcsc
