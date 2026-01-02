#include <document/deliveryadvice/deliveryadviceline/deliveryadviceline.h>
#include <document/deliveryadvice/deliveryadviceremarks.h>

namespace libcsc {
namespace document {

DeliveryAdviceLine::DeliveryAdviceLine()
{
}

DeliveryAdviceLine::~DeliveryAdviceLine()
{
}

const basar::Int16& DeliveryAdviceLine::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& DeliveryAdviceLine::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date& DeliveryAdviceLine::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::VarString& DeliveryAdviceLine::getDeliveryAdviceNo() const
{
	return m_DeliveryAdviceNo;
}

const basar::Int32& DeliveryAdviceLine::getDeliveryAdvicePosNo() const
{
	return m_DeliveryAdvicePosNo;
}

const basar::Int32& DeliveryAdviceLine::getPharmosOrderNo() const
{
	return m_PharmosOrderNo;
}

const basar::Int32& DeliveryAdviceLine::getPharmosOrderPosNo() const
{
	return m_PharmosOrderPosNo;
}

const basar::Int32& DeliveryAdviceLine::getCscOrderPosNo() const
{
	return m_CscOrderPosNo;
}

const basar::Int32& DeliveryAdviceLine::getArticleNo() const
{
	return m_ArticleNo;
}

const basar::VarString& DeliveryAdviceLine::getArticleCode() const
{
	return m_ArticleCode;
}

const basar::Int16& DeliveryAdviceLine::getCodeType() const
{
	return m_CodeType;
}

const basar::Int32& DeliveryAdviceLine::getQuantityOrdered() const
{
	return m_QuantityOrdered;
}

const basar::Int32& DeliveryAdviceLine::getQuantityConfirmed() const
{
	return m_QuantityConfirmed;
}

const basar::Int32& DeliveryAdviceLine::getQuantityRebateInKind() const
{
	return m_QuantityRebateInKind;
}

const basar::Int32& DeliveryAdviceLine::getQuantityInvoiced() const
{
	return m_QuantityInvoiced;
}

const basar::VarString& DeliveryAdviceLine::getLineReference() const
{
	return m_LineReference;
}

const basar::VarString& DeliveryAdviceLine::getVat() const
{
	return m_Vat;
}

const basar::Decimal& DeliveryAdviceLine::getVatPercentage() const
{
	return m_VatPercentage;
}

const basar::Decimal& DeliveryAdviceLine::getInvoicedPrice() const
{
	return m_InvoicedPrice;
}

const basar::Decimal& DeliveryAdviceLine::getLogisticServiceCost() const
{
	return m_LogisticServiceCost;
}

const basar::Decimal& DeliveryAdviceLine::getMinLogisticServiceCostValue() const
{
	return m_MinLogisticServiceCostValue;
}

DeliveryAdviceLine::DeliveryAdviceLineTypeEnum DeliveryAdviceLine::getLineType() const
{
	return static_cast<DeliveryAdviceLineTypeEnum>(m_LineType.get());
}

const basar::VarString& DeliveryAdviceLine::getArticleName() const
{
	return m_ArticleName;
}

const basar::VarString& DeliveryAdviceLine::getArticleUnit() const
{
	return m_ArticleUnit;
}

const basar::VarString& DeliveryAdviceLine::getPharmaceuticalForm() const
{
	return m_PharmaceuticalForm;
}

const basar::Decimal& DeliveryAdviceLine::getBasePrice() const
{
	return m_BasePrice;
}

const basar::Decimal& DeliveryAdviceLine::getPharmacySellPrice() const
{
	return m_PharmacySellPrice;
}

const DeliveryAdviceRemarksCollectionPtr DeliveryAdviceLine::getRemarksCollection() const
{
	return m_Remarks;
}

const DeliveryAdviceLineDiscountCollectionPtr DeliveryAdviceLine::getDiscountCollection() const
{
	return m_Discounts;
}

const DeliveryAdviceLineDetailsCollectionPtr DeliveryAdviceLine::getDetailsCollection() const
{
	return m_Details;
}

const DeliveryAdviceLineReturnCollectionPtr DeliveryAdviceLine::getReturnCollection() const
{
	return m_Return;
}

const DeliveryAdviceLineIbtLinkPtr DeliveryAdviceLine::getIbtLink() const
{
	return m_IbtLink;
}

const DeliveryAdviceLineExtrasATPtr DeliveryAdviceLine::getExtrasAT() const
{
	return m_ExtrasAT;
}

const basar::Int32& DeliveryAdviceLine::getQuantityFeeCalculation() const
{
    return m_QuantityFeeCalculation;
}

const basar::Decimal& DeliveryAdviceLine::getPrintedPricePerPiece() const
{
    return m_PrintedPricePerPiece;
}

const basar::Decimal& DeliveryAdviceLine::getLineValue() const
{
    return m_LineValue;
}

const basar::Decimal& DeliveryAdviceLine::getLineFee() const
{
    return m_LineFee;
}

const basar::Decimal& DeliveryAdviceLine::getPackageFee() const
{
    return m_PackageFee;
}

} // namespace document
} // namespace libcsc
