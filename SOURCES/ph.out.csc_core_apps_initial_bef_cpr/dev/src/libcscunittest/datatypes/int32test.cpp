#include "cmnut.h"
#include "int32fixture.h"
#include <datatypes/int32.h>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestInt32 )
{
//									methodName_condition_expectation
FIXTURE_TEST_START( Int32Fixture, Int32_stdCtor_unset )
{
	libcsc::Int32 i;
	CHECK( i.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, Int32_copyCtorCscInt32_123 )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	libcsc::Int32 iCopy( i );
	CHECK_EQUAL( basar::Int32( 123 ), iCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, Int32_copyCtorCscInt32_dirty )
{
	libcsc::Int32 i( basar::Int32( 0 ) );
	libcsc::Int32 iCopy( i );
	CHECK( iCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, Int32_copyCtorBasarInt32_123 )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	CHECK_EQUAL( basar::Int32( 123 ), i );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, Int32_copyCtorBasarInt32_dirty )
{
	libcsc::Int32 i( basar::Int32( 0 ) );
	CHECK( i.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, constOperatorBasarInt32_123_keeps123 )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	const basar::Int32 & bi = i.operator const basar::Int32 &();
	CHECK_EQUAL( basar::Int32( 123 ), bi );
	CHECK_EQUAL( basar::Int32( 123 ), i );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, constOperatorBasarInt32_clean_keepsClean )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	i.setClean();
	const basar::Int32 & bi = i.operator const basar::Int32 &(); bi;
	CHECK( i.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, get_123_keeps123 )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	const basar::Int32 & bi = i.get();
	CHECK_EQUAL( basar::Int32( 123 ), bi );
	CHECK_EQUAL( basar::Int32( 123 ), i );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, get_clean_keepsClean )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	i.setClean();
	const basar::Int32 & bi = i.get(); bi;
	CHECK( i.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_unsetUnset_equal )
{
	libcsc::Int32 i1( 4711 );
	i1.setUnset();
	libcsc::Int32 i2;
	CHECK_EQUAL( true, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_unsetDirty_notEqual )
{
	libcsc::Int32 i1;
	libcsc::Int32 i2;
	i2.setDirty();
	CHECK_EQUAL( false, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_valuesEqualStatesNotEqual_equal )
{
	libcsc::Int32 i1( 4711 );
	i1.setClean();
	libcsc::Int32 i2( 4711 );
	CHECK_EQUAL( true, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_valuesEqualStatesEqual_equal )
{
	libcsc::Int32 i1( 4711 );
	i1.setClean();
	libcsc::Int32 i2( 4711 );
	i2.setClean();
	CHECK_EQUAL( true, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_valuesNotEqualStatesEqual_notEqual )
{
	libcsc::Int32 i1( 42 );
	i1.setClean();
	libcsc::Int32 i2( 4711 );
	i2.setClean();
	CHECK_EQUAL( false, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, operatorEqual_valuesNotEqualStatesNotEqual_notEqual )
{
	libcsc::Int32 i1( 42 );
	i1.setClean();
	libcsc::Int32 i2( 4711 );
	i2.setDirty();
	CHECK_EQUAL( false, i1.operator==( i2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, toStream_123_string123 )
{
	libcsc::Int32 i( basar::Int32( 123 ) );
	std::stringstream ss;
	i.toStream( ss );
	CHECK_EQUAL( "123 (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, constOperatorBasarInt32_unset_exception )
{
	libcsc::Int32 i;
	basar::Int32 bi;
	CHECK_THROW( bi = i, libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( Int32Fixture, toStream_unset_stringUNSET )
{
	libcsc::Int32 i;
	std::stringstream ss;
	i.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

