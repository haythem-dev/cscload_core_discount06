#include "cmnut.h"
#include "common/commoncalculatorcommandfixture.h"
#include <discount/calculator/commands/retailcalculatorcommand.h>
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
	mapper.setPharmacyGrpId( PHARMACY_GROUP_UNIVERSAL );
	mapper.setCustomerNo( 0 );
	mapper.setDiscountGrpNo( 0 );
	mapper.setDiscountSpec( DISC_SPEC_RETAIL );
	mapper.setDiscountValuePct( basar::Decimal( 7.7 ) );
	mapper.setBaseQty( 1 );
	mapper.setBaseValue( basar::Decimal( 7.7 ) );
	mapper.map();
	return bv;
}

//													methodName_condition_expectation
FIXTURE_TEST_START( CommonCalculatorCommandFixture, Retail_calculate_validPercent_givenPercent )
{
	DiscountBaseValuePtr percent( getPercent() );
	addDiscountBaseValue( percent );

	RetailCalculatorCommand cmd( CT_ROOT, CT_RETAIL_TYPE );
	cmd.inject( m_DiscountBaseValueCollection );
	cmd.inject( m_NullLogger );
	cmd.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	DiscountCalculatorResult res = cmd.calculate();

	CHECK_EQUAL( percent->getArticleNo(), res.baseValue.articleNo );
	CHECK_EQUAL( percent->getDiscountValuePct(), res.getDiscountResult( 1 ).discountPercent );
	CHECK_EQUAL( CT_RETAIL_TYPE, res.getDiscountResult( 1 ).discountPercentOrigin );
}
FIXTURE_TEST_END


FIXTURE_TEST_START( CommonCalculatorCommandFixture, Retail_log_validPercent_validResult )
{
	DiscountBaseValuePtr percent( getPercent() );
	addDiscountBaseValue( percent );

	DiscountLoggerMockPtr logger( new DiscountLoggerMock() );
	RetailCalculatorCommand fp( CT_ROOT, CT_RETAIL_TYPE );
	fp.inject( m_DiscountBaseValueCollection );
	fp.inject( logger );
	fp.inject( IOrderBaseValueGetterPtr( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 1, 4711, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), basar::Decimal( 0 ), "4711" ) ) );
	DiscountCalculatorResult res = fp.calculate();

	CHECK_EQUAL( logger->getCalcResult( CT_RETAIL_TYPE ), res );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

