#ifndef GUARD_LIBCSC_UNITTEST_DISCOUNT_BASE_VALUE_MAPPER_STUB_H
#define GUARD_LIBCSC_UNITTEST_DISCOUNT_BASE_VALUE_MAPPER_STUB_H

#include <discount/basevalues/discountbasevalue/discountbasevaluemapperbase.h>

/*	behaves like a DiscountBaseValueSQLMapper
	To get a DicountBaseValue for testing purposes, use:

	DiscountBaseValuePtr baseValue( new DiscountBaseValue() );
	DiscountBaseValueMapperStub mapper( baseValue );
	mapper.setArticleNo( 4711 );
	mapper.setFixedPrice( 12.34 );
	...
	mapper.map();

	or

	DiscountBaseValuePtr baseValue( new DiscountBaseValue() );
	DiscountBaseValueMapperStub mapper( baseValue );
	mapper.setValuesFromText( "4711;1;..." );
	mapper.map();
*/

/*
Das sollten die für HR relevanten Felder aus der Tabelle “discount“ sein:

Articleno = PZN, auf die der Rabatt gewährt wird
Discountgrpno = Gruppe von Artikeln oder Herstellern, auf die der Rabatt gewährt wird
manufacturerno = Rabatt für alle Artikel dieses Herstellers, auf die der Rabatt gewährt wird

Customerno = Einschränkung des Rabatts auf bestimmte Kunden (Prio 1)
Pharmacygroupid = Einschränkung des Rabatts auf bestimmte Kundengruppen (Prio 2)
Pharmgrpexcluded = vom Rabatt ausgeschlossene Kundengruppe 1
pharmgrpexcl_2 = vom Rabatt ausgeschlossene Kundengruppe 2
pharmgrpexcl_3 = vom Rabatt ausgeschlossene Kundengruppe 3

Discountspec = WholeSale / WholeSale Industry / 

Baseqty = Bestellmenge, die mind. erreicht werden muss, damit Rabattsatz greift
base_value = Bestellwert, der mind. erreicht werden muss, damit Rabattsatz greift

Discountqty = Natra- Menge
Discountarticle = Natra- Artikel, wenn dieser vom Basis- Artikel abweicht
Discountvaluepct = Rabatt-% auf den Artikelpreis
Fixedprice = fester Artikelpreis

Refundpct = wird bei Natra- Übergabe ans Pharmos benötigt
monthlydiscount = nur 0 relevant (Monatsrabatte werden ausschließlich im Pharmos berrechnet)

*/

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
class DiscountBaseValueMapperStub : public libcsc::discount::DiscountBaseValueMapperBase
{
public:
	DiscountBaseValueMapperStub( 
		libcsc::discount::DiscountBaseValuePtr value
			);
	virtual ~DiscountBaseValueMapperStub();

	void setValuesFromText( const basar::VarString & line );

	void setArticleNo		( const basar::Int32		articleNo );
	void setDiscountGrpNo	( const basar::Int32		discountGrpNo );
	void setPharmacyGrpId	( const basar::VarString &	pharmacyGrpId );
	void setPharmGrpExcl_1	( const basar::VarString &	pharmGrpExcl_1 );
	void setPharmGrpExcl_2	( const basar::VarString &	pharmGrpExcl_2 );
	void setPharmGrpExcl_3	( const basar::VarString &	pharmGrpExcl_3 );
	void setCustomerNo		( const basar::Int32		customerNo );
	void setManufacturerNo	( const basar::Int32		manufacturerNo );
	void setDiscountValuePct( const basar::Decimal &	discountValuePct );
	void setGrpDiscountType	( const basar::Int16		grpDiscountType );
	void setBaseQty			( const basar::Int32		baseQty );
	void setDiscountSpec	( const basar::Int16		discountSpec );
	void setDiscountType	( const basar::Int16		discountType );
	void setDiscountQty		( const basar::Int16		discountQty );
	void setDiscountQtyPct	( const basar::Decimal &	discountQtyPct );
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

protected:
	virtual void doMap();

private:
	DiscountBaseValueMapperStub( const DiscountBaseValueMapperStub & );
	DiscountBaseValueMapperStub & operator=( const DiscountBaseValueMapperStub & );

	basar::Int32		m_ArticleNo;
	basar::Decimal		m_DiscountValuePct;
	basar::Int32		m_DiscountGrpNo;
	basar::VarString 	m_PharmacyGrpId;
	basar::VarString 	m_PharmGrpExcl_1;
	basar::VarString 	m_PharmGrpExcl_2;
	basar::VarString 	m_PharmGrpExcl_3;
	basar::Int32		m_CustomerNo;
	basar::Int32		m_ManufacturerNo;
	basar::Int16		m_GrpDiscountType;
	basar::Int32		m_BaseQty;
	basar::Int16		m_DiscountSpec;
	basar::Int16		m_DiscountType;
	basar::Int16		m_DiscountQty;
	basar::Decimal 		m_DiscountQtyPct;
	basar::Decimal 		m_SurchargePct;
	basar::Decimal 		m_FixedPrice;
	basar::Decimal 		m_RefundPct;
	basar::VarString	m_InternalDiscount;
	basar::Int32		m_DiscountArticle;
	basar::Decimal 		m_DiscountArticlePrice;
	basar::Decimal 		m_BaseValue;
	basar::Int32		m_BaseMultStdQty;
	basar::VarString 	m_NoMultipleQty;
	basar::Decimal 		m_FixedDiscountVal;
	basar::Int32		m_ArtCategoryNo;
	basar::Int16		m_PaymentTargetNo;
	basar::Decimal 		m_GrossProfitPct;
	basar::VarString 	m_AddOnDiscountOk;
	basar::VarString 	m_PaymentTermType;
	basar::Int32		m_TargetQty;
	basar::Decimal 		m_ExceedancePct;
	basar::Int16		m_RefundType;
	basar::Int32		m_ArticleNoPack;
	basar::Decimal 		m_RefundValue;
	basar::Int16		m_PromotionNo;
	basar::Int32		m_MaxQty;
	basar::VarString 	m_TurnoverCalcImpact;
	basar::VarString 	m_AddOnDiscount;
	basar::VarString 	m_MonthlyDiscount;
};

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_DISCOUNT_BASE_VALUE_MAPPER_STUB_H
