#include "cmnut.h"
#include "common/discountresultbasevaluefixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorResult )
{
//													methodName_condition_expectation
FIXTURE_TEST_START( DiscountResultBaseValueFixture, DiscountSource_stdCtor_isUnset )
{
	DiscountResultBaseValue drbv;
	CHECK( drbv.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, DiscountResult_copyCtor_isUnset )
{
	DiscountResultBaseValue drbv( m_DiscountResultBaseValue );
	CHECK( drbv.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, DiscountResult_copyCtor_values )
{
	m_DiscountResultBaseValue.articleNo = 4711;
	m_DiscountResultBaseValue.quantity = 29;
	m_DiscountResultBaseValue.baseArticlePrice = basar::Decimal( 56.43 );
	DiscountResultBaseValue drbv( m_DiscountResultBaseValue );
	CHECK_EQUAL( 4711, drbv.articleNo );
	CHECK_EQUAL( 29, drbv.quantity );
	CHECK_EQUAL( basar::Decimal( 56.43 ), drbv.baseArticlePrice );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, constOperatorDiscountResultBaseValue_values_keepsValues )
{
	m_DiscountResultBaseValue.articleNo = 4711;
	m_DiscountResultBaseValue.quantity = 29;
	m_DiscountResultBaseValue.baseArticlePrice = basar::Decimal( 56.43 );
	DiscountResultBaseValue drbv;
	drbv.operator=( m_DiscountResultBaseValue );

	CHECK_EQUAL( 4711, drbv.articleNo );
	CHECK_EQUAL( 29, drbv.quantity );
	CHECK_EQUAL( basar::Decimal( 56.43 ), drbv.baseArticlePrice );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, operatorEqual_unsetUnset_equal )
{
	DiscountResultBaseValue drbv1;
	DiscountResultBaseValue drbv2;
	CHECK_EQUAL( true, drbv1.operator==( drbv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, operatorEqual_unsetClean_notEqual )
{
	DiscountResultBaseValue drbv1;
	DiscountResultBaseValue drbv2;
	drbv2.articleNo.setClean();
	drbv2.quantity.setClean();
	drbv2.baseArticlePrice.setClean();
	CHECK_EQUAL( false, drbv1.operator==( drbv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, toStream_values_stringValues )
{
	m_DiscountResultBaseValue.articleNo = 4711;
	m_DiscountResultBaseValue.quantity = 29;
	m_DiscountResultBaseValue.baseArticlePrice = basar::Decimal( 56.43 );
	std::stringstream ss;
	m_DiscountResultBaseValue.toStream( ss );
	CHECK_EQUAL( "DiscountResultBaseValue: articleNo=<4711 (DIRTY)>, quantity=<29 (DIRTY)>, baseArticlePrice=<56.43 (DIRTY)>", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountResultBaseValueFixture, toStream_unset_stringUnset )
{
	std::stringstream ss;
	m_DiscountResultBaseValue.toStream( ss );
	CHECK_EQUAL( "DiscountResultBaseValue: articleNo=<UNSET>, quantity=<UNSET>, baseArticlePrice=<UNSET>", ss.str().c_str() );
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

