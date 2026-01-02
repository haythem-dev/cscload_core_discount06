#include "orderresponse.h"

namespace libcsc {
namespace msv3 {

OrderResponse::OrderResponse()
{
}

OrderResponse::~OrderResponse()
{
}

const Int32& OrderResponse::getId() const
{
	return m_Id;
}

const libcsc::Int32& OrderResponse::getTransmissionId() const
{
	return m_TransmissionId;
}

const libcsc::VarString& OrderResponse::getOrderUuid() const
{
	return m_OrderUuid;
}

const libcsc::Int32& OrderResponse::getCscOrderNo() const
{
	return m_CscOrderNo;
}

const libcsc::VarString& OrderResponse::getBundleId() const
{
	return m_BundleId;
}

const libcsc::VarString& OrderResponse::getOrderLabel() const
{
	return m_OrderLabel;
}

const libcsc::Int32& OrderResponse::getOrderSupportId() const
{
	return m_OrderSupportId;
}

void OrderResponse::setId(const Int32& id)
{
	m_Id = id;
}

void OrderResponse::setTransmissionId(const libcsc::Int32& transmissionId)
{
	m_TransmissionId = transmissionId;
}

void OrderResponse::setOrderUuid(const libcsc::VarString& orderUuid)
{
	m_OrderUuid = orderUuid;
}

void OrderResponse::setCscOrderNo(const libcsc::Int32& cscOrderNo)
{
	m_CscOrderNo = cscOrderNo;
}

void OrderResponse::setBundleId(const libcsc::VarString& bundleId)
{
	m_BundleId = bundleId;
}

void OrderResponse::setOrderLabel(const libcsc::VarString& orderLabel)
{
	m_OrderLabel = orderLabel;
}

void OrderResponse::setOrderSupportId(const libcsc::Int32& orderSupportId)
{
	m_OrderSupportId = orderSupportId;
}

bool OrderResponse::isClean()
{
	return m_Id.isClean() && m_TransmissionId.isClean();
}

bool OrderResponse::isDirty()
{
	return m_TransmissionId.isDirty() && m_OrderUuid.isDirty();
}

void OrderResponse::setClean()
{
}

} // namespace msv3
} // namespace libcsc
