#include "orderresponsemapperbase.h"
#include "orderresponse.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace msv3 {

OrderResponseMapperBase::OrderResponseMapperBase(OrderResponsePtr orderResponse) :
	m_OrderResponse(orderResponse)
{
}

OrderResponseMapperBase::~OrderResponseMapperBase()
{
}

void OrderResponseMapperBase::map()
{
	doMap();
}

void OrderResponseMapperBase::mapSerial(const basar::Int32& id)
{
	doMapSerial(id);
}

void OrderResponseMapperBase::setId(const basar::Int32& id)
{
	m_OrderResponse->m_Id = id;
	m_OrderResponse->m_Id.setClean();
}

void OrderResponseMapperBase::setTransmissionId(const basar::Int32& transmissionId)
{
	m_OrderResponse->m_TransmissionId = transmissionId;
	m_OrderResponse->m_TransmissionId.setClean();
}

void OrderResponseMapperBase::setOrderUuid(const basar::VarString& orderUuid)
{
	m_OrderResponse->m_OrderUuid = orderUuid;
	m_OrderResponse->m_OrderUuid.setClean();
}

void OrderResponseMapperBase::setCscOrderNo(const basar::Int32& cscOrderNo)
{
	m_OrderResponse->m_CscOrderNo = cscOrderNo;
	m_OrderResponse->m_CscOrderNo.setClean();
}

void OrderResponseMapperBase::setBundleId(const basar::VarString& bundleId)
{
	m_OrderResponse->m_BundleId = bundleId;
	m_OrderResponse->m_BundleId.setClean();
}

void OrderResponseMapperBase::setOrderLabel(const basar::VarString& orderLabel)
{
	m_OrderResponse->m_OrderLabel = orderLabel;
	m_OrderResponse->m_OrderLabel.setClean();
}

void OrderResponseMapperBase::setOrderSupportId(const basar::Int32& orderSupportId)
{
	m_OrderResponse->m_OrderSupportId = orderSupportId;
	m_OrderResponse->m_OrderSupportId.setClean();
}

void OrderResponseMapperBase::setClean()
{
	m_OrderResponse->m_Id.setClean();
	m_OrderResponse->m_TransmissionId.setClean();
	m_OrderResponse->m_OrderUuid.setClean();
	m_OrderResponse->m_CscOrderNo.setClean();
	m_OrderResponse->m_BundleId.setClean();
	m_OrderResponse->m_OrderLabel.setClean();
	m_OrderResponse->m_OrderSupportId.setClean();
}

} // end namespace msv3
} // end namespace libcsc
