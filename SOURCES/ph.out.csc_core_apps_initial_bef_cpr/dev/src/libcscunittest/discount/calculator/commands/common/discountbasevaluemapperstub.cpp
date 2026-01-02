#include "cmnut.h"
#include "discountbasevaluemapperstub.h"
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <exceptions/invaliddataexception.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
DiscountBaseValueMapperStub::DiscountBaseValueMapperStub( 
	libcsc::discount::DiscountBaseValuePtr value
		)
: libcsc::discount::DiscountBaseValueMapperBase( value ),
  m_ArticleNo( 0 ),
  m_DiscountValuePct( 0 ),
  m_DiscountGrpNo( 0 ),
  m_PharmacyGrpId( "" ),
  m_PharmGrpExcl_1( "" ),
  m_PharmGrpExcl_2( "" ),
  m_PharmGrpExcl_3( "" ),
  m_CustomerNo( 0 ),
  m_ManufacturerNo( 0 ),
  m_GrpDiscountType( 0 ),
  m_BaseQty( 0 ),
  m_DiscountSpec( 0 ),
  m_DiscountType( 0 ),
  m_DiscountQty( 0 ),
  m_DiscountQtyPct( 0 ),
  m_SurchargePct( 0 ),
  m_FixedPrice( 0 ),
  m_RefundPct( 0 ),
  m_InternalDiscount( "" ),
  m_DiscountArticle( 0 ),
  m_DiscountArticlePrice( 0 ),
  m_BaseValue( 0 ),
  m_BaseMultStdQty( 0 ),
  m_NoMultipleQty( "" ),
  m_FixedDiscountVal( 0 ),
  m_ArtCategoryNo( 0 ),
  m_PaymentTargetNo( 0 ),
  m_GrossProfitPct( 0 ),
  m_AddOnDiscountOk( "" ),
  m_PaymentTermType( "" ),
  m_TargetQty( 0 ),
  m_ExceedancePct( 0 ),
  m_RefundType( 0 ),
  m_ArticleNoPack( 0 ),
  m_RefundValue( 0 ),
  m_PromotionNo( 0 ),
  m_MaxQty( 0 ),
  m_TurnoverCalcImpact( "" ),
  m_AddOnDiscount( "" ),
  m_MonthlyDiscount( "" )
{
}

DiscountBaseValueMapperStub::~DiscountBaseValueMapperStub()
{
}

