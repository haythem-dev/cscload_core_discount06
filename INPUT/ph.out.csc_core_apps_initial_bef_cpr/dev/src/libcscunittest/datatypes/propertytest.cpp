#include "cmnut.h"
#include "propertyfixture.h"
#include <datatypes/property.hpp>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestProperty )
{
//									 methodName_condition_expectation
FIXTURE_TEST_START( PropertyFixture, Property_int_stdCtor_unset )
{
	libcsc::Property<int> p;
	CHECK( p.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_int_copyCtorProperty_123 )
{
	libcsc::Property<int> p( 123 );
	libcsc::Property<int> pCopy( p );
	CHECK_EQUAL( libcsc::Property<int>( 123 ), pCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_int_copyCtorProperty_dirty )
{
	libcsc::Property<int> p( 0 );
	libcsc::Property<int> pCopy( p );
	CHECK( pCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_int_copyCtorInt_123 )
{
	libcsc::Property<int> p( 123 );
	CHECK_EQUAL( 123, p.operator const int &() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_int_copyCtorBasarInt32_dirty )
{
	libcsc::Property<int> p( 0 );
	CHECK( p.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, constOperatorInt_123_keeps123 )
{
	libcsc::Property<int> p( 123 );
	const int & i = p.operator const int &();
	CHECK_EQUAL( 123, i );
	CHECK_EQUAL( 123, p.operator const int &() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, constOperatorInt_clean_keepsClean )
{
	libcsc::Property<int> p( 123 );
	p.setClean();
	const int & i = p.operator const int &(); i;
	CHECK( p.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, get_123_keeps123 )
{
	libcsc::Property<int> p( 123 );
	const int & i = p.get();
	CHECK_EQUAL( 123, i );
	CHECK_EQUAL( 123, p.get() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, get_clean_keepsClean )
{
	libcsc::Property<int> p( 123 );
	p.setClean();
	const int & i = p.get(); i;
	CHECK( p.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_unsetUnset_equal )
{
	libcsc::Property<int> p1( 123 );
	p1.setUnset();
	libcsc::Property<int> p2;
	CHECK_EQUAL( true, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_unsetDirty_notEqual )
{
	libcsc::Property<int> p1;
	libcsc::Property<int> p2;
	p2.setDirty();
	CHECK_EQUAL( false, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_valuesEqualStatesNotEqual_equal )
{
	libcsc::Property<int> p1( 4711 );
	p1.setClean();
	libcsc::Property<int> p2( 4711 );
	CHECK_EQUAL( true, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_valuesEqualStatesEqual_equal )
{
	libcsc::Property<int> p1( 4711 );
	p1.setClean();
	libcsc::Property<int> p2( 4711 );
	p2.setClean();
	CHECK_EQUAL( true, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_valuesNotEqualStatesEqual_notEqual )
{
	libcsc::Property<int> p1( 42 );
	p1.setClean();
	libcsc::Property<int> p2( 4711 );
	p2.setClean();
	CHECK_EQUAL( false, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, operatorEqual_valuesNotEqualStatesNotEqual_notEqual )
{
	libcsc::Property<int> p1( 42 );
	p1.setClean();
	libcsc::Property<int> p2( 4711 );
	p2.setDirty();
	CHECK_EQUAL( false, p1.operator==( p2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, int_toStream_123_string123 )
{
	libcsc::Property<int> p( 123 );
	std::stringstream ss;
	p.toStream( ss );
	CHECK_EQUAL( "123 (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, constOperatorInt_unset_exception )
{
	libcsc::Property<int> p;
	int i;
	CHECK_THROW( i = p, libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, int_toStream_unset_stringUNSET )
{
	libcsc::Property<int> p;
	std::stringstream ss;
	p.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END




enum TestEnum
{
	THE_ANSWER = 42
};

FIXTURE_TEST_START( PropertyFixture, Property_TestEnum_copyCtorProperty_THE_ANSWER )
{
	libcsc::Property<TestEnum> p( THE_ANSWER );
	libcsc::Property<TestEnum> pCopy( p );
	CHECK_EQUAL( libcsc::Property<TestEnum>( THE_ANSWER ), pCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_TestEnum_copyCtorTestEnum_THE_ANSWER )
{
	libcsc::Property<TestEnum> p( THE_ANSWER );
	CHECK_EQUAL( THE_ANSWER, p.operator const TestEnum &() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, TestEnum_toStream_THE_ANSWER_string42 )
{
	libcsc::Property<TestEnum> p( THE_ANSWER );
	std::stringstream ss;
	p.toStream( ss );
	CHECK_EQUAL( "42 (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END




FIXTURE_TEST_START( PropertyFixture, Property_string_copyCtorProperty_Blubb )
{
	libcsc::Property<std::string> p( "Blubb" );
	libcsc::Property<std::string> pCopy( p );
	CHECK_EQUAL( libcsc::Property<std::string>( "Blubb" ), pCopy );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, Property_string_copyCtorString_Blubb )
{
	libcsc::Property<std::string> p( std::string( "Blubb" ) );
	CHECK_EQUAL( std::string( "Blubb" ), p.operator const std::string &() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyFixture, string_toStream_Blubb_stringBlubb )
{
	libcsc::Property<std::string> p( "Blubb" );
	std::stringstream ss;
	p.toStream( ss );
	CHECK_EQUAL( "Blubb (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END


} // end TESTSUITE
} // end namespace libutilUnitTest

