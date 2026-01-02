#include "cmnut.h"
#include "datetimefixture.h"
#include <datatypes/datetime.h>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestDateTime )
{
//									methodName_condition_expectation
FIXTURE_TEST_START( DateTimeFixture, DateTime_stdCtor_unset )
{
	libcsc::DateTime dt;
	CHECK( dt.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, DateTime_copyCtorCscDateTime_20501223_133655 )
{
	libcsc::DateTime dt( basar::DateTime( 20501223, 133655 ) );
	libcsc::DateTime dtCopy( dt );
	CHECK_EQUAL( basar::DateTime( 20501223, 133655 ), dtCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, DateTime_copyCtorCscDateTime_dirty )
{
	libcsc::DateTime dt( basar::Int32( 20501223 ) );
	libcsc::DateTime dtCopy( dt );
	CHECK( dtCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, DateTime_copyCtorBasarDateTime_20501223 )
{
	libcsc::DateTime dt( basar::Int32( 20501223 ) );
	CHECK_EQUAL( basar::DateTime( 20501223 ), dt );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, DateTime_copyCtorBasarDateTime_dirty )
{
	libcsc::DateTime dt( basar::DateTime( 20501223 ) );
	CHECK( dt.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, constOperatorBasarDateTime_20501223_keeps20501223 )
{
	libcsc::DateTime dt( basar::DateTime( 20501223 ) );
	const basar::DateTime & bdt = dt;
	CHECK_EQUAL( basar::DateTime( 20501223 ), bdt );
	CHECK_EQUAL( basar::DateTime( 20501223 ), dt );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, constOperatorBasarDateTime_clean_keepsClean )
{
	libcsc::DateTime dt( basar::DateTime( 20501223 ) );
	dt.setClean();
	const basar::DateTime & bdt = dt; bdt;
	CHECK( dt.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_unsetUnset_equal )
{
	libcsc::DateTime dt1( basar::DateTime( 20140407 ) );
	dt1.setUnset();
	libcsc::DateTime dt2;
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_unsetDirty_notEqual )
{
	libcsc::DateTime dt1;
	libcsc::DateTime dt2;
	dt2.setDirty();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_valuesEqualStatesNotEqual_equal )
{
	libcsc::DateTime dt1( basar::DateTime( 20140407 ) );
	dt1.setClean();
	libcsc::DateTime dt2( basar::DateTime( 20140407 ) );
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_valuesEqualStatesEqual_equal )
{
	libcsc::DateTime dt1( basar::DateTime( 20140407 ) );
	dt1.setClean();
	libcsc::DateTime dt2( basar::DateTime( 20140407 ) );
	dt2.setClean();
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_valuesNotEqualStatesEqual_notEqual )
{
	libcsc::DateTime dt1( basar::DateTime( 20111111 ) );
	dt1.setClean();
	libcsc::DateTime dt2( basar::DateTime( 20140407 ) );
	dt2.setClean();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, operatorEqual_valuesNotEqualStatesNotEqual_notEqual )
{
	libcsc::DateTime dt1( basar::DateTime( 20111111 ) );
	dt1.setClean();
	libcsc::DateTime dt2( basar::DateTime( 20140407 ) );
	dt2.setDirty();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, toStream_20501223_string20501223 )
{
	libcsc::DateTime dt( basar::DateTime( 20501223, 113655000 ) );
	std::stringstream ss;
	dt.toStream( ss );
	CHECK_EQUAL( "12/23/2050 11:36:55.000 AM (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, constOperatorBasarDateTime_unset_exception )
{
	libcsc::DateTime dt;
	basar::DateTime bdt;
	CHECK_THROW( bdt = dt, libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateTimeFixture, toStream_unset_stringUNSET )
{
	libcsc::DateTime dt;
	std::stringstream ss;
	dt.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

