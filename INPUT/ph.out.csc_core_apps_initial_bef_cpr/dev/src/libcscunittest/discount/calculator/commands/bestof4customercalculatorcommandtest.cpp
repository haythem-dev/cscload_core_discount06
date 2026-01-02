#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/bestof4customercombinedcalculatorcommand.h>
#include "common/calculatorcommandstub.h"
#include <exceptions/emptycompositeexception.h>

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

static const DiscountCalculatorResult & getSecondPercent()
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
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}

static const DiscountCalculatorResult & getThirdPercent()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 10 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.source.pharmacyGroup = "000";
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
		dr.discountedArticlePrice = basar::Decimal( 9.10 );
		dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}

static const DiscountCalculatorResult & getThirdFourthCombined()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 10 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.discountedArticlePrice = basar::Decimal( 9.10 );
		dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
		dr.source.pharmacyGroup = "000";
	}
	return dcr;
}

static const DiscountCalculatorResult & getFifthRebateInKind()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 13, 1, basar::Decimal( 3 ), false ) );
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 14, 1, basar::Decimal( 4 ), false ) );
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 15, 1, basar::Decimal( 5 ), false ) );
	}
	return dcr;
}

static const DiscountCalculatorResult & getThirdFourthFifthCombined()
{
	static DiscountCalculatorResult dcr;		
	if( dcr.baseValue.isUnset() )
	{
		dcr.baseValue.articleNo = 4711;
		dcr.baseValue.baseArticlePrice = basar::Decimal( 10 );
		dcr.baseValue.quantity = 1;
		DiscountResult & dr( dcr.getDiscountResult( 1 ) );
		dr.discountPercent = basar::Decimal( 10 );
		dr.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE;
		dr.discountedArticlePrice = basar::Decimal( 9.10 );
		dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
		dr.source.pharmacyGroup = "000";
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 13, 1, basar::Decimal( 3 ), false ) );
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 14, 1, basar::Decimal( 4 ), false ) );
		dcr.addRebateInKind( RebateInKindValue( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, 15, 1, basar::Decimal( 5 ), false ) );
	}
	return dcr;
}



//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, BestOf4CustomerCombined_calculate_emptyCollection_exception )
{
	BestOf4CustomerCombinedCalculatorCommand calc( CT_ROOT, CT_BEST_OF_FOR_CUSTOMER_TYPE, false );
	CHECK_THROW( calc.calculate(), libcsc::exceptions::EmptyCompositeException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, BestOf4CustomerCombined_calculate_firstPercentSecondUnset_first )
{
	BestOf4CustomerCombinedCalculatorCommand calc( CT_ROOT, CT_BEST_OF_FOR_CUSTOMER_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getUnset() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getFirstPercent(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, BestOf4CustomerCombined_calculate_firstPercentLessThanSecondPercent_second )
{
	BestOf4CustomerCombinedCalculatorCommand calc( CT_ROOT, CT_BEST_OF_FOR_CUSTOMER_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getSecondPercent() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getSecondPercent(), res );
}
FIXTURE_TEST_END
	
FIXTURE_TEST_START( CommonCalculatorCommandFixture, BestOf4CustomerCombined_calculate_firstPercentSecondFix_combined )
{
	BestOf4CustomerCombinedCalculatorCommand calc( CT_ROOT, CT_BEST_OF_FOR_CUSTOMER_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getThirdPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFourthFix() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getThirdFourthCombined(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, BestOf4CustomerCombined_calculate_firstPercentSecondFixThirdRiK_combined )
{
	BestOf4CustomerCombinedCalculatorCommand calc( CT_ROOT, CT_BEST_OF_FOR_CUSTOMER_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getThirdPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFourthFix() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFifthRebateInKind() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getThirdFourthFifthCombined(), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

