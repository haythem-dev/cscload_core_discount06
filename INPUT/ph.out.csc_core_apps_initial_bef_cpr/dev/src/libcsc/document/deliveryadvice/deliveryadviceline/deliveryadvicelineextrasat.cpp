#include "deliveryadvicelineextrasat.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineExtrasAT::DeliveryAdviceLineExtrasAT()
{
}

DeliveryAdviceLineExtrasAT::~DeliveryAdviceLineExtrasAT()
{
}

const basar::Int16& DeliveryAdviceLineExtrasAT::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLineExtrasAT::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLineExtrasAT::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::Int32& DeliveryAdviceLineExtrasAT::getPharmosOrderNo() const
{
	return m_PharmosOrderNo;
}

const basar::Int32& DeliveryAdviceLineExtrasAT::getPharmosOrderPosNo() const
{
	return m_PharmosOrderPosNo;
}

const basar::Int32& DeliveryAdviceLineExtrasAT::getDeliveryPosNo() const
{
	return m_DeliveryPosNo;
}

bool DeliveryAdviceLineExtrasAT::isNarcotic() const
{
	return m_IsNarcotic;
}

bool DeliveryAdviceLineExtrasAT::isRX() const
{
	return m_IsRX;
}

bool DeliveryAdviceLineExtrasAT::isPsychotropic() const
{
	return m_IsPsychotropic;
}

bool DeliveryAdviceLineExtrasAT::isVeterinary() const
{
	return m_IsVeterinary;
}

bool DeliveryAdviceLineExtrasAT::isHazardous() const
{
	return m_IsHazardous;
}

bool DeliveryAdviceLineExtrasAT::isReportable() const
{
	return m_IsReportable;
}

bool DeliveryAdviceLineExtrasAT::isShortExpiry() const
{
	return m_IsShortExpiry;
}

} // namespace document
} // namespace libcsc
