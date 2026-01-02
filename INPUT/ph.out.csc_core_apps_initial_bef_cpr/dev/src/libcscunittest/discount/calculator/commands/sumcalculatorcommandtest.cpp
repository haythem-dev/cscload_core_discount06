#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/sumcalculatorcommand.h>
#include "common/calculatorcommandstub.h"
#include <exceptions/emptycompositeexception.h>
#include <exceptions/invaliddataexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorCommands )
{
static const DiscountCalculatorResult & getUnset() 
{
	static DiscountCalculatorResult dcr;
	return dcr;
}

static const DiscountCalculatorResult & getFirstPercent() 
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 42 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 7.7 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}

static const DiscountCalculatorResult & getSecondAll()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 42 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 7.7 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.discountValue = basar::Decimal( 0.10 );
		dr.discountValueOrigin = CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_TYPE;
		dr.source.pharmacyGroup = "000";
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 13, 1, basar::Decimal( 3 ), false ) );
	}
	return dcr;
}

static const DiscountCalculatorResult & getThirdAll()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 42 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 8.8 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.discountValue = basar::Decimal( 0.20 );
		dr.discountValueOrigin = CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_TYPE;
		dr.source.pharmacyGroup = "000";
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 14, 1, basar::Decimal( 4 ), false ) );
	}
	return dcr;
}

static const DiscountCalculatorResult & getSumSecondAllThirdAll()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 42 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 7.7 ) + basar::Decimal( 8.8 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.discountValue = basar::Decimal( 0.10 ) + basar::Decimal( 0.20 );
		dr.discountValueOrigin = CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_TYPE;
		dr.source.pharmacyGroup = "000";
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 13, 1, basar::Decimal( 3 ), false ) );
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 14, 1, basar::Decimal( 4 ), false ) );
	}
	return dcr;
}

static const DiscountCalculatorResult & getFourthFix()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountedArticlePrice = basar::Decimal( 9.20 );
		dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}

static const DiscountCalculatorResult & getFifthFix()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountedArticlePrice = basar::Decimal( 9.10 );
		dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}



//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, Sum_calculate_emptyCollection_exception )
{
	SumCalculatorCommand calc( CT_ROOT, CT_SUM_TYPE, false );
	CHECK_THROW( calc.calculate(), libcsc::exceptions::EmptyCompositeException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, Sum_calculate_firstPercentSecondUnset_first )
{
	SumCalculatorCommand calc( CT_ROOT, CT_SUM_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getUnset() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getFirstPercent(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, Sum_calculate_firstAllSecondAll_firstPlusSecond )
{
	SumCalculatorCommand calc( CT_ROOT, CT_SUM_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getSecondAll() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getThirdAll() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getSumSecondAllThirdAll(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, Sum_calculate_firstFixSecondFix_exception )
{
	SumCalculatorCommand calc( CT_ROOT, CT_SUM_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFourthFix() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFifthFix() ) ) );
	CHECK_THROW( calc.calculate(), libcsc::exceptions::InvalidDataException );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

