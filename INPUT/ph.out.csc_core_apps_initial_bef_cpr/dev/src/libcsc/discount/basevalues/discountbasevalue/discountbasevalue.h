#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_H

#include <datatypes/decimal.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/date.h>
#include <iostream>

namespace libcsc
{
namespace discount
{
class DiscountBaseValue
{
	// because of OR mapping
	friend class DiscountBaseValueMapperBase;

public:
	DiscountBaseValue();

          basar::Int16		    getBranchno         (  ) const;
    const basar::Int32 &		getArticleNo		(  ) const;
    const basar::Date &	        getDateFrom         (  ) const;
    const basar::Date &	        getDateTo           (  ) const;
	const basar::Int32 &		getDiscountGrpNo	(  ) const;
	const basar::VarString &	getPharmacyGrpId	(  ) const;
	const basar::VarString &	getPharmGrpExcl_1	(  ) const;
	const basar::VarString &	getPharmGrpExcl_2	(  ) const;
	const basar::VarString &	getPharmGrpExcl_3	(  ) const;
	const basar::Int32 &		getCustomerNo		(  ) const;
	const basar::Int32 &		getManufacturerNo	(  ) const;
	const basar::Int32 &		getGrpDiscountType	(  ) const;
	const basar::Int32 &		getBaseQty			(  ) const;
	const basar::Int32 &		getDiscountSpec		(  ) const;
	const basar::Int32 &		getDiscountType		(  ) const;
	const basar::Int32 &		getDiscountQty		(  ) const;
    const basar::Decimal &		getDiscountQtyPct   (  ) const;
    const basar::Decimal &		getDiscountValuePct (  ) const;
	const basar::Decimal &		getSurchargePct		(  ) const;
	const basar::Decimal &		getFixedPrice		(  ) const;
	const basar::Decimal &		getRefundPct		(  ) const;
	const basar::VarString &	getInternalDiscount (  ) const;
	const basar::Int32 &		getDiscountArticle	(  ) const;
	const basar::Decimal &		getDiscountArticlePrice()const;
	const basar::Decimal &		getBaseValue		(  ) const;
	const basar::Int32 &		getBaseMultStdQty	(  ) const;
	const basar::VarString &	getNoMultipleQty	(  ) const;
	const basar::Decimal &		getFixedDiscountVal (  ) const;
	const basar::Int32 &		getArtCategoryNo	(  ) const;
	const basar::Int32 &		getPaymentTargetNo	(  ) const;
	const basar::Decimal &		getGrossProfitPct	(  ) const;
	const basar::VarString &	getAddOnDiscountOk	(  ) const;
	const basar::VarString &	getPaymentTermType	(  ) const;
	const basar::Int32 &		getTargetQty		(  ) const;
	const basar::Decimal &		getExceedancePct	(  ) const;
	const basar::Int32 &		getRefundType		(  ) const;
	const basar::Int32 &		getArticleNoPack	(  ) const;
	const basar::Decimal &		getRefundValue		(  ) const;
	const basar::Int16 &		getPromotionNo		(  ) const;
	const basar::Int32 &		getMaxQty			(  ) const;
	const basar::VarString &	getTurnoverCalcImpact( ) const;
	const basar::VarString &	getAddOnDiscount	(  ) const;
	const basar::VarString &	getMonthlyDiscount	(  ) const;
	const basar::VarString &	getPromotionName	(  ) const;
	void						setFixedPrice       ( const basar::Decimal& fixedPrice );
	
	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	// enthält werte aus tabelle discount

private:
    libcsc::Int16		m_BranchNo;
    libcsc::Int32		m_ArticleNo;
    libcsc::Date        m_DateFrom;
    libcsc::Date        m_DateTo;
	libcsc::Int32		m_DiscountGrpNo;
	libcsc::VarString 	m_PharmacyGrpId;
	libcsc::VarString 	m_PharmGrpExcl_1;
	libcsc::VarString 	m_PharmGrpExcl_2;
	libcsc::VarString 	m_PharmGrpExcl_3;
	libcsc::Int32		m_CustomerNo;
	libcsc::Int32		m_ManufacturerNo;
	libcsc::Int32		m_GrpDiscountType;
	libcsc::Int32		m_BaseQty;
	libcsc::Int32		m_DiscountSpec;
	libcsc::Int32		m_DiscountType;
	libcsc::Int32		m_DiscountQty;
	libcsc::Decimal 	m_DiscountQtyPct;
    libcsc::Decimal 	m_DiscountValuePct;
	libcsc::Decimal 	m_SurchargePct;
	libcsc::Decimal 	m_FixedPrice;
	libcsc::Decimal 	m_RefundPct;
	libcsc::VarString	m_InternalDiscount;
	libcsc::Int32		m_DiscountArticle;
	libcsc::Decimal 	m_DiscountArticlePrice;
	libcsc::Decimal 	m_BaseValue;
	libcsc::Int32		m_BaseMultStdQty;
	libcsc::VarString 	m_NoMultipleQty;
	libcsc::Decimal 	m_FixedDiscountVal;
	libcsc::Int32		m_ArtCategoryNo;
	libcsc::Int32		m_PaymentTargetNo;
	libcsc::Decimal 	m_GrossProfitPct;
	libcsc::VarString 	m_AddOnDiscountOk;
	libcsc::VarString 	m_PaymentTermType;
	libcsc::Int32		m_TargetQty;
	libcsc::Decimal 	m_ExceedancePct;
	libcsc::Int32		m_RefundType;
	libcsc::Int32		m_ArticleNoPack;
	libcsc::Decimal 	m_RefundValue;
	libcsc::Int16		m_PromotionNo;
	libcsc::Int32		m_MaxQty;
	libcsc::VarString 	m_TurnoverCalcImpact;
	libcsc::VarString 	m_AddOnDiscount;
	libcsc::VarString 	m_MonthlyDiscount;
	libcsc::VarString	m_PromotionName;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::DiscountBaseValue & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_H
