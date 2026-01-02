#include "deliveryadvicelinedetails.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineDetails::DeliveryAdviceLineDetails()
{
}

DeliveryAdviceLineDetails::~DeliveryAdviceLineDetails()
{
}

const basar::Int16& DeliveryAdviceLineDetails::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLineDetails::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLineDetails::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::Int32& DeliveryAdviceLineDetails::getPharmosOrderNo() const
{
	return m_PharmosOrderNo;
}

const basar::Int32& DeliveryAdviceLineDetails::getPharmosOrderPosNo() const
{
	return m_PharmosOrderPosNo;
}

const basar::Int32& DeliveryAdviceLineDetails::getDeliveryPosNo() const
{
	return m_DeliveryPosNo;
}

const basar::Int32& DeliveryAdviceLineDetails::getQuantityDelivery() const
{
	return m_QuantityDelivery;
}

const basar::VarString& DeliveryAdviceLineDetails::getBatch() const
{
	return m_Batch;
}

const basar::Date& DeliveryAdviceLineDetails::getExpiryDate() const
{
	return m_ExpiryDate;
}

const basar::Int32& DeliveryAdviceLineDetails::getPackageId() const
{
	return m_PackageId;
}

const basar::VarString& DeliveryAdviceLineDetails::getTrackingId() const
{
	return m_TrackingId;
}

const basar::Int32& DeliveryAdviceLineDetails::getQuantityLack() const
{
	return m_QuantityLack;
}

const basar::Int16&	DeliveryAdviceLineDetails::getPreCalcBatchChanged() const
{
	return m_PreCalcBatchChanged;
}

bool DeliveryAdviceLineDetails::isPreCalcBatchChanged() const
{
	return m_PreCalcBatchChanged > 0;
}

} // namespace document
} // namespace libcsc
