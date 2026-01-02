#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/wholesaleindustrycustomerarticlegroupcalculatorcommand.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include "common/discountloggermock.h"
#include "common/discountloggermockptr.h"
#include <discount/common/orderbasevaluestub.h>
#include "common/discountbasevaluemapperstub.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorCommands )
{
//static const DiscountBaseValuePtr getFix()
//{
//	DiscountBaseValuePtr bv( new DiscountBaseValue() );
//	DiscountBaseValueMapperStub mapper( bv );
//	mapper.setArticleNo( 4711 );
//	mapper.setFixedPrice( basar::Decimal( 7.7 ) );
//	mapper.setBaseQty( 1 );
//	mapper.setBaseValue( basar::Decimal( 7.7 ) );
//	mapper.map();
//	return bv;
//}



//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleIndustryCustomerArticleGroup_calculate_validFixedPrice_givenPrice )
{
	CHECK_EQUAL( "TODO: to be implemented", "not implemented yet" );

	//DiscountBaseValuePtr fix( getFix() );
	//addDiscountBaseValue( fix );

	//FixedPriceCalculatorCommand fp( CT_ROOT, CT_FIXED_PRICE_TYPE );
	//fp.inject( m_DiscountBaseValueCollection );
	//fp.inject( m_NullLogger );
	//fp.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	//DiscountCalculatorResult res = fp.calculate();

	//CHECK_EQUAL( fix->getArticleNo(), res.baseValue.articleNo );
	//CHECK_EQUAL( fix->getFixedPrice(), res.getDiscountResult( 1 ).discountedArticlePrice );
	//CHECK_EQUAL( CT_FIXED_PRICE_TYPE, res.getDiscountResult( 1 ).discountedArticlePriceOrigin );
}
FIXTURE_TEST_END


FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleIndustryCustomerArticleGroup_log_validFixedPrice_validResult )
{
	CHECK_EQUAL( "TODO: to be implemented", "not implemented yet" );

	//DiscountBaseValuePtr fix( getFix() );
	//addDiscountBaseValue( fix );

	//DiscountLoggerMockPtr logger( new DiscountLoggerMock() );
	//FixedPriceCalculatorCommand fp( CT_ROOT, CT_FIXED_PRICE_TYPE );
	//fp.inject( m_DiscountBaseValueCollection );
	//fp.inject( logger );
	//fp.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	//DiscountCalculatorResult res = fp.calculate();

	//CHECK_EQUAL( logger->getCalcResult( CT_FIXED_PRICE_TYPE ), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

