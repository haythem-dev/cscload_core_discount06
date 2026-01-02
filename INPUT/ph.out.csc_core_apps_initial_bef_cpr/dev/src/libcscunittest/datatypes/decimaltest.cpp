#include "cmnut.h"
#include "decimalfixture.h"
#include <datatypes/decimal.h>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestDecimal )
{
//									methodName_condition_expectation
FIXTURE_TEST_START( DecimalFixture, Decimal_zero_0_clean )
{
	CHECK_EQUAL( basar::Decimal( 0.0 ), libcsc::Decimal::zero() );
	CHECK( libcsc::Decimal::zero().isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, Decimal_stdCtor_unset )
{
	libcsc::Decimal d;
	CHECK( d.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, Decimal_copyCtorCscDecimal_1_1 )
{
	libcsc::Decimal d( basar::Decimal( 1.1 ) );
	libcsc::Decimal dCopy( d );
	CHECK_EQUAL( basar::Decimal( 1.1 ), dCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, Decimal_copyCtorCscDecimal_dirty )
{
	libcsc::Decimal d( basar::Decimal( 0.0 ) );
	libcsc::Decimal dCopy( d );
	CHECK( dCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, Decimal_copyCtorBasarDecimal_1_1 )
{
	libcsc::Decimal d( basar::Decimal( 1.1 ) );
	CHECK_EQUAL( basar::Decimal( 1.1 ), d );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, Decimal_copyCtorBasarDecimal_dirty )
{
	libcsc::Decimal d( basar::Decimal( 0.0 ) );
	CHECK( d.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, constOperatorBasarDecimal_1_1_keeps1_1 )
{
	libcsc::Decimal d( basar::Decimal( 1.1 ) );
	const basar::Decimal & bd = d;
	CHECK_EQUAL( basar::Decimal( 1.1 ), bd );
	CHECK_EQUAL( basar::Decimal( 1.1 ), d );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, constOperatorBasarDecimal_clean_keepsClean )
{
	libcsc::Decimal d( basar::Decimal( 1.1 ) );
	d.setClean();
	const basar::Decimal & bd = d; bd;
	CHECK( d.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, constOperatorBasarDecimal_unset_exception )
{
	libcsc::Decimal d;
	basar::Decimal bd;
	CHECK_THROW( bd = d, libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_unsetUnset_equal )
{
	libcsc::Decimal d1( basar::Decimal( 1.1 ) );
	d1.setUnset();
	libcsc::Decimal d2;
	CHECK_EQUAL( true, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_unsetDirty_notEqual )
{
	libcsc::Decimal d1;
	libcsc::Decimal d2;
	d2.setDirty();
	CHECK_EQUAL( false, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_valuesEqualStatesNotEqual_equal )
{
	libcsc::Decimal d1( basar::Decimal( 1.1 ) );
	d1.setClean();
	libcsc::Decimal d2( basar::Decimal( 1.1 ) );
	CHECK_EQUAL( true, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_valuesEqualStatesEqual_equal )
{
	libcsc::Decimal d1( basar::Decimal( 1.1 ) );
	d1.setClean();
	libcsc::Decimal d2( basar::Decimal( 1.1 ) );
	d2.setClean();
	CHECK_EQUAL( true, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_valuesNotEqualStatesEqual_notEqual )
{
	libcsc::Decimal d1( basar::Decimal( 2.2 ) );
	d1.setClean();
	libcsc::Decimal d2( basar::Decimal( 1.1 ) );
	d2.setClean();
	CHECK_EQUAL( false, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, operatorEqual_valuesNotEqualStatesNotEqual_notEqual )
{
	libcsc::Decimal d1( basar::Decimal( 2.2 ) );
	d1.setClean();
	libcsc::Decimal d2( basar::Decimal( 1.1 ) );
	d2.setDirty();
	CHECK_EQUAL( false, d1.operator==( d2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, toStream_1_2_string1_2 )
{
	libcsc::Decimal d( basar::Decimal( 1.2 ) );
	std::stringstream ss;
	d.toStream( ss );
	CHECK_EQUAL( "1.2 (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DecimalFixture, toStream_unset_stringUNSET )
{
	libcsc::Decimal d;
	std::stringstream ss;
	d.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

