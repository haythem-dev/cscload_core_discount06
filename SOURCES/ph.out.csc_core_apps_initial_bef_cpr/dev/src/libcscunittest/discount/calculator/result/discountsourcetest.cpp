#include "cmnut.h"
#include "common/discountsourcefixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorResult )
{
//											methodName_condition_expectation
FIXTURE_TEST_START( DiscountSourceFixture, DiscountSource_stdCtor_isDirty )
{
	DiscountSource ds;
	CHECK( ds.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, DiscountSource_stdCtor_values )
{
	DiscountSource ds;
	CHECK_EQUAL( 0, ds.number );
	CHECK_EQUAL( DiscountSource::DST_POSITION, ds.type );
	CHECK_EQUAL( true, ds.pharmacyGroup == "" );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, DiscountSource_copyCtor_isDirty )
{
	DiscountSource ds( m_DiscountSource );
	CHECK( ds.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, DiscountSource_copyCtor_values )
{
	DiscountSource ds( m_DiscountSource );
	CHECK_EQUAL( 0, ds.number );
	CHECK_EQUAL( DiscountSource::DST_POSITION, ds.type );
	CHECK_EQUAL( true, ds.pharmacyGroup == "" );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, constOperatorDiscountSource_values_keepsValues )
{
	m_DiscountSource.number = 4711;
	m_DiscountSource.type = DiscountSource::DST_ARTICLE_GROUP;
	m_DiscountSource.pharmacyGroup = "nieselpriem";
	DiscountSource ds;
	ds.operator=( m_DiscountSource );

	CHECK_EQUAL( 4711, ds.number );
	CHECK_EQUAL( DiscountSource::DST_ARTICLE_GROUP, ds.type );
	CHECK_EQUAL( true, ds.pharmacyGroup == "nieselpriem" );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, operatorEqual_dirtyDirty_equal )
{
	DiscountSource ds1;
	DiscountSource ds2;
	CHECK_EQUAL( true, ds1.operator==( ds2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, operatorEqual_dirtyClean_notEqual )
{
	DiscountSource ds1;
	DiscountSource ds2;
	ds2.number.setClean();
	ds2.type.setClean();
	ds2.pharmacyGroup.setClean();
	CHECK_EQUAL( false, ds1.operator==( ds2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, toStream_values_stringValues )
{
	m_DiscountSource.number = 4711;
	m_DiscountSource.type = DiscountSource::DST_ARTICLE_GROUP;
	m_DiscountSource.pharmacyGroup = "nieselpriem";
	std::stringstream ss;
	m_DiscountSource.toStream( ss );
	CHECK_EQUAL( "DiscountSource: number=<4711 (DIRTY)>, type=<DST_ARTICLE_GROUP>, pharmacyGroup=<nieselpriem (DIRTY)>", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountSourceFixture, toStream_unset_stringUnset )
{
	m_DiscountSource.number.setUnset();
	m_DiscountSource.type.setUnset();
	m_DiscountSource.pharmacyGroup.setUnset();
	std::stringstream ss;
	m_DiscountSource.toStream( ss );
	CHECK_EQUAL( "DiscountSource: number=<UNSET>, type=<UNSET>, pharmacyGroup=<UNSET>", ss.str().c_str() );
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
