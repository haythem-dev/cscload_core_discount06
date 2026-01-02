#include "ibtrequestmapperbase.h"
#include "ibtrequest.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtRequestMapperBase::IbtRequestMapperBase( IbtRequestPtr ibtRequest )
: m_IbtRequest( ibtRequest )
{
}

IbtRequestMapperBase::~IbtRequestMapperBase()
{
}

void IbtRequestMapperBase::map()
{
    doMap();

    std::stringstream ss;
    ss << "IbtRequestMapperBase::map(), m_IbtRequest: " << *m_IbtRequest << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void IbtRequestMapperBase::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequest->m_IbtRequestId = ibtRequestId;
    m_IbtRequest->m_IbtRequestId.setClean();
}

void IbtRequestMapperBase::setBranchNo( const basar::Int16 branchNo )
{
    m_IbtRequest->m_BranchNo = branchNo;
    m_IbtRequest->m_BranchNo.setClean();
}

void IbtRequestMapperBase::setCscOrderNo( const basar::Int32 cscOrderNo )
{
    m_IbtRequest->m_CscOrderNo = cscOrderNo;
    m_IbtRequest->m_CscOrderNo.setClean();
}

void IbtRequestMapperBase::setCscOrderPosNo( const basar::Int32 cscOrderPosNo )
{
    m_IbtRequest->m_CscOrderPosNo = cscOrderPosNo;
    m_IbtRequest->m_CscOrderPosNo.setClean();
}

void IbtRequestMapperBase::setIbtBranchNo( const basar::Int16 ibtBranchNo )
{
    m_IbtRequest->m_IbtBranchNo = ibtBranchNo;
    m_IbtRequest->m_IbtBranchNo.setClean();
}

void IbtRequestMapperBase::setIbtCustomerNo( const basar::Int32 ibtCustomerNo )
{
    m_IbtRequest->m_IbtCustomerNo = ibtCustomerNo;
    m_IbtRequest->m_IbtCustomerNo.setClean();
}

void IbtRequestMapperBase::setCreationDateTime( const basar::DateTime & creationDateTime )
{
    m_IbtRequest->m_CreationDateTime = creationDateTime;
    m_IbtRequest->m_CreationDateTime.setClean();
}

void IbtRequestMapperBase::setProcessingState( const IbtRequestProcessingStateEnum processingState )
{
    m_IbtRequest->m_ProcessingState = processingState;
    m_IbtRequest->m_ProcessingState.setClean();
}

void IbtRequestMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
    m_IbtRequest->m_CustomerNo = customerNo;
    m_IbtRequest->m_CustomerNo.setClean();
}

void IbtRequestMapperBase::setOrderType( const basar::VarString & orderType )
{
    m_IbtRequest->m_OrderType = orderType;
    m_IbtRequest->m_OrderType.setClean();
}

void IbtRequestMapperBase::setPickingType( const basar::VarString & pickingType )
{
    m_IbtRequest->m_PickingType = pickingType;
    m_IbtRequest->m_PickingType.setClean();
}

void IbtRequestMapperBase::setBookingType( const basar::VarString & bookingType )
{
    m_IbtRequest->m_BookingType = bookingType;
    m_IbtRequest->m_BookingType.setClean();
}

void IbtRequestMapperBase::setArticleNo( const basar::Int32 articleNo )
{
    m_IbtRequest->m_ArticleNo = articleNo;
    m_IbtRequest->m_ArticleNo.setClean();
}

void IbtRequestMapperBase::setArticleCodeType( const basar::Int16 articleCodeType )
{
    m_IbtRequest->m_ArticleCodeType = articleCodeType;
    m_IbtRequest->m_ArticleCodeType.setClean();
}

void IbtRequestMapperBase::setArticleCode( const basar::VarString & articleCode )
{
    m_IbtRequest->m_ArticleCode = articleCode;
    m_IbtRequest->m_ArticleCode.setClean();
}

void IbtRequestMapperBase::setQuantity( const basar::Int32 quantity )
{
    m_IbtRequest->m_Quantity = quantity;
    m_IbtRequest->m_Quantity.setClean();
}

void IbtRequestMapperBase::setCustomerTourId( const basar::VarString & customerTourId )
{
    m_IbtRequest->m_CustomerTourId = customerTourId;
    m_IbtRequest->m_CustomerTourId.setClean();
}

void IbtRequestMapperBase::setTourWeekDay( const ::WeekDayEnum tourWeekDay )
{
    m_IbtRequest->m_TourWeekDay = tourWeekDay;
    m_IbtRequest->m_TourWeekDay.setClean();
}

void IbtRequestMapperBase::setNLevelIbtTypeId( const basar::Int16 nLevelIbtTypeId )
{
    m_IbtRequest->m_NLevelIbtTypeId = nLevelIbtTypeId;
    m_IbtRequest->m_NLevelIbtTypeId.setClean();
}

void IbtRequestMapperBase::setDayIbtFlag( const basar::Int16 dayIbtFlag )
{
    m_IbtRequest->m_DayIbtFlag = dayIbtFlag;
    m_IbtRequest->m_DayIbtFlag.setClean();
}

void IbtRequestMapperBase::setCustOrderRef( const basar::VarString & custOrderRef )
{
    m_IbtRequest->m_CustOrderRef = custOrderRef;
    m_IbtRequest->m_CustOrderRef.setClean();
}

void IbtRequestMapperBase::setManualFixPrice( const basar::Decimal & manualFixPrice )
{
    m_IbtRequest->m_ManualFixPrice = manualFixPrice;
    m_IbtRequest->m_ManualFixPrice.setClean();
}

void IbtRequestMapperBase::setPaymentTerm( const basar::VarString & paymentTerm )
{
    m_IbtRequest->m_PaymentTerm = paymentTerm;
    m_IbtRequest->m_PaymentTerm.setClean();
}

void IbtRequestMapperBase::setIbtTourId( const basar::VarString & ibttourid )
{
    m_IbtRequest->m_IbtTourId = ibttourid;
    m_IbtRequest->m_IbtTourId.setClean();
}

void IbtRequestMapperBase::setIbtTourDate( const basar::Date & ibttourdate )
{
    m_IbtRequest->m_IbtTourDate = ibttourdate;
    m_IbtRequest->m_IbtTourDate.setClean();
}

} // end namespace ibt
} // end namespace libcsc
