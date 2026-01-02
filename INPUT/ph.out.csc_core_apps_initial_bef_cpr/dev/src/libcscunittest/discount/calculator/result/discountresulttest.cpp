#include "cmnut.h"
#include "common/discountresultfixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorResult )
{
//											methodName_condition_expectation
FIXTURE_TEST_START( DiscountResultFixture, DiscountResult_stdCtor_isUnset )
{
	DiscountResult dr;
	CHECK( dr.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, DiscountResult_stdCtor_values )
{
	DiscountResult dr;
	CHECK_EQUAL( CT_UNSET, dr.discountPercentOrigin );
	CHECK_EQUAL( CT_UNSET, dr.discountValueOrigin );
	CHECK_EQUAL( CT_UNSET, dr.discountedArticlePriceOrigin );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, DiscountResult_copyCtor_isUnset )
{
	DiscountResult dr( m_DiscountResult );
	CHECK( dr.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, DiscountResult_copyCtor_values )
{
	DiscountResult dr( m_DiscountResult );
	CHECK_EQUAL( CT_UNSET, dr.discountPercentOrigin );
	CHECK_EQUAL( CT_UNSET, dr.discountValueOrigin );
	CHECK_EQUAL( CT_UNSET, dr.discountedArticlePriceOrigin );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, constOperatorDiscountResult_values_keepsValues )
{
	m_DiscountResult.discountPercent = basar::Decimal( 47.11 );
	m_DiscountResult.discountPercentOrigin = CT_RETAIL_TYPE;
	m_DiscountResult.discountValue = basar::Decimal( 123.45 );
	m_DiscountResult.discountValueOrigin = CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE;
	m_DiscountResult.discountedArticlePrice = basar::Decimal( 876.54 );
	m_DiscountResult.discountedArticlePriceOrigin = CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE;
	DiscountResult dr;
	dr.operator=( m_DiscountResult );

	CHECK_EQUAL( basar::Decimal( 47.11 ), dr.discountPercent );
	CHECK_EQUAL( CT_RETAIL_TYPE, dr.discountPercentOrigin );
	CHECK_EQUAL( basar::Decimal( 123.45 ), dr.discountValue );
	CHECK_EQUAL( CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE, dr.discountValueOrigin );
	CHECK_EQUAL( basar::Decimal( 876.54 ), dr.discountedArticlePrice );
	CHECK_EQUAL( CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE, dr.discountedArticlePriceOrigin );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, operatorEqual_unsetUnset_equal )
{
	DiscountResult dr1;
	DiscountResult dr2;
	CHECK_EQUAL( true, dr1.operator==( dr2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, operatorEqual_unsetClean_notEqual )
{
	DiscountResult dr1;
	DiscountResult dr2;
	dr2.discountPercent.setClean();
	dr2.discountValue.setClean();
	dr2.discountedArticlePrice.setClean();
	CHECK_EQUAL( false, dr1.operator==( dr2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, toStream_values_stringValues )
{
	m_DiscountResult.discountPercent = basar::Decimal( 47.11 );
	m_DiscountResult.discountPercentOrigin = CT_RETAIL_TYPE;
	m_DiscountResult.discountValue = basar::Decimal( 123.45 );
	m_DiscountResult.discountValueOrigin = CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE;
	m_DiscountResult.discountedArticlePrice = basar::Decimal( 876.54 );
	m_DiscountResult.discountedArticlePriceOrigin = CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE;
	std::stringstream ss;
	m_DiscountResult.toStream( ss );
	CHECK_EQUAL( "DiscountResult: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, discountPercent=<47.109999999999999 (DIRTY)>, discountPercentOrigin=<CT_RETAIL_TYPE>, discountValue=<123.45 (DIRTY)>, discountValueOrigin=<CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE>, discountedArticlePrice=<876.53999999999996 (DIRTY)>, discountedArticlePriceOrigin=<CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE>", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultFixture, toStream_unset_stringUnset )
{
	std::stringstream ss;
	m_DiscountResult.toStream( ss );
	CHECK_EQUAL( "DiscountResult: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, discountPercent=<UNSET>, discountPercentOrigin=<CT_UNSET>, discountValue=<UNSET>, discountValueOrigin=<CT_UNSET>, discountedArticlePrice=<UNSET>, discountedArticlePriceOrigin=<CT_UNSET>", ss.str().c_str() );
}
FIXTURE_TEST_END

/* Tests for the following methods are needless, because they are delegated to class PropertyCollection only:

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;
*/

} // end TESTSUITE
} // end namespace libcscUnitTest
