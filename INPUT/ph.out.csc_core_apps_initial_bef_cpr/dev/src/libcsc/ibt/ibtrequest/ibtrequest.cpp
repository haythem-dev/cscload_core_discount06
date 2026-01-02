#include "ibtrequest.h"
#include "iibtrequestfactory.h"

//#include "ibtdiscountrequestcollection.h"
//#include "ibtdiscountrequest.h"
//#include "ibtremarkrequestcollection.h"
//#include "ibtremarkrequest.h"
#include "logger/loggerpool.h"

namespace libcsc 
{
namespace ibt
{
IbtRequest::IbtRequest()
{
    m_PropertyCollection.add( m_IbtRequestId );
    m_PropertyCollection.add( m_BranchNo );
    m_PropertyCollection.add( m_CscOrderNo );
    m_PropertyCollection.add( m_CscOrderPosNo );
    m_PropertyCollection.add( m_IbtBranchNo );
    m_PropertyCollection.add( m_IbtCustomerNo );
    m_PropertyCollection.add( m_CreationDateTime );
    m_PropertyCollection.add( m_ProcessingState );
    m_PropertyCollection.add( m_CustomerNo );
    m_PropertyCollection.add( m_OrderType );
    m_PropertyCollection.add( m_PickingType );
    m_PropertyCollection.add( m_BookingType );
    m_PropertyCollection.add( m_ArticleNo );
    m_PropertyCollection.add( m_ArticleCodeType );
    m_PropertyCollection.add( m_ArticleCode );
    m_PropertyCollection.add( m_Quantity );
    m_PropertyCollection.add( m_CustomerTourId );
    m_PropertyCollection.add( m_TourWeekDay );
    m_PropertyCollection.add( m_NLevelIbtTypeId );
    m_PropertyCollection.add( m_DayIbtFlag );
    m_PropertyCollection.add( m_CustOrderRef );
    m_PropertyCollection.add( m_ManualFixPrice );
    m_PropertyCollection.add( m_PaymentTerm );
	m_PropertyCollection.add( m_IbtTourId );
	m_PropertyCollection.add( m_IbtTourDate );
}

IbtRequest::~IbtRequest()
{
}

void IbtRequest::injectRequestFactory( IIbtRequestFactoryPtr factory )
{
	m_Factory = factory;
}

const libcsc::Int32 & IbtRequest::getIbtRequestId() const
{
    return m_IbtRequestId;
}

const basar::Int16 & IbtRequest::getBranchNo() const
{
    return m_BranchNo;
}

const basar::Int32 & IbtRequest::getCscOrderNo() const
{
    return m_CscOrderNo;
}

const basar::Int32 & IbtRequest::getCscOrderPosNo() const
{
    return m_CscOrderPosNo;
}

const basar::Int16 & IbtRequest::getIbtBranchNo() const
{
    return m_IbtBranchNo;
}

const basar::Int32 & IbtRequest::getIbtCustomerNo() const
{
    return m_IbtCustomerNo;
}

const basar::DateTime & IbtRequest::getCreationDateTime() const
{
    return m_CreationDateTime;
}

const IbtRequestProcessingStateEnum & IbtRequest::getProcessingState() const
{
    return m_ProcessingState;
}

const basar::Int32 & IbtRequest::getCustomerNo() const
{
    return m_CustomerNo;
}

const basar::VarString & IbtRequest::getOrderType() const
{
    return m_OrderType;
}

const basar::VarString & IbtRequest::getPickingType() const
{
    return m_PickingType;
}

const basar::VarString & IbtRequest::getBookingType() const
{
    return m_BookingType;
}

const basar::Int32 & IbtRequest::getArticleNo() const
{
    return m_ArticleNo;
}

const basar::Int16 & IbtRequest::getArticleCodeType() const
{
    return m_ArticleCodeType;
}

const basar::VarString & IbtRequest::getArticleCode() const
{
    return m_ArticleCode;
}

const basar::Int32 & IbtRequest::getQuantity() const
{
    return m_Quantity;
}

const basar::VarString & IbtRequest::getCustomerTourId() const
{
    return m_CustomerTourId;
}

const ::WeekDayEnum & IbtRequest::getTourWeekDay() const
{
    return m_TourWeekDay;
}

const basar::Int16 & IbtRequest::getNLevelIbtTypeId() const
{
    return m_NLevelIbtTypeId;
}

const basar::Int16 & IbtRequest::getDayIbtFlag() const
{
    return m_DayIbtFlag;
}

const basar::VarString & IbtRequest::getCustOrderRef() const
{
    return m_CustOrderRef;
}

const basar::Decimal & IbtRequest::getManualFixPrice() const
{
    return m_ManualFixPrice;
}

const basar::VarString & IbtRequest::getPaymentTerm() const
{
    return m_PaymentTerm;
}

const basar::VarString & IbtRequest::getIbtTourId() const
{
	return m_IbtTourId;
}

const basar::Date & IbtRequest::getIbtTourDate() const
{
	return m_IbtTourDate;
}

const IIbtRequestDiscountCollection & IbtRequest::getDiscounts() const
{
	return m_Discounts;
}

const IIbtRequestRemarkCollection & IbtRequest::getRemarks() const
{
	return m_Remarks;
}

IIbtRequestDiscountPtr IbtRequest::getDiscount( const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo )
{
	IIbtRequestDiscountCollection::const_iterator iter = m_Discounts.begin();
	for( ; iter != m_Discounts.end(); ++iter )
	{
		IIbtRequestDiscountPtr discount( *iter );
		if(    discountType == discount->getDiscountType()
			&& paymentTargetNo == discount->getPaymentTargetNo() )
		{
			return discount;
		}
	}

	return m_Factory->createRequestDiscount( shared_from_this(), discountType, paymentTargetNo );
}

IIbtRequestRemarkPtr IbtRequest::getRemark( const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType )
{
	IIbtRequestRemarkCollection::const_iterator iter = m_Remarks.begin();
	for( ; iter != m_Remarks.end(); ++iter )
	{
		IIbtRequestRemarkPtr remark( *iter );
		if(    remarkLevel == remark->getRemarkLevel() 
			&& remarkType == remark->getRemarkType() )
		{
			return remark;
		}
	}

	return m_Factory->createRequestRemark( shared_from_this(), remarkLevel, remarkType );
}

void IbtRequest::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequestId = ibtRequestId;
}

void IbtRequest::setBranchNo( const basar::Int16 branchNo )
{
    m_BranchNo = branchNo;
}

void IbtRequest::setCscOrderNo( const basar::Int32 cscOrderNo )
{
    m_CscOrderNo = cscOrderNo;
}

void IbtRequest::setCscOrderPosNo( const basar::Int32 cscOrderPosNo )
{
    m_CscOrderPosNo = cscOrderPosNo;
}

void IbtRequest::setIbtBranchNo( const basar::Int16 ibtBranchNo )
{
    m_IbtBranchNo = ibtBranchNo;
}

void IbtRequest::setIbtCustomerNo( const basar::Int32 ibtCustomerNo )
{
    m_IbtCustomerNo = ibtCustomerNo;
}

void IbtRequest::setCreationDateTime( const basar::DateTime & creationDateTime )
{
    m_CreationDateTime = creationDateTime;
}

void IbtRequest::setProcessingState( const IbtRequestProcessingStateEnum processingState )
{
    m_ProcessingState = processingState;
}

void IbtRequest::setCustomerNo( const basar::Int32 customerNo )
{
    m_CustomerNo = customerNo;
}

void IbtRequest::setOrderType( const basar::VarString & orderType )
{
    m_OrderType = orderType;
}

void IbtRequest::setPickingType( const basar::VarString & pickingType )
{
    m_PickingType = pickingType;
}

void IbtRequest::setBookingType( const basar::VarString & bookingType )
{
    m_BookingType = bookingType;
}

void IbtRequest::setArticleNo( const basar::Int32 articleNo )
{
    m_ArticleNo = articleNo;
}

void IbtRequest::setArticleCodeType( const basar::Int16 articleCodeType )
{
    m_ArticleCodeType = articleCodeType;
}

void IbtRequest::setArticleCode( const basar::VarString & articleCode )
{
    m_ArticleCode = articleCode;
}

void IbtRequest::setQuantity( const basar::Int32 quantity )
{
    m_Quantity = quantity;
}

void IbtRequest::setCustomerTourId( const basar::VarString & customerTourId )
{
    m_CustomerTourId = customerTourId;
}

void IbtRequest::setTourWeekDay( const ::WeekDayEnum tourWeekDay )
{
    m_TourWeekDay = tourWeekDay;
}

void IbtRequest::setNLevelIbtTypeId( const basar::Int16 nLevelIbtTypeId )
{
    m_NLevelIbtTypeId = nLevelIbtTypeId;
}

void IbtRequest::setDayIbtFlag( const basar::Int16 dayIbtFlag )
{
    m_DayIbtFlag = dayIbtFlag;
}

void IbtRequest::setCustOrderRef( const basar::VarString & custOrderRef )
{
    m_CustOrderRef = custOrderRef;
}

void IbtRequest::setManualFixPrice( const basar::Decimal & manualFixPrice )
{
    m_ManualFixPrice = manualFixPrice;
}

void IbtRequest::setPaymentTerm( const basar::VarString & paymentTerm )
{
    m_PaymentTerm = paymentTerm;
}

void IbtRequest::setIbtTourId( const basar::VarString & ibttourid )
{
	m_IbtTourId = ibttourid;
}

void IbtRequest::setIbtTourDate( const basar::Date & ibttourdate )
{
	m_IbtTourDate = ibttourdate;
}

std::ostream & IbtRequest::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "m_IbtRequestId=<" << m_IbtRequestId << ">";
	strm << ", m_BranchNo=<" << m_BranchNo << ">";
	strm << ", m_CscOrderNo=<" << m_CscOrderNo << ">";
	strm << ", m_CscOrderPosNo=<" << m_CscOrderPosNo << ">";
	strm << ", m_IbtBranchNo=<" << m_IbtBranchNo << ">";
	strm << ", m_IbtCustomerNo=<" << m_IbtCustomerNo << ">";
	strm << ", m_CreationDateTime=<" << m_CreationDateTime << ">";
	strm << ", m_ProcessingState=<" << m_ProcessingState << ">";
	strm << ", m_CustomerNo=<" << m_CustomerNo << ">";
	strm << ", m_OrderType=<" << m_OrderType << ">";
	strm << ", m_PickingType=<" << m_PickingType << ">";
	strm << ", m_BookingType=<" << m_BookingType << ">";
	strm << ", m_ArticleNo=<" << m_ArticleNo << ">";
	strm << ", m_ArticleCodeType=<" << m_ArticleCodeType << ">";
	strm << ", m_ArticleCode=<" << m_ArticleCode << ">";
	strm << ", m_Quantity=<" << m_Quantity << ">";
	strm << ", m_CustomerTourId=<" << m_CustomerTourId << ">";
	strm << ", m_TourWeekDay=<" << m_TourWeekDay << ">";
	strm << ", m_NLevelIbtTypeId=<" << m_NLevelIbtTypeId << ">";
	strm << ", m_DayIbtFlag=<" << m_DayIbtFlag << ">";
	strm << ", m_CustOrderRef=<" << m_CustOrderRef << ">";
	strm << ", m_ManualFixPrice=<" << m_ManualFixPrice << ">";
	strm << ", m_PaymentTerm=<" << m_PaymentTerm << ">";
	strm << ", m_IbtTourId=<" << m_IbtTourId << ">";
	strm << ", m_IbtTourDate=<" << m_IbtTourDate << ">\n";

	strm << "m_Discounts == \n";
	IIbtRequestDiscountCollection::const_iterator discountIter = m_Discounts.begin();
	for( ; discountIter !=  m_Discounts.end(); ++discountIter )
	{
		( *discountIter )->toStream( strm );
		strm << "\n";
	}

	strm << "m_Remarks == \n";
	IIbtRequestRemarkCollection::const_iterator remarkIter = m_Remarks.begin();
	for( ; remarkIter !=  m_Remarks.end(); ++remarkIter )
	{
		( *remarkIter )->toStream( strm );
		strm << "\n";
	}

	return strm;
}

void IbtRequest::markAsBooked()
{
	setProcessingState( libcsc::ibt::Processed );
}

bool IbtRequest::hasToBeBooked()
{
	return ( 0 < m_Quantity );
}

bool IbtRequest::isProcessed()
{
	return ( libcsc::ibt::Processed == getProcessingState() );
}

void IbtRequest::setClean()
{
	m_PropertyCollection.setClean();
}

bool IbtRequest::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

} // namespace ibt
} // namespace libcsc
