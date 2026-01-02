#include "discountbasevalue.h"

namespace libcsc
{
namespace discount
{
DiscountBaseValue::DiscountBaseValue()
{
}

basar::Int16 DiscountBaseValue::getBranchno() const
{   
    return m_BranchNo;
}

const basar::Int32 & DiscountBaseValue::getArticleNo() const
{
    return m_ArticleNo;
}

const basar::Date & DiscountBaseValue::getDateFrom() const
{
    return m_DateFrom;
}

const basar::Date & DiscountBaseValue::getDateTo() const
{
    return m_DateTo;
}

const basar::Decimal & DiscountBaseValue::getDiscountValuePct() const
{
	return m_DiscountValuePct;
}

const basar::Int32 &		DiscountBaseValue::getDiscountGrpNo	(  ) const
{
	return m_DiscountGrpNo ;
}

const basar::VarString &	DiscountBaseValue::getPharmacyGrpId	(  ) const
{
	return m_PharmacyGrpId ;
}

const basar::VarString &	DiscountBaseValue::getPharmGrpExcl_1	(  ) const
{
	return m_PharmGrpExcl_1 ;
}

const basar::VarString &	DiscountBaseValue::getPharmGrpExcl_2	(  ) const
{
	return m_PharmGrpExcl_2 ;
}

const basar::VarString &	DiscountBaseValue::getPharmGrpExcl_3	(  ) const
{
	return m_PharmGrpExcl_3 ;
}

const basar::Int32 &		DiscountBaseValue::getCustomerNo		(  ) const
{
	return m_CustomerNo ;
}

const basar::Int32 &		DiscountBaseValue::getManufacturerNo	(  ) const
{
	return m_ManufacturerNo ;
}

const basar::Int32 &		DiscountBaseValue::getGrpDiscountType	(  ) const
{
	return m_GrpDiscountType ;
}

const basar::Int32 &		DiscountBaseValue::getBaseQty			(  ) const
{
	return m_BaseQty ;
}

const basar::Int32 &		DiscountBaseValue::getDiscountSpec		(  ) const
{
	return m_DiscountSpec ;
}

const basar::Int32 &		DiscountBaseValue::getDiscountType		(  ) const
{
	return m_DiscountType ;
}

const basar::Int32 &		DiscountBaseValue::getDiscountQty		(  ) const
{
	return m_DiscountQty ;
}

const basar::Decimal &		DiscountBaseValue::getDiscountQtyPct() const
{
    return m_DiscountQtyPct;
}

const basar::Decimal &		DiscountBaseValue::getSurchargePct		(  ) const
{
	return m_SurchargePct ;
}

const basar::Decimal &		DiscountBaseValue::getFixedPrice		(  ) const
{
	return m_FixedPrice ;
}

const basar::Decimal &		DiscountBaseValue::getRefundPct		(  ) const
{
	return m_RefundPct ;
}

const basar::VarString &	DiscountBaseValue::getInternalDiscount (  ) const
{
	return m_InternalDiscount ;
}

const basar::Int32 &		DiscountBaseValue::getDiscountArticle	(  ) const
{
	return m_DiscountArticle ;
}

const basar::Decimal &		DiscountBaseValue::getDiscountArticlePrice ( ) const
{
	return m_DiscountArticlePrice ;
}

const basar::Decimal &		DiscountBaseValue::getBaseValue		(  ) const
{
	return m_BaseValue ;
}

const basar::Int32 &		DiscountBaseValue::getBaseMultStdQty	(  ) const
{
	return m_BaseMultStdQty ;
}

const basar::VarString &	DiscountBaseValue::getNoMultipleQty	(  ) const
{
	return m_NoMultipleQty ;
}

const basar::Decimal &		DiscountBaseValue::getFixedDiscountVal (  ) const
{
	return m_FixedDiscountVal ;
}

const basar::Int32 &		DiscountBaseValue::getArtCategoryNo	(  ) const
{
	return m_ArtCategoryNo ;
}

const basar::Int32 &		DiscountBaseValue::getPaymentTargetNo	(  ) const
{
	return m_PaymentTargetNo ;
}

const basar::Decimal &		DiscountBaseValue::getGrossProfitPct	(  ) const
{
	return m_GrossProfitPct ;
}

const basar::VarString &	DiscountBaseValue::getAddOnDiscountOk	(  ) const
{
	return m_AddOnDiscountOk ;
}

const basar::VarString &	DiscountBaseValue::getPaymentTermType	(  ) const
{
	return m_PaymentTermType ;
}

const basar::Int32 &		DiscountBaseValue::getTargetQty		(  ) const
{
	return m_TargetQty ;
}

const basar::Decimal &		DiscountBaseValue::getExceedancePct	(  ) const
{
	return m_ExceedancePct ;
}

const basar::Int32 &		DiscountBaseValue::getRefundType		(  ) const
{
	return m_RefundType ;
}

const basar::Int32 &		DiscountBaseValue::getArticleNoPack	(  ) const
{
	return m_ArticleNoPack ;
}

const basar::Decimal &		DiscountBaseValue::getRefundValue		(  ) const
{
	return m_RefundValue ;
}

const basar::Int16 &		DiscountBaseValue::getPromotionNo		(  ) const
{
	return m_PromotionNo ;
}

const basar::Int32 &		DiscountBaseValue::getMaxQty			(  ) const
{
	return m_MaxQty ;
}

const basar::VarString &	DiscountBaseValue::getTurnoverCalcImpact( ) const
{
	return m_TurnoverCalcImpact ;
}

const basar::VarString &	DiscountBaseValue::getAddOnDiscount	(  ) const
{
	return m_AddOnDiscount ;
}

const basar::VarString &	DiscountBaseValue::getMonthlyDiscount	(  ) const
{
	return m_MonthlyDiscount ;
}

const basar::VarString &	DiscountBaseValue::getPromotionName	() const
{
	return m_PromotionName;
}

void DiscountBaseValue::setFixedPrice(const basar::Decimal& fixedPrice)
{
	m_FixedPrice = fixedPrice;
}

#define INT_TO_STRM(strm,x) if( false == x.isUnset() && 0 != x ) { strm << #x << "=<" << x << ">, "; }
#define DEC_TO_STRM(strm,x) if( false == x.isUnset() && basar::Decimal( 0 ) != x ) { strm << #x << "=<" << x << ">, "; }
#define STR_TO_STRM(strm,x) if( false == x.isUnset() && x != "" ) { strm << #x << "=<" << x << ">, "; }

std::ostream & DiscountBaseValue::toStream( std::ostream & strm /* = std::cout */ ) const
{
    INT_TO_STRM( strm, m_BranchNo )
    INT_TO_STRM( strm, m_ArticleNo )
	DEC_TO_STRM( strm, m_DiscountValuePct )
	INT_TO_STRM( strm, m_DiscountGrpNo )
	STR_TO_STRM( strm, m_PharmacyGrpId )
	STR_TO_STRM( strm, m_PharmGrpExcl_1 )
	STR_TO_STRM( strm, m_PharmGrpExcl_2 )
	STR_TO_STRM( strm, m_PharmGrpExcl_3 )
	INT_TO_STRM( strm, m_CustomerNo )
	INT_TO_STRM( strm, m_ManufacturerNo )
	INT_TO_STRM( strm, m_GrpDiscountType )
	INT_TO_STRM( strm, m_BaseQty )
	INT_TO_STRM( strm, m_DiscountSpec )
	INT_TO_STRM( strm, m_DiscountType )
	INT_TO_STRM( strm, m_DiscountQty )
    DEC_TO_STRM(strm, m_DiscountQtyPct)
    DEC_TO_STRM( strm, m_DiscountValuePct )
	DEC_TO_STRM( strm, m_SurchargePct )
	DEC_TO_STRM( strm, m_FixedPrice )
	DEC_TO_STRM( strm, m_RefundPct )
	STR_TO_STRM( strm, m_InternalDiscount )
	INT_TO_STRM( strm, m_DiscountArticle )
	DEC_TO_STRM( strm, m_DiscountArticlePrice )
	DEC_TO_STRM( strm, m_BaseValue )
	INT_TO_STRM( strm, m_BaseMultStdQty )
	STR_TO_STRM( strm, m_NoMultipleQty )
	DEC_TO_STRM( strm, m_FixedDiscountVal )
	INT_TO_STRM( strm, m_ArtCategoryNo )
	INT_TO_STRM( strm, m_PaymentTargetNo )
	DEC_TO_STRM( strm, m_GrossProfitPct )
	STR_TO_STRM( strm, m_AddOnDiscountOk )
	STR_TO_STRM( strm, m_PaymentTermType )
	INT_TO_STRM( strm, m_TargetQty )
	DEC_TO_STRM( strm, m_ExceedancePct )
	INT_TO_STRM( strm, m_RefundType )
	INT_TO_STRM( strm, m_ArticleNoPack )
	DEC_TO_STRM( strm, m_RefundValue )
	INT_TO_STRM( strm, m_PromotionNo )
	INT_TO_STRM( strm, m_MaxQty )
	STR_TO_STRM( strm, m_TurnoverCalcImpact )
	STR_TO_STRM( strm, m_AddOnDiscount )
	STR_TO_STRM( strm, m_MonthlyDiscount )
	STR_TO_STRM( strm, m_PromotionName )

	//strm << "articleNo=<" << m_ArticleNo << ">";
	//strm << ", discountValuePct=<" << m_DiscountValuePct << ">";
	//strm << ", discountGrpNo=<" << m_DiscountGrpNo << ">";
	//strm << ", pharmacyGrpId=<" << m_PharmacyGrpId << ">";
	//strm << ", pharmGrpExcl_1=<" << m_PharmGrpExcl_1 << ">";
	//strm << ", pharmGrpExcl_2=<" << m_PharmGrpExcl_2 << ">";
	//strm << ", pharmGrpExcl_3=<" << m_PharmGrpExcl_3 << ">";
	//strm << ", customerNo=<" << m_CustomerNo << ">";
	//strm << ", manufacturerNo=<" << m_ManufacturerNo << ">";
	//strm << ", grpDiscountType=<" << m_GrpDiscountType << ">";
	//strm << ", baseQty=<" << m_BaseQty << ">";
	//strm << ", discountSpec=<" << m_DiscountSpec << ">";
	//strm << ", discountType=<" << m_DiscountType << ">";
	//strm << ", discountQty=<" << m_DiscountQty << ">";
	//strm << ", discountQtyPct=<" << m_DiscountQtyPct << ">";
	//strm << ", surchargePct=<" << m_SurchargePct << ">";
	//strm << ", fixedPrice=<" << m_FixedPrice << ">";
	//strm << ", refundPct=<" << m_RefundPct << ">";
	//strm << ", internalDiscount=<" << m_InternalDiscount << ">";
	//strm << ", discountArticle=<" << m_DiscountArticle << ">";
	//strm << ", discountArticlePrice=<" << m_DiscountArticlePrice << ">";
	//strm << ", baseValue=<" << m_BaseValue << ">";
	//strm << ", baseMultStdQty=<" << m_BaseMultStdQty << ">";
	//strm << ", noMultipleQty=<" << m_NoMultipleQty << ">";
	//strm << ", fixedDiscountVal=<" << m_FixedDiscountVal << ">";
	//strm << ", artCategoryNo=<" << m_ArtCategoryNo << ">";
	//strm << ", paymentTargetNo=<" << m_PaymentTargetNo << ">";
	//strm << ", grossProfitPct=<" << m_GrossProfitPct << ">";
	//strm << ", addOnDiscountOk=<" << m_AddOnDiscountOk << ">";
	//strm << ", paymentTermType=<" << m_PaymentTermType << ">";
	//strm << ", targetQty=<" << m_TargetQty << ">";
	//strm << ", exceedancePct=<" << m_ExceedancePct << ">";
	//strm << ", refundType=<" << m_RefundType << ">";
	//strm << ", articleNoPack=<" << m_ArticleNoPack << ">";
	//strm << ", refundValue=<" << m_RefundValue << ">";
	//strm << ", promotionNo=<" << m_PromotionNo << ">";
	//strm << ", maxQty=<" << m_MaxQty << ">";
	//strm << ", turnoverCalcImpact=<" << m_TurnoverCalcImpact << ">";
	//strm << ", addOnDiscount=<" << m_AddOnDiscount << ">";
	//strm << ", monthlyDiscount=<" << m_MonthlyDiscount << ">";
	return strm;	
}

} // end namespace discount
} // end namespace libcsc

