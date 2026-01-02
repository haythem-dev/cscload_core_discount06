#include "deliveryadvicelinemapperbase.h"
#include "deliveryadviceline.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineMapperBase::DeliveryAdviceLineMapperBase( DeliveryAdviceLinePtr deliveryAdviceLine, const DeliveryAdvicePtr& deliveryAdvice ) :
	m_DeliveryAdviceLine( deliveryAdviceLine ),
    m_DeliveryAdvice(deliveryAdvice)
{
}

DeliveryAdviceLineMapperBase::~DeliveryAdviceLineMapperBase()
{
}

void DeliveryAdviceLineMapperBase::map()
{
	doMap();
}

void DeliveryAdviceLineMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_DeliveryAdviceLine->m_BranchNo = branchNo;
	m_DeliveryAdviceLine->m_BranchNo.setClean();
}

void DeliveryAdviceLineMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLine->m_CustomerNo = customerNo;
	m_DeliveryAdviceLine->m_CustomerNo.setClean();
}

void DeliveryAdviceLineMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceLine->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLine->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceLineMapperBase::setDeliveryAdviceNo( const basar::VarString & deliveryAdviceNo )
{
	m_DeliveryAdviceLine->m_DeliveryAdviceNo = deliveryAdviceNo;
	m_DeliveryAdviceLine->m_DeliveryAdviceNo.setClean();
}

void DeliveryAdviceLineMapperBase::setDeliveryAdvicePosNo( const basar::Int32 deliveryAdvicePosNo )
{
	m_DeliveryAdviceLine->m_DeliveryAdvicePosNo = deliveryAdvicePosNo;
	m_DeliveryAdviceLine->m_DeliveryAdvicePosNo.setClean();
}

void DeliveryAdviceLineMapperBase::setPharmosOrderNo(const basar::Int32 pharmosOrderNo)
{
	m_DeliveryAdviceLine->m_PharmosOrderNo = pharmosOrderNo;
	m_DeliveryAdviceLine->m_PharmosOrderNo.setClean();
}

void DeliveryAdviceLineMapperBase::setPharmosOrderPosNo(const basar::Int32 pharmosOrderPosNo)
{
	m_DeliveryAdviceLine->m_PharmosOrderPosNo = pharmosOrderPosNo;
	m_DeliveryAdviceLine->m_PharmosOrderPosNo.setClean();
}

void DeliveryAdviceLineMapperBase::setCscOrderPosNo( const basar::Int32 cscOrderPosNo )
{
	m_DeliveryAdviceLine->m_CscOrderPosNo = cscOrderPosNo;
	m_DeliveryAdviceLine->m_CscOrderPosNo.setClean();
}

void DeliveryAdviceLineMapperBase::setArticleNo( const basar::Int32 articleNo )
{
	m_DeliveryAdviceLine->m_ArticleNo = articleNo;
	m_DeliveryAdviceLine->m_ArticleNo.setClean();
}

void DeliveryAdviceLineMapperBase::setArticleCode( const basar::VarString & articleCode )
{
	m_DeliveryAdviceLine->m_ArticleCode = articleCode;
	m_DeliveryAdviceLine->m_ArticleCode.setClean();
}

void DeliveryAdviceLineMapperBase::setCodeType( const basar::Int16 codeType )
{
	m_DeliveryAdviceLine->m_CodeType = codeType;
	m_DeliveryAdviceLine->m_CodeType.setClean();
}

void DeliveryAdviceLineMapperBase::setQuantityOrdered( const basar::Int32 qtyOrdered )
{
	m_DeliveryAdviceLine->m_QuantityOrdered = qtyOrdered;
	m_DeliveryAdviceLine->m_QuantityOrdered.setClean();
}

void DeliveryAdviceLineMapperBase::setQuantityConfirmed( const basar::Int32 qtyConfirmed )
{
	m_DeliveryAdviceLine->m_QuantityConfirmed = qtyConfirmed;
	m_DeliveryAdviceLine->m_QuantityConfirmed.setClean();
}

void DeliveryAdviceLineMapperBase::setQuantityRebateInKind( const basar::Int32 qtyRebateInKind )
{
	m_DeliveryAdviceLine->m_QuantityRebateInKind = qtyRebateInKind;
	m_DeliveryAdviceLine->m_QuantityRebateInKind.setClean();
}

void DeliveryAdviceLineMapperBase::setQuantityInvoiced( const basar::Int32 qtyInvoiced )
{
	m_DeliveryAdviceLine->m_QuantityInvoiced = qtyInvoiced;
	m_DeliveryAdviceLine->m_QuantityInvoiced.setClean();
}

