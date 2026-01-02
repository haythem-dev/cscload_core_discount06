#include "discountbasevaluemapperbase.h"
#include "discountbasevalue.h"

namespace libcsc
{
namespace discount
{
DiscountBaseValueMapperBase::DiscountBaseValueMapperBase( DiscountBaseValuePtr value )
: m_Value( value )
{
}

DiscountBaseValueMapperBase::~DiscountBaseValueMapperBase()
{
}

void DiscountBaseValueMapperBase::map()
{
	doMap();
}

//const basar::VarString DiscountBaseValueMapperBase::serialize() const
//{
//	return doSerialize();
//}


void DiscountBaseValueMapperBase::setBranchNo( const basar::Int16 branchNo )
{
    m_Value->m_BranchNo = branchNo;
    m_Value->m_BranchNo.setClean();
}

void DiscountBaseValueMapperBase::setArticleNo( const basar::Int32 articleNo )
{
	m_Value->m_ArticleNo = articleNo;
	m_Value->m_ArticleNo.setClean();
}

void DiscountBaseValueMapperBase::setDateFrom( const basar::Date& dateFrom)
{
    m_Value->m_DateFrom = dateFrom;
    m_Value->m_DateFrom.setClean();
}

void DiscountBaseValueMapperBase::setDateTo( const basar::Date& dateTo)
{
    m_Value->m_DateTo = dateTo;
    m_Value->m_DateTo.setClean();
}

void DiscountBaseValueMapperBase::setDiscountGrpNo	( const basar::Int32		discountGrpNo )
{
	m_Value->m_DiscountGrpNo = discountGrpNo;
	m_Value->m_DiscountGrpNo.setClean();
}

void DiscountBaseValueMapperBase::setPharmacyGrpId	( const basar::VarString &	pharmacyGrpId )
{
	m_Value->m_PharmacyGrpId = pharmacyGrpId;
	m_Value->m_PharmacyGrpId.setClean();
}

void DiscountBaseValueMapperBase::setPharmGrpExcl_1	( const basar::VarString &	pharmGrpExcl_1 )
{
	m_Value->m_PharmGrpExcl_1 = pharmGrpExcl_1;
	m_Value->m_PharmGrpExcl_1.setClean();
}

void DiscountBaseValueMapperBase::setPharmGrpExcl_2	( const basar::VarString &	pharmGrpExcl_2 )
{
	m_Value->m_PharmGrpExcl_2 = pharmGrpExcl_2;
	m_Value->m_PharmGrpExcl_2.setClean();
}

void DiscountBaseValueMapperBase::setPharmGrpExcl_3	( const basar::VarString &	pharmGrpExcl_3 )
{
	m_Value->m_PharmGrpExcl_3 = pharmGrpExcl_3;
	m_Value->m_PharmGrpExcl_3.setClean();
}

void DiscountBaseValueMapperBase::setCustomerNo		( const basar::Int32		customerNo )
{
	m_Value->m_CustomerNo = customerNo;
	m_Value->m_CustomerNo.setClean();
}

void DiscountBaseValueMapperBase::setManufacturerNo	( const basar::Int32		manufacturerNo )
{
	m_Value->m_ManufacturerNo = manufacturerNo;
	m_Value->m_ManufacturerNo.setClean();
}
	
void DiscountBaseValueMapperBase::setGrpDiscountType	( const basar::Int16		grpDiscountType )
{
	m_Value->m_GrpDiscountType = grpDiscountType;
	m_Value->m_GrpDiscountType.setClean();
}

void DiscountBaseValueMapperBase::setBaseQty			( const basar::Int32		baseQty )
{
	m_Value->m_BaseQty = baseQty;
	m_Value->m_BaseQty.setClean();
}

void DiscountBaseValueMapperBase::setDiscountSpec	( const basar::Int16		discountSpec )
{
	m_Value->m_DiscountSpec = discountSpec;
	m_Value->m_DiscountSpec.setClean();
}

void DiscountBaseValueMapperBase::setDiscountType	( const basar::Int16		discountType )
{
	m_Value->m_DiscountType = discountType;
	m_Value->m_DiscountType.setClean();
}

void DiscountBaseValueMapperBase::setDiscountQty		( const basar::Int16		discountQty )
{
	m_Value->m_DiscountQty = discountQty;
	m_Value->m_DiscountQty.setClean();
}

void DiscountBaseValueMapperBase::setDiscountQtyPct(const basar::Decimal &	discountQtyPct)
{
    m_Value->m_DiscountQtyPct = discountQtyPct;
    m_Value->m_DiscountQtyPct.setClean();
}

void DiscountBaseValueMapperBase::setDiscountValuePct(const basar::Decimal &	discountValuePct)
{
    m_Value->m_DiscountValuePct = discountValuePct;
    m_Value->m_DiscountValuePct.setClean();
}

void DiscountBaseValueMapperBase::setSurchargePct	( const basar::Decimal &	surchargePct )
{
	m_Value->m_SurchargePct = surchargePct;
	m_Value->m_SurchargePct.setClean();
}

void DiscountBaseValueMapperBase::setFixedPrice		( const basar::Decimal &	fixedPrice )
{
	m_Value->m_FixedPrice = fixedPrice;
	m_Value->m_FixedPrice.setClean();
}

void DiscountBaseValueMapperBase::setRefundPct		( const basar::Decimal &	refundPct )
{
	m_Value->m_RefundPct = refundPct;
	m_Value->m_RefundPct.setClean();
}

void DiscountBaseValueMapperBase::setInternalDiscount( const basar::VarString &		internalDiscount )
{
	m_Value->m_InternalDiscount = internalDiscount;
	m_Value->m_InternalDiscount.setClean();
}

void DiscountBaseValueMapperBase::setDiscountArticle	( const basar::Int32		discountArticle )
{
	m_Value->m_DiscountArticle = discountArticle;
	m_Value->m_DiscountArticle.setClean();
}

void DiscountBaseValueMapperBase::setDiscountArticlePrice	( const basar::Decimal &		discountArticlePrice )
{
	m_Value->m_DiscountArticlePrice = discountArticlePrice;
	m_Value->m_DiscountArticlePrice.setClean();
}

void DiscountBaseValueMapperBase::setBaseValue		( const basar::Decimal &	baseValue )
{
	m_Value->m_BaseValue = baseValue;
	m_Value->m_BaseValue.setClean();
}

void DiscountBaseValueMapperBase::setBaseMultStdQty	( const basar::Int32		baseMultStdQty )
{
	m_Value->m_BaseMultStdQty = baseMultStdQty;
	m_Value->m_BaseMultStdQty.setClean();
}

void DiscountBaseValueMapperBase::setNoMultipleQty	( const basar::VarString &	noMultipleQty )
{
	m_Value->m_NoMultipleQty = noMultipleQty;
	m_Value->m_NoMultipleQty.setClean();
}

void DiscountBaseValueMapperBase::setFixedDiscountVal( const basar::Decimal &	fixedDiscountVal )
{
	m_Value->m_FixedDiscountVal = fixedDiscountVal;
	m_Value->m_FixedDiscountVal.setClean();
}

void DiscountBaseValueMapperBase::setArtCategoryNo	( const basar::Int32		artCategoryNo )
{
	m_Value->m_ArtCategoryNo = artCategoryNo;
	m_Value->m_ArtCategoryNo.setClean();
}

void DiscountBaseValueMapperBase::setPaymentTargetNo	( const basar::Int16		paymentTargetNo )
{
	m_Value->m_PaymentTargetNo = paymentTargetNo;
	m_Value->m_PaymentTargetNo.setClean();
}

void DiscountBaseValueMapperBase::setGrossProfitPct	( const basar::Decimal &	grossProfitPct )
{
	m_Value->m_GrossProfitPct = grossProfitPct;
	m_Value->m_GrossProfitPct.setClean();
}

void DiscountBaseValueMapperBase::setAddOnDiscountOk	( const basar::VarString &	addOnDiscountOk )
{
	m_Value->m_AddOnDiscountOk = addOnDiscountOk;
	m_Value->m_AddOnDiscountOk.setClean();
}

void DiscountBaseValueMapperBase::setPaymentTermType	( const basar::VarString &	paymentTermType )
{
	m_Value->m_PaymentTermType = paymentTermType;
	m_Value->m_PaymentTermType.setClean();
}

void DiscountBaseValueMapperBase::setTargetQty		( const basar::Int32		targetQty )
{
	m_Value->m_TargetQty = targetQty;
	m_Value->m_TargetQty.setClean();
}

void DiscountBaseValueMapperBase::setExceedancePct	( const basar::Decimal &	exceedancePct )
{
	m_Value->m_ExceedancePct = exceedancePct;
	m_Value->m_ExceedancePct.setClean();
}

void DiscountBaseValueMapperBase::setRefundType		( const basar::Int16		refundType )
{
	m_Value->m_RefundType = refundType;
	m_Value->m_RefundType.setClean();
}

void DiscountBaseValueMapperBase::setArticleNoPack	( const basar::Int32		articleNoPack )
{
	m_Value->m_ArticleNoPack = articleNoPack;
	m_Value->m_ArticleNoPack.setClean();
}

void DiscountBaseValueMapperBase::setRefundValue		( const basar::Decimal &	refundValue )
{
	m_Value->m_RefundValue = refundValue;
	m_Value->m_RefundValue.setClean();
}

void DiscountBaseValueMapperBase::setPromotionNo		( const basar::Int16		promotionNo )
{
	m_Value->m_PromotionNo = promotionNo;
	m_Value->m_PromotionNo.setClean();
}

void DiscountBaseValueMapperBase::setMaxQty			( const basar::Int32		maxQty )
{
	m_Value->m_MaxQty = maxQty;
	m_Value->m_MaxQty.setClean();
}

void DiscountBaseValueMapperBase::setTurnoverCalcImpact(const basar::VarString &	turnoverCalcImpact )
{
	m_Value->m_TurnoverCalcImpact = turnoverCalcImpact;
	m_Value->m_TurnoverCalcImpact.setClean();
}

void DiscountBaseValueMapperBase::setAddOnDiscount	( const basar::VarString &	addOnDiscount )
{
	m_Value->m_AddOnDiscount = addOnDiscount;
	m_Value->m_AddOnDiscount.setClean();
}

void DiscountBaseValueMapperBase::setMonthlyDiscount	( const basar::VarString &	monthlyDiscount )
{
	m_Value->m_MonthlyDiscount = monthlyDiscount;
	m_Value->m_MonthlyDiscount.setClean();
}

void DiscountBaseValueMapperBase::setPromotionName	( const basar::VarString &	promotionName )
{
	m_Value->m_PromotionName = promotionName;
	m_Value->m_PromotionName.setClean();
}

} // end namespace discount
} // end namespace libcsc

