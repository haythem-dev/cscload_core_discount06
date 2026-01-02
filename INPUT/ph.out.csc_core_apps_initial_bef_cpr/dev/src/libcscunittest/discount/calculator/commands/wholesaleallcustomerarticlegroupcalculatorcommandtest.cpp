#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/wholesaleallcustomerarticlegroupcalculatorcommand.h>
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
//static const DiscountBaseValuePtr getPercent()
//{
//	DiscountBaseValuePtr bv( new DiscountBaseValue() );
//	DiscountBaseValueMapperStub mapper( bv );
//	mapper.setArticleNo( 4711 );
//	mapper.setCustomerNo( 0 );
//	mapper.setPharmacyGrpId( PHARMACY_GROUP_UNIVERSAL );
//	mapper.setDiscountSpec( DISC_SPEC_WHOLESALE_INDUSTRY );
//	mapper.setDiscountValuePct( basar::Decimal( 7.7 ) );
//	mapper.setBaseQty( 1 );
//	mapper.setBaseValue( basar::Decimal( 7.7 ) );
//	mapper.map();
//	return bv;
//}



//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleAllCustomerArticleGroup_calculate_validPercent_givenPercent )
{
	CHECK_EQUAL( "TODO: to be implemented", "not implemented yet" );

	//DiscountBaseValuePtr percent( getPercent() );
	//addDiscountBaseValue( percent );

	//WholesaleAllCustomerArticleGroupCalculatorCommand cmd( CT_ROOT, CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE );
	//cmd.inject( m_DiscountBaseValueCollection );
	//cmd.inject( m_NullLogger );
	//cmd.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	//DiscountCalculatorResult res = cmd.calculate();

	//CHECK_EQUAL( percent->getArticleNo(), res.baseValue.articleNo );
	//CHECK_EQUAL( percent->getDiscountValuePct(), res.getDiscountResult( 1 ).discountPercent );
	//CHECK_EQUAL( CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE, res.getDiscountResult( 1 ).discountPercentOrigin );
}
FIXTURE_TEST_END


FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleAllCustomerArticleGroup_log_validPercent_validResult )
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

	//CHECK_EQUAL( logger->getCalcResult( CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE ), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