void DeliveryAdviceLineMapperBase::setLineReference( const basar::VarString & lineReference )
{
	m_DeliveryAdviceLine->m_LineReference = lineReference;
	m_DeliveryAdviceLine->m_LineReference.setClean();
}

void DeliveryAdviceLineMapperBase::setVat(const basar::VarString & vat)
{
	m_DeliveryAdviceLine->m_Vat = vat;
	m_DeliveryAdviceLine->m_Vat.setClean();
}

void DeliveryAdviceLineMapperBase::setVatPercentage(const basar::Decimal & vatPercentage)
{
	m_DeliveryAdviceLine->m_VatPercentage = vatPercentage;
	m_DeliveryAdviceLine->m_VatPercentage.setClean();
}

void DeliveryAdviceLineMapperBase::setInvoicedPrice( const basar::Decimal& invoicedPrice )
{
	m_DeliveryAdviceLine->m_InvoicedPrice = invoicedPrice;
	m_DeliveryAdviceLine->m_InvoicedPrice.setClean();
}

void DeliveryAdviceLineMapperBase::setLogisticServiceCost( const basar::Decimal& logisticServiceCost )
{
	m_DeliveryAdviceLine->m_LogisticServiceCost = logisticServiceCost;
	m_DeliveryAdviceLine->m_LogisticServiceCost.setClean();
}

void DeliveryAdviceLineMapperBase::setMinLogisticServiceCostValue( const basar::Decimal& minlogisticServiceCostValue )
{
	m_DeliveryAdviceLine->m_MinLogisticServiceCostValue = minlogisticServiceCostValue;
	m_DeliveryAdviceLine->m_MinLogisticServiceCostValue.setClean();
}

void DeliveryAdviceLineMapperBase::setLineType( const basar::Int16 lineType )
{
	m_DeliveryAdviceLine->m_LineType = lineType;
	m_DeliveryAdviceLine->m_LineType.setClean();
}

void DeliveryAdviceLineMapperBase::setArticleName(const basar::VarString& articleName)
{
	m_DeliveryAdviceLine->m_ArticleName = articleName;
	m_DeliveryAdviceLine->m_ArticleName.setClean();
}

void DeliveryAdviceLineMapperBase::setArticleUnit(const basar::VarString& articleUnit)
{
	m_DeliveryAdviceLine->m_ArticleUnit = articleUnit;
	m_DeliveryAdviceLine->m_ArticleUnit.setClean();
}

void DeliveryAdviceLineMapperBase::setPharmaceuticalForm(const basar::VarString& pharmaceuticalForm)
{
	m_DeliveryAdviceLine->m_PharmaceuticalForm = pharmaceuticalForm;
	m_DeliveryAdviceLine->m_PharmaceuticalForm.setClean();
}

void DeliveryAdviceLineMapperBase::setBasePrice(const basar::Decimal& basePrice)
{
	m_DeliveryAdviceLine->m_BasePrice = basePrice;
	m_DeliveryAdviceLine->m_BasePrice.setClean();
}

void DeliveryAdviceLineMapperBase::setPharmacySellPrice(const basar::Decimal& pharmacySellPrice)
{
	m_DeliveryAdviceLine->m_PharmacySellPrice = pharmacySellPrice;
	m_DeliveryAdviceLine->m_PharmacySellPrice.setClean();
}

void DeliveryAdviceLineMapperBase::setQuantityFeeCalculation(const basar::Int32 qtyFeeCalculation)
{
    m_DeliveryAdviceLine->m_QuantityFeeCalculation = qtyFeeCalculation;
    m_DeliveryAdviceLine->m_QuantityFeeCalculation.setClean();
}

void DeliveryAdviceLineMapperBase::setPrintedPricePerPiece(const basar::Decimal& printedPricePerPiece)
{
    m_DeliveryAdviceLine->m_PrintedPricePerPiece = printedPricePerPiece;
    m_DeliveryAdviceLine->m_PrintedPricePerPiece.setClean();
}

void DeliveryAdviceLineMapperBase::setLineValue(const basar::Decimal& lineValue)
{
    m_DeliveryAdviceLine->m_LineValue = lineValue;
    m_DeliveryAdviceLine->m_LineValue.setClean();
}

void DeliveryAdviceLineMapperBase::setLineFee(const basar::Decimal & lineFee)
{
    m_DeliveryAdviceLine->m_LineFee = lineFee;
    m_DeliveryAdviceLine->m_LineFee.setClean();
}

void DeliveryAdviceLineMapperBase::setPackageFee(const basar::Decimal & packageFee)
{
    m_DeliveryAdviceLine->m_PackageFee = packageFee;
    m_DeliveryAdviceLine->m_PackageFee.setClean();
}

} // end namespace document
} // end namespace libcsc