void DiscountBaseValueMapperStub::setValuesFromText( const basar::VarString & line )
{
	basar::cmnutil::CollBString	subStrings = line.tokenize( ";", true, false );
	if( 39 != subStrings.size() )
	{
		std::stringstream ss;
		ss << "Wrong number of values, line=<" << line.c_str() << ">";
		throw libcsc::exceptions::InvalidDataException( basar::ExceptInfo( "SumCalculatorCommand::addResult()", ss.str().c_str(), __FILE__, __LINE__ ) );
	}
	
	m_ArticleNo = subStrings[ 0 ].stoi();
	m_DiscountValuePct.fromNonLocString( subStrings[ 1 ] );
	m_DiscountGrpNo = subStrings[ 2 ].stoi();
	m_PharmacyGrpId = subStrings[ 3 ];
	m_PharmGrpExcl_1 = subStrings[ 4 ];
	m_PharmGrpExcl_2 = subStrings[ 5 ];
	m_PharmGrpExcl_3 = subStrings[ 6 ];
	m_CustomerNo = subStrings[ 7 ].stoi();
	m_ManufacturerNo = subStrings[ 8 ].stoi();
	m_GrpDiscountType = static_cast<basar::Int16>( subStrings[ 9 ].stoi() );
	m_BaseQty = subStrings[ 10 ].stoi();
	m_DiscountSpec = static_cast<basar::Int16>( subStrings[ 11 ].stoi() );
	m_DiscountType = static_cast<basar::Int16>( subStrings[ 12 ].stoi() );
	m_DiscountQty = static_cast<basar::Int16>( subStrings[ 13 ].stoi() );
	m_DiscountQtyPct.fromNonLocString( subStrings[ 14 ] );
	m_SurchargePct.fromNonLocString( subStrings[ 15 ] );
	m_FixedPrice.fromNonLocString( subStrings[ 16 ] );
	m_RefundPct.fromNonLocString( subStrings[ 17 ] );
	m_InternalDiscount = subStrings[ 18 ];
	m_DiscountArticle = subStrings[ 19 ].stoi();
	m_DiscountArticlePrice.fromNonLocString( subStrings[ 20 ] );
	m_BaseValue.fromNonLocString( subStrings[ 21 ] );
	m_BaseMultStdQty = subStrings[ 22 ].stoi();
	m_NoMultipleQty = subStrings[ 23 ];
	m_FixedDiscountVal.fromNonLocString( subStrings[ 24 ] );
	m_ArtCategoryNo = subStrings[ 25 ].stoi();
	m_PaymentTargetNo = static_cast<basar::Int16>( subStrings[ 26 ].stoi() );
	m_GrossProfitPct.fromNonLocString( subStrings[ 27 ] );
	m_AddOnDiscountOk = subStrings[ 28 ];
	m_PaymentTermType = subStrings[ 29 ];
	m_TargetQty = subStrings[ 30 ].stoi();
	m_ExceedancePct.fromNonLocString( subStrings[ 31 ] );
	m_RefundType = static_cast<basar::Int16>( subStrings[ 32 ].stoi() );
	m_ArticleNoPack = subStrings[ 33 ].stoi();
	m_RefundValue.fromNonLocString( subStrings[ 34 ] );
	m_PromotionNo = static_cast<basar::Int16>( subStrings[ 35 ].stoi() );
	m_MaxQty = subStrings[ 36 ].stoi();
	m_TurnoverCalcImpact = subStrings[ 37 ];
	m_AddOnDiscount = subStrings[ 38 ];
	m_MonthlyDiscount = subStrings[ 39 ];
}

void DiscountBaseValueMapperStub::setArticleNo( const basar::Int32 articleNo )
{
	m_ArticleNo = articleNo;
}

void DiscountBaseValueMapperStub::setDiscountValuePct( const basar::Decimal & discountValuePct )
{
	m_DiscountValuePct = discountValuePct;
}

void DiscountBaseValueMapperStub::setDiscountGrpNo( const basar::Int32 discountGrpNo )
{
	m_DiscountGrpNo = discountGrpNo;
}

void DiscountBaseValueMapperStub::setPharmacyGrpId( const basar::VarString & pharmacyGrpId )
{
	m_PharmacyGrpId = pharmacyGrpId;
}

void DiscountBaseValueMapperStub::setPharmGrpExcl_1( const basar::VarString & pharmGrpExcl_1 )
{
	m_PharmGrpExcl_1 = pharmGrpExcl_1;
}

void DiscountBaseValueMapperStub::setPharmGrpExcl_2( const basar::VarString & pharmGrpExcl_2 )
{
	m_PharmGrpExcl_2 = pharmGrpExcl_2;
}

void DiscountBaseValueMapperStub::setPharmGrpExcl_3( const basar::VarString & pharmGrpExcl_3 )
{
	m_PharmGrpExcl_3 = pharmGrpExcl_3;
}

void DiscountBaseValueMapperStub::setCustomerNo( const basar::Int32 customerNo )
{
	m_CustomerNo = customerNo;
}

void DiscountBaseValueMapperStub::setManufacturerNo( const basar::Int32 manufacturerNo )
{
	m_ManufacturerNo = manufacturerNo;
}
	
void DiscountBaseValueMapperStub::setGrpDiscountType( const basar::Int16 grpDiscountType )
{
	m_GrpDiscountType = grpDiscountType;
}

void DiscountBaseValueMapperStub::setBaseQty( const basar::Int32 baseQty )
{
	m_BaseQty = baseQty;
}

void DiscountBaseValueMapperStub::setDiscountSpec( const basar::Int16 discountSpec )
{
	m_DiscountSpec = discountSpec;
}

void DiscountBaseValueMapperStub::setDiscountType( const basar::Int16 discountType )
{
	m_DiscountType = discountType;
}

