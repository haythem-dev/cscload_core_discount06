#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlink.h>


namespace libcsc {
namespace document {

DeliveryAdviceLineIbtLink::DeliveryAdviceLineIbtLink()
{
}

DeliveryAdviceLineIbtLink::DeliveryAdviceLineIbtLink(DeliveryAdviceLineIbtLink& deliveryAdviceLineIbtLink)
{
    setBranchNo(deliveryAdviceLineIbtLink.getBranchNo());
    setCustomerNo(deliveryAdviceLineIbtLink.getCustomerNo());
    setDeliveryAdviceDate(deliveryAdviceLineIbtLink.getDeliveryAdviceDate());
    setDeliveryAdviceNo(deliveryAdviceLineIbtLink.getDeliveryAdviceNo());
    setDeliveryAdvicePosNo(deliveryAdviceLineIbtLink.getDeliveryAdvicePosNo());
    setCscOrderNo(deliveryAdviceLineIbtLink.getCscOrderNo());
    setCscOrderPosNo(deliveryAdviceLineIbtLink.getCscOrderPosNo());
    setIbtBranchNo(deliveryAdviceLineIbtLink.getIbtBranchNo());
    setIbtCustomerNo(deliveryAdviceLineIbtLink.getIbtCustomerNo());
    setIbtDeliveryAdviceDate(deliveryAdviceLineIbtLink.getIbtDeliveryAdviceDate());
    setIbtDeliveryAdviceNo(deliveryAdviceLineIbtLink.getIbtDeliveryAdviceNo());
    setIbtDeliveryAdvicePosNo(deliveryAdviceLineIbtLink.getIbtDeliveryAdvicePosNo());
    setIbtCscOrderNo(deliveryAdviceLineIbtLink.getIbtCscOrderNo());
    setIbtCscOrderPosNo(deliveryAdviceLineIbtLink.getIbtCscOrderPosNo());
}

DeliveryAdviceLineIbtLink::~DeliveryAdviceLineIbtLink()
{
}

const basar::Int16& DeliveryAdviceLineIbtLink::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLineIbtLink::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::VarString& DeliveryAdviceLineIbtLink::getDeliveryAdviceNo() const
{
	return m_DeliveryAdviceNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getDeliveryAdvicePosNo() const
{
	return m_DeliveryAdvicePosNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getCscOrderNo() const
{
	return m_CscOrderNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getCscOrderPosNo() const
{
	return m_CscOrderPosNo;
}

const basar::Int16& DeliveryAdviceLineIbtLink::getIbtBranchNo() const
{
	return m_IbtBranchNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getIbtCustomerNo() const
{
	return m_IbtCustomerNo;
}

const basar::Date& DeliveryAdviceLineIbtLink::getIbtDeliveryAdviceDate() const
{
	return m_IbtDeliveryAdviceDate;
}

const basar::VarString& DeliveryAdviceLineIbtLink::getIbtDeliveryAdviceNo() const
{
	return m_IbtDeliveryAdviceNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getIbtDeliveryAdvicePosNo() const
{
	return m_IbtDeliveryAdvicePosNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getIbtCscOrderNo() const
{
	return m_IbtCscOrderNo;
}

const basar::Int32& DeliveryAdviceLineIbtLink::getIbtCscOrderPosNo() const
{
	return m_IbtCscOrderPosNo;
}

void DeliveryAdviceLineIbtLink::setBranchNo(const basar::Int16& branchNo)
{
    m_BranchNo = branchNo;
}

void DeliveryAdviceLineIbtLink::setCustomerNo(const basar::Int32& customerNo)
{
    m_CustomerNo = customerNo;
}

void DeliveryAdviceLineIbtLink::setDeliveryAdviceDate(const basar::Date& deliveryAdviceDate)
{
    m_DeliveryAdviceDate = deliveryAdviceDate;
}

void DeliveryAdviceLineIbtLink::setDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo)
{
    m_DeliveryAdviceNo = deliveryAdviceNo;
}

void DeliveryAdviceLineIbtLink::setDeliveryAdvicePosNo(const basar::Int32& deliveryAdvicePosNo)
{
    m_DeliveryAdvicePosNo = deliveryAdvicePosNo;
}

void DeliveryAdviceLineIbtLink::setCscOrderNo(const basar::Int32& cscOrderNo)
{
    m_CscOrderNo = cscOrderNo;
}

void DeliveryAdviceLineIbtLink::setCscOrderPosNo(const basar::Int32& cscOrderPosNo)
{
    m_CscOrderNo = cscOrderPosNo;
}

void DeliveryAdviceLineIbtLink::setIbtBranchNo(const basar::Int16& ibtBranchNo)
{
    m_IbtBranchNo = ibtBranchNo;
}

void DeliveryAdviceLineIbtLink::setIbtCustomerNo(const basar::Int32& ibtCustomerNo)
{
    m_IbtCustomerNo = ibtCustomerNo;
}

void DeliveryAdviceLineIbtLink::setIbtDeliveryAdviceDate(const basar::Date& ibtDeliveryAdviceDate)
{
    m_IbtDeliveryAdviceDate = ibtDeliveryAdviceDate;
}

void DeliveryAdviceLineIbtLink::setIbtDeliveryAdviceNo(const basar::VarString& ibtDeliveryAdviceNo)
{
    m_IbtDeliveryAdviceNo = ibtDeliveryAdviceNo;
}

void DeliveryAdviceLineIbtLink::setIbtDeliveryAdvicePosNo(const basar::Int32& ibtDeliveryAdvicePosNo)
{
    m_IbtDeliveryAdvicePosNo = ibtDeliveryAdvicePosNo;
}

void DeliveryAdviceLineIbtLink::setIbtCscOrderNo(const basar::Int32& ibtCscOrderNo)
{
    m_IbtCscOrderNo = ibtCscOrderNo;
}

void DeliveryAdviceLineIbtLink::setIbtCscOrderPosNo(const basar::Int32& ibtCscOrderPosNo)
{
    m_IbtCscOrderPosNo = ibtCscOrderPosNo;
}

// temp property
const basar::Int32&	DeliveryAdviceLineIbtLink::getPositionBookingDate() const
{
	return m_PositionBookingDate;
}

void DeliveryAdviceLineIbtLink::setPositionBookingDate(const basar::Int32& positionBookingDate)
{
	m_PositionBookingDate = positionBookingDate;
}

const bool&	DeliveryAdviceLineIbtLink::isCustomerOrderArchived() const
{
	return m_CustomerOrderArchived;
}

void DeliveryAdviceLineIbtLink::setCustomerOrderArchived(const bool& customerOrderArchived)
{
	m_CustomerOrderArchived = customerOrderArchived;
}

} // namespace document
} // namespace libcsc
