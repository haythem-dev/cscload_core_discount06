#include "deliveryadvicelineibtlinkmapperbase.h"
#include "deliveryadvicelineibtlink.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineIbtLinkMapperBase::DeliveryAdviceLineIbtLinkMapperBase( DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink ) :
	m_DeliveryAdviceLineIbtLink( deliveryAdviceLineIbtLink )
{
}

DeliveryAdviceLineIbtLinkMapperBase::~DeliveryAdviceLineIbtLinkMapperBase()
{
}

void DeliveryAdviceLineIbtLinkMapperBase::map()
{
	doMap();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapCustomerOrders()
{
    doMapCustomerOrders();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapCustomerOrderDetails()
{
    doMapCustomerOrderDetails();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapDeliveryAdvice4CustomerOrder()
{
    doMapDeliveryAdvice4CustomerOrder();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapShuttleOrders()
{
    doMapShuttleOrders();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapShuttleOrderDetails()
{
    doMapShuttleOrderDetails();
}

void DeliveryAdviceLineIbtLinkMapperBase::mapDeliveryAdvice4ShuttleOrder()
{
    doMapDeliveryAdvice4ShuttleOrder();
}

void DeliveryAdviceLineIbtLinkMapperBase::setBranchNo(const basar::Int16 branchNo)
{
	m_DeliveryAdviceLineIbtLink->m_BranchNo = branchNo;
	m_DeliveryAdviceLineIbtLink->m_BranchNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLineIbtLink->m_CustomerNo = customerNo;
	m_DeliveryAdviceLineIbtLink->m_CustomerNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setDeliveryAdviceNo( const basar::VarString& deliveryAdviceNo )
{
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdviceNo = deliveryAdviceNo;
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdviceNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setDeliveryAdvicePosNo( const basar::Int32 deliveryAdvicePosNo )
{
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdvicePosNo = deliveryAdvicePosNo;
	m_DeliveryAdviceLineIbtLink->m_DeliveryAdvicePosNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setCscOrderNo( const basar::Int32 cscOrderNo )
{
	m_DeliveryAdviceLineIbtLink->m_CscOrderNo = cscOrderNo;
	m_DeliveryAdviceLineIbtLink->m_CscOrderNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setCscOrderPosNo( const basar::Int32 cscOrderPosNo )
{
	m_DeliveryAdviceLineIbtLink->m_CscOrderPosNo = cscOrderPosNo;
	m_DeliveryAdviceLineIbtLink->m_CscOrderPosNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtBranchNo( const basar::Int16 ibtBranchNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtBranchNo = ibtBranchNo;
	m_DeliveryAdviceLineIbtLink->m_IbtBranchNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtCustomerNo( const basar::Int32 ibtCustomerNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtCustomerNo = ibtCustomerNo;
	m_DeliveryAdviceLineIbtLink->m_IbtCustomerNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtDeliveryAdviceDate( const basar::Date& ibtDeliveryAdviceDate )
{
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdviceDate = ibtDeliveryAdviceDate;
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdviceDate.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtDeliveryAdviceNo( const basar::VarString& ibtDeliveryAdviceNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdviceNo = ibtDeliveryAdviceNo;
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdviceNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtDeliveryAdvicePosNo( const basar::Int32 ibtDeliveryAdvicePosNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdvicePosNo = ibtDeliveryAdvicePosNo;
	m_DeliveryAdviceLineIbtLink->m_IbtDeliveryAdvicePosNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtCscOrderNo( const basar::Int32 ibtCscOrderNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtCscOrderNo = ibtCscOrderNo;
	m_DeliveryAdviceLineIbtLink->m_IbtCscOrderNo.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setIbtCscOrderPosNo( const basar::Int32 ibtCscOrderPosNo )
{
	m_DeliveryAdviceLineIbtLink->m_IbtCscOrderPosNo = ibtCscOrderPosNo;
	m_DeliveryAdviceLineIbtLink->m_IbtCscOrderPosNo.setClean();
}

// TEMP property
void DeliveryAdviceLineIbtLinkMapperBase::setPositionBookingDate(const basar::Int32& positionBookingDate)
{
	m_DeliveryAdviceLineIbtLink->m_PositionBookingDate = positionBookingDate;
	m_DeliveryAdviceLineIbtLink->m_PositionBookingDate.setClean();
}

void DeliveryAdviceLineIbtLinkMapperBase::setCustomerOrderArchived(const bool& customerOrderArchived)
{
	m_DeliveryAdviceLineIbtLink->m_CustomerOrderArchived = customerOrderArchived;
	m_DeliveryAdviceLineIbtLink->m_CustomerOrderArchived.setClean();
}


} // end namespace document
} // end namespace libcsc