void DiscountBaseValueMapperStub::setDiscountQty( const basar::Int16 discountQty )
{
	m_DiscountQty = discountQty;
}

void DiscountBaseValueMapperStub::setDiscountQtyPct( const basar::Decimal & discountQtyPct )
{
	m_DiscountQtyPct = discountQtyPct;
}

void DiscountBaseValueMapperStub::setSurchargePct( const basar::Decimal & surchargePct )
{
	m_SurchargePct = surchargePct;
}

void DiscountBaseValueMapperStub::setFixedPrice( const basar::Decimal & fixedPrice )
{
	m_FixedPrice = fixedPrice;
}

void DiscountBaseValueMapperStub::setRefundPct( const basar::Decimal & refundPct )
{
	m_RefundPct = refundPct;
}

void DiscountBaseValueMapperStub::setInternalDiscount( const basar::VarString & internalDiscount )
{
	m_InternalDiscount = internalDiscount;
}

void DiscountBaseValueMapperStub::setDiscountArticle( const basar::Int32 discountArticle )
{
	m_DiscountArticle = discountArticle;
}

void DiscountBaseValueMapperStub::setDiscountArticlePrice( const basar::Decimal & discountArticlePrice )
{
	m_DiscountArticlePrice = discountArticlePrice;
}

void DiscountBaseValueMapperStub::setBaseValue( const basar::Decimal & baseValue )
{
	m_BaseValue = baseValue;
}

void DiscountBaseValueMapperStub::setBaseMultStdQty( const basar::Int32 baseMultStdQty )
{
	m_BaseMultStdQty = baseMultStdQty;
}

void DiscountBaseValueMapperStub::setNoMultipleQty( const basar::VarString & noMultipleQty )
{
	m_NoMultipleQty = noMultipleQty;
}

void DiscountBaseValueMapperStub::setFixedDiscountVal( const basar::Decimal & fixedDiscountVal )
{
	m_FixedDiscountVal = fixedDiscountVal;
}

void DiscountBaseValueMapperStub::setArtCategoryNo( const basar::Int32 artCategoryNo )
{
	m_ArtCategoryNo = artCategoryNo;
}

void DiscountBaseValueMapperStub::setPaymentTargetNo( const basar::Int16 paymentTargetNo )
{
	m_PaymentTargetNo = paymentTargetNo;
}

void DiscountBaseValueMapperStub::setGrossProfitPct( const basar::Decimal & grossProfitPct )
{
	m_GrossProfitPct = grossProfitPct;
}

void DiscountBaseValueMapperStub::setAddOnDiscountOk( const basar::VarString & addOnDiscountOk )
{
	m_AddOnDiscountOk = addOnDiscountOk;
}

void DiscountBaseValueMapperStub::setPaymentTermType( const basar::VarString & paymentTermType )
{
	m_PaymentTermType = paymentTermType;
}

void DiscountBaseValueMapperStub::setTargetQty( const basar::Int32 targetQty )
{
	m_TargetQty = targetQty;
}

void DiscountBaseValueMapperStub::setExceedancePct( const basar::Decimal & exceedancePct )
{
	m_ExceedancePct = exceedancePct;
}

void DiscountBaseValueMapperStub::setRefundType( const basar::Int16 refundType )
{
	m_RefundType = refundType;
}

void DiscountBaseValueMapperStub::setArticleNoPack( const basar::Int32 articleNoPack )
{
	m_ArticleNoPack = articleNoPack;
}

void DiscountBaseValueMapperStub::setRefundValue( const basar::Decimal & refundValue )
{
	m_RefundValue = refundValue;
}

void DiscountBaseValueMapperStub::setPromotionNo( const basar::Int16 promotionNo )
{
	m_PromotionNo = promotionNo;
}

void DiscountBaseValueMapperStub::setMaxQty( const basar::Int32 maxQty )
{
	m_MaxQty = maxQty;
}

void DiscountBaseValueMapperStub::setTurnoverCalcImpact(const basar::VarString & turnoverCalcImpact )
{
	m_TurnoverCalcImpact = turnoverCalcImpact;
}

