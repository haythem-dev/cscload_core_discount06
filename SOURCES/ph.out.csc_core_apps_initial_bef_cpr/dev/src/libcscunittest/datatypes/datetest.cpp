#include "cmnut.h"
#include "datefixture.h"
#include <datatypes/date.h>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestDate )
{
//									methodName_condition_expectation
FIXTURE_TEST_START( DateFixture, Date_stdCtor_unset )
{
	libcsc::Date dt;
	CHECK( dt.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, Date_copyCtorCscDate_20501223 )
{
	libcsc::Date dt( basar::Date( 20501223 ) );
	libcsc::Date dtCopy( dt );
	CHECK_EQUAL( basar::Date( 20501223 ), dtCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, Date_copyCtorCscDate_dirty )
{
	libcsc::Date dt( basar::Int32( 20501223 ) );
	libcsc::Date dtCopy( dt );
	CHECK( dtCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, Date_copyCtorBasarDate_20501223 )
{
	libcsc::Date dt( basar::Int32( 20501223 ) );
	CHECK_EQUAL( basar::Date( 20501223 ), dt );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, Date_copyCtorBasarDate_dirty )
{
	libcsc::Date dt( basar::Date( 20501223 ) );
	CHECK( dt.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, constOperatorBasarDate_20501223_keeps20501223 )
{
	libcsc::Date dt( basar::Date( 20501223 ) );
	const basar::Date & bdt = dt;
	CHECK_EQUAL( basar::Date( 20501223 ), bdt );
	CHECK_EQUAL( basar::Date( 20501223 ), dt );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, constOperatorBasarDate_clean_keepsClean )
{
	libcsc::Date dt( basar::Date( 20501223 ) );
	dt.setClean();
	const basar::Date & bdt = dt; bdt;
	CHECK( dt.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_unsetUnset_equal )
{
	libcsc::Date dt1( basar::Date( 20140407 ) );
	dt1.setUnset();
	libcsc::Date dt2;
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_unsetDirty_notEqual )
{
	libcsc::Date dt1;
	libcsc::Date dt2;
	dt2.setDirty();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_valuesEqualStatesNotEqual_equal )
{
	libcsc::Date dt1( basar::Date( 20140407 ) );
	dt1.setClean();
	libcsc::Date dt2( basar::Date( 20140407 ) );
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_valuesEqualStatesEqual_equal )
{
	libcsc::Date dt1( basar::Date( 20140407 ) );
	dt1.setClean();
	libcsc::Date dt2( basar::Date( 20140407 ) );
	dt2.setClean();
	CHECK_EQUAL( true, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_valuesNotEqualStatesEqual_notEqual )
{
	libcsc::Date dt1( basar::Date( 20111111 ) );
	dt1.setClean();
	libcsc::Date dt2( basar::Date( 20140407 ) );
	dt2.setClean();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, operatorEqual_valuesNotEqualStatesNotEqual_notEqual )
{
	libcsc::Date dt1( basar::Date( 20111111 ) );
	dt1.setClean();
	libcsc::Date dt2( basar::Date( 20140407 ) );
	dt2.setDirty();
	CHECK_EQUAL( false, dt1.operator==( dt2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, toStream_20501223_string20501223 )
{
	libcsc::Date dt( basar::Date( 20501223 ) );
	std::stringstream ss;
	dt.toStream( ss );
	CHECK_EQUAL( "12/23/2050 (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, constOperatorBasarDate_unset_exception )
{
	libcsc::Date dt;
	basar::Date bdt;
	CHECK_THROW( bdt = dt, libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DateFixture, toStream_unset_stringUNSET )
{
	libcsc::Date dt;
	std::stringstream ss;
	dt.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

