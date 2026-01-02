#include "deliveryadvicemapperbase.h"
#include "deliveryadvice.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceMapperBase::DeliveryAdviceMapperBase( DeliveryAdvicePtr deliveryAdvice ) :
    m_DeliveryAdvice( deliveryAdvice )
{
}

DeliveryAdviceMapperBase::~DeliveryAdviceMapperBase()
{
}

void DeliveryAdviceMapperBase::map()
{
    doMap();
}

void DeliveryAdviceMapperBase::mapKeysOnly()
{
    doMapKeysOnly();
}

void DeliveryAdviceMapperBase::setBranchNo(const basar::Int16 branchNo)
{
    m_DeliveryAdvice->m_BranchNo = branchNo;
    m_DeliveryAdvice->m_BranchNo.setClean();
}

void DeliveryAdviceMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
    m_DeliveryAdvice->m_CustomerNo = customerNo;
    m_DeliveryAdvice->m_CustomerNo.setClean();
}

void DeliveryAdviceMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
    m_DeliveryAdvice->m_DeliveryAdviceDate = deliveryAdviceDate;
    m_DeliveryAdvice->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceMapperBase::setDeliveryAdviceNo( const basar::VarString & deliveryAdviceNo )
{
    m_DeliveryAdvice->m_DeliveryAdviceNo = deliveryAdviceNo;
    m_DeliveryAdvice->m_DeliveryAdviceNo.setClean();
}

void DeliveryAdviceMapperBase::setPharmosOrderNo( const basar::Int32 pharmosOrderNo )
{
    m_DeliveryAdvice->m_PharmosOrderNo = pharmosOrderNo;
    m_DeliveryAdvice->m_PharmosOrderNo.setClean();
}

void DeliveryAdviceMapperBase::setCSCOrderNo( const basar::Int32 cscOrderNo )
{
    m_DeliveryAdvice->m_CscOrderNo = cscOrderNo;
    m_DeliveryAdvice->m_CscOrderNo.setClean();
}

void DeliveryAdviceMapperBase::setCompleted( const basar::VarString & completed )
{
    m_DeliveryAdvice->m_Completed = completed;
    m_DeliveryAdvice->m_Completed.setClean();
}

void DeliveryAdviceMapperBase::setSpecialDocumentType( const basar::VarString & specialdocumenttype )
{
    m_DeliveryAdvice->m_SpecialDocumentType = specialdocumenttype;
    m_DeliveryAdvice->m_SpecialDocumentType.setClean();
}

void DeliveryAdviceMapperBase::setTourId( const basar::VarString & tourId )
{
    m_DeliveryAdvice->m_TourId = tourId;
    m_DeliveryAdvice->m_TourId.setClean();
}

void DeliveryAdviceMapperBase::setDueDate( const basar::Date dueDate )
{
    m_DeliveryAdvice->m_DueDate = dueDate;
    m_DeliveryAdvice->m_DueDate.setClean();
}

void DeliveryAdviceMapperBase::setOrderType( const basar::VarString& orderType )
{
    m_DeliveryAdvice->m_OrderType = orderType;
    m_DeliveryAdvice->m_OrderType.setClean();
}

void DeliveryAdviceMapperBase::setPickingType( const basar::VarString& pickingType )
{
    m_DeliveryAdvice->m_PickingType = pickingType;
    m_DeliveryAdvice->m_PickingType.setClean();
}

void DeliveryAdviceMapperBase::setBookingType( const basar::VarString& bookingType )
{
    m_DeliveryAdvice->m_BookingType = bookingType;
    m_DeliveryAdvice->m_BookingType.setClean();
}

void DeliveryAdviceMapperBase::setRequested( const basar::Int16 requested )
{
    m_DeliveryAdvice->m_Requested = requested;
    m_DeliveryAdvice->m_Requested.setClean();
}

void DeliveryAdviceMapperBase::setConfirmed( const basar::Int16 confirmed )
{
    m_DeliveryAdvice->m_Confirmed = confirmed;
    m_DeliveryAdvice->m_Confirmed.setClean();
}

void DeliveryAdviceMapperBase::setOrderLabel( const basar::VarString& orderLabel )
{
    m_DeliveryAdvice->m_OrderLabel = orderLabel;
    m_DeliveryAdvice->m_OrderLabel.setClean();
}

void DeliveryAdviceMapperBase::setCancelled( const basar::Int16 cancelled )
{
    m_DeliveryAdvice->m_Cancelled = cancelled;
    m_DeliveryAdvice->m_Cancelled.setClean();
}

void DeliveryAdviceMapperBase::setBatchCorrectionAdvice(const basar::Int16 batchCorrectionAdvice)
{
    m_DeliveryAdvice->m_BatchCorrectionAdvice = batchCorrectionAdvice;
    m_DeliveryAdvice->m_BatchCorrectionAdvice.setClean();
}

void DeliveryAdviceMapperBase::setLineFee(const basar::Decimal & lineFee)
{
    m_DeliveryAdvice->m_LineFee = lineFee;
    m_DeliveryAdvice->m_LineFee.setClean();
}

void DeliveryAdviceMapperBase::setPackageFee(const basar::Decimal & packageFee)
{
    m_DeliveryAdvice->m_PackageFee = packageFee;
    m_DeliveryAdvice->m_PackageFee.setClean();
}

void DeliveryAdviceMapperBase::setContractId(const basar::VarString& contractId)
{
    m_DeliveryAdvice->m_ContractId = contractId;
    m_DeliveryAdvice->m_ContractId.setClean();
}

void DeliveryAdviceMapperBase::setDepositValue(const basar::Decimal & depositValue)
{
    m_DeliveryAdvice->m_DepositValue = depositValue;
    m_DeliveryAdvice->m_DepositValue.setClean();
}

void DeliveryAdviceMapperBase::setNetTurnover(const basar::Decimal& netTurnover)
{
    m_DeliveryAdvice->m_NetTurnover = netTurnover;
    m_DeliveryAdvice->m_NetTurnover.setClean();
}

void DeliveryAdviceMapperBase::setDiscountRetail(const basar::Decimal& discountRetail)
{
    m_DeliveryAdvice->m_DiscountRetail = discountRetail;
    m_DeliveryAdvice->m_DiscountRetail.setClean();
}

void DeliveryAdviceMapperBase::setDiscountWholesale(const basar::Decimal& discountWholesale)
{
    m_DeliveryAdvice->m_DiscountWholesale = discountWholesale;
    m_DeliveryAdvice->m_DiscountWholesale.setClean();
}

void DeliveryAdviceMapperBase::setVatAmount(const basar::Decimal& vatAmount)
{
    m_DeliveryAdvice->m_VatAmount = vatAmount;
    m_DeliveryAdvice->m_VatAmount.setClean();
}

void DeliveryAdviceMapperBase::setLogisticServiceCost(const basar::Decimal & logisticServiceCost)
{
    m_DeliveryAdvice->m_LogisticServiceCost = logisticServiceCost;
    m_DeliveryAdvice->m_LogisticServiceCost.setClean();
}

void DeliveryAdviceMapperBase::setDocumentId(const basar::VarString& documentId)
{
    m_DeliveryAdvice->m_DocumentId = documentId;
    m_DeliveryAdvice->m_DocumentId.setClean();
}


} // end namespace document
} // end namespace libcsc