void DiscountBaseValueMapperStub::setAddOnDiscount( const basar::VarString & addOnDiscount )
{
	m_AddOnDiscount = addOnDiscount;
}

void DiscountBaseValueMapperStub::setMonthlyDiscount( const basar::VarString & monthlyDiscount )
{
	m_MonthlyDiscount = monthlyDiscount;
}

void DiscountBaseValueMapperStub::doMap()
{
	DiscountBaseValueMapperBase::setArticleNo( m_ArticleNo );
	DiscountBaseValueMapperBase::setDiscountGrpNo( m_DiscountGrpNo );
	DiscountBaseValueMapperBase::setPharmacyGrpId( m_PharmacyGrpId );
	DiscountBaseValueMapperBase::setPharmGrpExcl_1( m_PharmGrpExcl_1 );
	DiscountBaseValueMapperBase::setPharmGrpExcl_2( m_PharmGrpExcl_2 );
	DiscountBaseValueMapperBase::setPharmGrpExcl_3( m_PharmGrpExcl_3 );
	DiscountBaseValueMapperBase::setCustomerNo( m_CustomerNo );
	DiscountBaseValueMapperBase::setManufacturerNo( m_ManufacturerNo );
	DiscountBaseValueMapperBase::setDiscountValuePct( m_DiscountValuePct );
	DiscountBaseValueMapperBase::setGrpDiscountType( m_GrpDiscountType );
	DiscountBaseValueMapperBase::setBaseQty( m_BaseQty );
	DiscountBaseValueMapperBase::setDiscountSpec( m_DiscountSpec );
	DiscountBaseValueMapperBase::setDiscountType( m_DiscountType );
	DiscountBaseValueMapperBase::setDiscountQty( m_DiscountQty );
	DiscountBaseValueMapperBase::setDiscountQtyPct( m_DiscountQtyPct );
	DiscountBaseValueMapperBase::setSurchargePct( m_SurchargePct );
	DiscountBaseValueMapperBase::setFixedPrice( m_FixedPrice );
	DiscountBaseValueMapperBase::setRefundPct( m_RefundPct );
	DiscountBaseValueMapperBase::setInternalDiscount( m_InternalDiscount );
	DiscountBaseValueMapperBase::setDiscountArticle( m_DiscountArticle );
	DiscountBaseValueMapperBase::setDiscountArticlePrice( m_DiscountArticlePrice );
	DiscountBaseValueMapperBase::setBaseValue( m_BaseValue );
	DiscountBaseValueMapperBase::setBaseMultStdQty( m_BaseMultStdQty );
	DiscountBaseValueMapperBase::setNoMultipleQty( m_NoMultipleQty );
	DiscountBaseValueMapperBase::setFixedDiscountVal( m_FixedDiscountVal );
	DiscountBaseValueMapperBase::setArtCategoryNo( m_ArtCategoryNo );
	DiscountBaseValueMapperBase::setPaymentTargetNo( m_PaymentTargetNo );
	DiscountBaseValueMapperBase::setGrossProfitPct( m_GrossProfitPct );
	DiscountBaseValueMapperBase::setAddOnDiscountOk( m_AddOnDiscountOk );
	DiscountBaseValueMapperBase::setPaymentTermType( m_PaymentTermType );
	DiscountBaseValueMapperBase::setTargetQty( m_TargetQty );
	DiscountBaseValueMapperBase::setExceedancePct( m_ExceedancePct );
	DiscountBaseValueMapperBase::setRefundType( m_RefundType );
	DiscountBaseValueMapperBase::setArticleNoPack( m_ArticleNoPack );
	DiscountBaseValueMapperBase::setRefundValue( m_RefundValue );
	DiscountBaseValueMapperBase::setPromotionNo( m_PromotionNo );
	DiscountBaseValueMapperBase::setMaxQty( m_MaxQty );
	DiscountBaseValueMapperBase::setTurnoverCalcImpact( m_TurnoverCalcImpact );
	DiscountBaseValueMapperBase::setAddOnDiscount( m_AddOnDiscount );
	DiscountBaseValueMapperBase::setMonthlyDiscount( m_MonthlyDiscount );
}

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

