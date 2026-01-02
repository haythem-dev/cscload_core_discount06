#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/wholesalecustomerarticlecalculatorcommand.h>
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
static const DiscountBaseValuePtr getPercent()
{
	DiscountBaseValuePtr bv( new DiscountBaseValue() );
	DiscountBaseValueMapperStub mapper( bv );
	mapper.setArticleNo( 4711 );
	mapper.setCustomerNo( 475909 );
	mapper.setDiscountSpec( DISC_SPEC_WHOLESALE );
	mapper.setDiscountValuePct( basar::Decimal( 7.7 ) );
	mapper.setBaseQty( 1 );
	mapper.setBaseValue( basar::Decimal( 7.7 ) );
	mapper.map();
	return bv;
}

//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleCustomerArticle_calculate_validPercent_givenPercent )
{
	DiscountBaseValuePtr percent( getPercent() );
	addDiscountBaseValue( percent );

	WholesaleCustomerArticleCalculatorCommand cmd( CT_ROOT, CT_WH_CUSTOMER_ARTICLE_TYPE );
	cmd.inject( m_DiscountBaseValueCollection );
	cmd.inject( m_NullLogger );
	cmd.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	DiscountCalculatorResult res = cmd.calculate();

	CHECK_EQUAL( percent->getArticleNo(), res.baseValue.articleNo );
	CHECK_EQUAL( percent->getDiscountValuePct(), res.getDiscountResult( 1 ).discountPercent );
	CHECK_EQUAL( CT_WH_CUSTOMER_ARTICLE_TYPE, res.getDiscountResult( 1 ).discountPercentOrigin );
}
FIXTURE_TEST_END


FIXTURE_TEST_START( CommonCalculatorCommandFixture, WholesaleCustomerArticle_log_validPercent_validResult )
{
	DiscountBaseValuePtr percent( getPercent() );
	addDiscountBaseValue( percent );

	DiscountLoggerMockPtr logger( new DiscountLoggerMock() );
	WholesaleCustomerArticleCalculatorCommand cmd( CT_ROOT, CT_WH_CUSTOMER_ARTICLE_TYPE );
	cmd.inject( m_DiscountBaseValueCollection );
	cmd.inject( logger );
	cmd.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	DiscountCalculatorResult res = cmd.calculate();

	CHECK_EQUAL( logger->getCalcResult( CT_WH_CUSTOMER_ARTICLE_TYPE ), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

