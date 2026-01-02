#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_MAPPER_BASE_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_MAPPER_BASE_H

#include <discount/basevalues/discountbasevalue/discountbasevalueptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueMapperBase
{
public:
	DiscountBaseValueMapperBase( DiscountBaseValuePtr value );

	void map();
	//const basar::VarString serialize() const;

protected:
	virtual ~DiscountBaseValueMapperBase();

	virtual void doMap() = 0;
	//virtual const basar::VarString doSerialize() const = 0;

    void setBranchNo        ( const basar::Int16		branchNo        );
    void setArticleNo		( const basar::Int32		articleNo       );
    void setDateFrom        ( const basar::Date&        dateFrom        );
    void setDateTo          ( const basar::Date&        dateTo          );
	void setDiscountGrpNo	( const basar::Int32		discountGrpNo   );
	void setPharmacyGrpId	( const basar::VarString &	pharmacyGrpId   );
	void setPharmGrpExcl_1	( const basar::VarString &	pharmGrpExcl_1  );
	void setPharmGrpExcl_2	( const basar::VarString &	pharmGrpExcl_2  );
	void setPharmGrpExcl_3	( const basar::VarString &	pharmGrpExcl_3  );
	void setCustomerNo		( const basar::Int32		customerNo      );
	void setManufacturerNo	( const basar::Int32		manufacturerNo  );
	void setGrpDiscountType	( const basar::Int16		grpDiscountType );
	void setBaseQty			( const basar::Int32		baseQty );
	void setDiscountSpec	( const basar::Int16		discountSpec );
	void setDiscountType	( const basar::Int16		discountType );
	void setDiscountQty		( const basar::Int16		discountQty );
	void setDiscountQtyPct	( const basar::Decimal &	discountQtyPct );
    void setDiscountValuePct(const basar::Decimal &	discountQtyPct );
	void setSurchargePct	( const basar::Decimal &	surchargePct );
	void setFixedPrice		( const basar::Decimal &	fixedPrice );
	void setRefundPct		( const basar::Decimal &	refundPct );
	void setInternalDiscount( const basar::VarString &	internalDiscount );
	void setDiscountArticle	( const basar::Int32		discountArticle );
	void setDiscountArticlePrice(const basar::Decimal &	discountArticlePrice );
	void setBaseValue		( const basar::Decimal &	baseValue );
	void setBaseMultStdQty	( const basar::Int32		baseMultStdQty );
	void setNoMultipleQty	( const basar::VarString &	noMultipleQty );
	void setFixedDiscountVal( const basar::Decimal &	fixedDiscountVal );
	void setArtCategoryNo	( const basar::Int32		artCategoryNo );
	void setPaymentTargetNo	( const basar::Int16		paymentTargetNo );
	void setGrossProfitPct	( const basar::Decimal &	grossProfitPct );
	void setAddOnDiscountOk	( const basar::VarString &	addOnDiscountOk );
	void setPaymentTermType	( const basar::VarString &	paymentTermType );
	void setTargetQty		( const basar::Int32		targetQty );
	void setExceedancePct	( const basar::Decimal &	exceedancePct );
	void setRefundType		( const basar::Int16		refundType );
	void setArticleNoPack	( const basar::Int32		articleNoPack );
	void setRefundValue		( const basar::Decimal &	refundValue );
	void setPromotionNo		( const basar::Int16		promotionNo );
	void setMaxQty			( const basar::Int32		maxQty );
	void setTurnoverCalcImpact(const basar::VarString &	turnoverCalcImpact );
	void setAddOnDiscount	( const basar::VarString &	addOnDiscount );
	void setMonthlyDiscount	( const basar::VarString &	monthlyDiscount );
	void setPromotionName	( const basar::VarString &	promotionName );

private:
	DiscountBaseValuePtr	m_Value;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_MAPPER_BASE_H
