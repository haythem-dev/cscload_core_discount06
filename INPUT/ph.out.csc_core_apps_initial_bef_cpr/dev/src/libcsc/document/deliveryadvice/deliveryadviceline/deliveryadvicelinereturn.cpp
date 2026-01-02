#include "deliveryadvicelinereturn.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineReturn::DeliveryAdviceLineReturn()
{
}

DeliveryAdviceLineReturn::~DeliveryAdviceLineReturn()
{
}

const basar::Int16& DeliveryAdviceLineReturn::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLineReturn::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLineReturn::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::VarString& DeliveryAdviceLineReturn::getDeliveryAdviceNo() const
{
	return m_DeliveryAdviceNo;
}

const basar::Int32& DeliveryAdviceLineReturn::getDeliveryAdvicePosNo() const
{
	return m_DeliveryAdvicePosNo;
}

const basar::Int16& DeliveryAdviceLineReturn::getBlockedForreturns() const
{
	return m_BlockedForreturns;
}

const basar::Int32& DeliveryAdviceLineReturn::getQuantityReturned() const
{
	return m_QuantityReturned;
}

const basar::Int32& DeliveryAdviceLineReturn::getQuantityReturnedRebateInKind() const
{
	return m_QuantityReturnedRebateInKind;
}

const basar::Int32& DeliveryAdviceLineReturn::getQuantityReturnRejected() const
{
	return m_QuantityReturnRejected;
}

} // namespace document
} // namespace libcsc
