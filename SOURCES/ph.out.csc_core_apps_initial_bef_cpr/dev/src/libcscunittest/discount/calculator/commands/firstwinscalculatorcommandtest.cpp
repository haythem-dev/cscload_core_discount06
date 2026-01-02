#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/firstwinscalculatorcommand.h>
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

static const DiscountCalculatorResult & getSecondFix()
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
FIXTURE_TEST_START( CommonCalculatorCommandFixture, FirstWins_calculate_emptyCollection_exception )
{
	FirstWinsCalculatorCommand calc( CT_ROOT, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, false );
	CHECK_THROW( calc.calculate(), libcsc::exceptions::EmptyCompositeException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, FirstWins_calculate_firstPercentSecondUnset_first )
{
	FirstWinsCalculatorCommand calc( CT_ROOT, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getUnset() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getFirstPercent(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, FirstWins_calculate_firstUnsetSecondPercent_second )
{
	FirstWinsCalculatorCommand calc( CT_ROOT, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getUnset() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getFirstPercent(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, FirstWins_calculate_firstPercentSecondFix_first )
{
	FirstWinsCalculatorCommand calc( CT_ROOT, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getSecondFix() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getFirstPercent(), res );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( CommonCalculatorCommandFixture, FirstWins_calculate_firstFixSecondPercent_first )
{
	FirstWinsCalculatorCommand calc( CT_ROOT, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, false );
	calc.inject( m_NullLogger );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getSecondFix() ) ) );
	calc.add( IDiscountCalculatorCommandPtr( new CalculatorCommandStub( getFirstPercent() ) ) );
	DiscountCalculatorResult res = calc.calculate();
	CHECK_EQUAL( getSecondFix(), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

