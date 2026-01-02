#include "cmnut.h"
#include "varstringfixture.h"
#include <datatypes/varstring.h>
#include <sstream>
#include <exceptions/propertyunsetexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestVarString )
{
//									methodName_condition_expectation
FIXTURE_TEST_START( VarStringFixture, stdCtor_Empty_Empty )
{
	libcsc::VarString s( "" );
	CHECK( s == basar::VarString( "" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, stdCtor_unset_unset )
{
	libcsc::VarString s;
	CHECK( s.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorCscVarString_Hello_Hello )
{
	libcsc::VarString s( basar::VarString( "Hello" ) );
	libcsc::VarString sCopy( s );
	CHECK( sCopy == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorCscVarString_Empty_dirty )
{
	libcsc::VarString s( basar::VarString( "" ) );
	libcsc::VarString sCopy( s );
	CHECK( sCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorBasarVarString_Hello_Hello )
{
	libcsc::VarString s( basar::VarString( "Hello" ) );
	CHECK( s == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorBasarVarString_Empty_dirty )
{
	libcsc::VarString s( basar::VarString( "" ) );
	CHECK( s.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorStdString_Hello_Hello )
{
	libcsc::VarString s( std::string( "Hello" ) );
	CHECK( s == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorStdString_Empty_dirty )
{
	libcsc::VarString s( std::string( "" ) );
	CHECK( s.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorCharPtr_Hello_Hello )
{
	const char * c = "Hello";
	libcsc::VarString s( c );
	CHECK( s == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, copyCtorCharPtr_Empty_dirty )
{
	const char * c = "";
	libcsc::VarString s( c );
	CHECK( s.isDirty() );
}
FIXTURE_TEST_END

//FIXTURE_TEST_START( VarStringFixture, copyCtorCharPtr_NULL_dirty )
//{
//	const char * c = NULL;
//	libcsc::VarString s( c );
//	CHECK( s.isDirty() );
//}
//FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorCscVarString_Hello_Hello )
{
	libcsc::VarString s( "Hello" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorCscVarString_Empty_dirty )
{
	libcsc::VarString s( "" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorBasarVarString_Hello_Hello )
{
	basar::VarString s( "Hello" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorBasarVarString_Empty_dirty )
{
	basar::VarString s( "" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorStdString_Hello_Hello )
{
	std::string s( "Hello" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorStdString_Empty_dirty )
{
	std::string s( "" );
	libcsc::VarString sCopy;
	sCopy.operator=( s );
	CHECK( sCopy.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorCharPtr_Hello_Hello )
{
	const char * c = "Hello";
	libcsc::VarString sCopy;
	sCopy.operator=( c );
	CHECK( sCopy == basar::VarString( "Hello" ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, assignOperatorCharPtr_Empty_dirty )
{
	const char * c = "";
	libcsc::VarString sCopy;
	sCopy.operator=( c );
	CHECK( sCopy.isDirty() );
}
FIXTURE_TEST_END

//FIXTURE_TEST_START( VarStringFixture, assignOperatorCharPtr_NULL_dirty )
//{
//	const char * c = NULL;
//	libcsc::VarString sCopy;
//	sCopy.operator=( c );
//	CHECK( sCopy.isDirty() );
//}
//FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorCscVarString_Equal_true )
{
	libcsc::VarString s( "Hello" );
	libcsc::VarString bs( "Hello" );
	
	CHECK_EQUAL( true, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorCscVarString_NotEqual_false )
{
	libcsc::VarString s( "Hello" );
	libcsc::VarString bs( "World" );
	
	CHECK_EQUAL( false, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorBasarVarString_Equal_true )
{
	libcsc::VarString s( "Hello" );
	basar::VarString bs( "Hello" );
	
	CHECK_EQUAL( true, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorBasarVarString_NotEqual_false )
{
	libcsc::VarString s( "Hello" );
	basar::VarString bs( "World" );
	
	CHECK_EQUAL( false, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorStdVarString_Equal_true )
{
	libcsc::VarString s( "Hello" );
	std::string bs( "Hello" );
	
	CHECK_EQUAL( true, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorStdVarString_NotEqual_false )
{
	libcsc::VarString s( "Hello" );
	std::string bs( "World" );
	
	CHECK_EQUAL( false, s.operator==( bs ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorCharPtr_Equal_true )
{
	libcsc::VarString s( "Hello" );
	const char * c = "Hello";
	
	CHECK_EQUAL( true, s.operator==( c ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, equalOperatorCharPtr_NotEqual_false )
{
	libcsc::VarString s( "Hello" );
	const char * c = "World";
	
	CHECK_EQUAL( false, s.operator==( c ) );
}
FIXTURE_TEST_END

// no tests for notEqualOperator, because it's implemented with equalOperator

FIXTURE_TEST_START( VarStringFixture, constOperatorBasarVarString_Hello_keepsHello )
{
	libcsc::VarString s( "Hello" );
	const basar::VarString & bs = s.operator const basar::VarString & ();
	CHECK_EQUAL( "Hello", bs );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, constOperatorBasarVarString_clean_keepsClean )
{
	libcsc::VarString s( "Hello" );
	s.setClean();
	const basar::VarString & bs = s.operator const basar::VarString & (); bs;
	CHECK( s.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, constOperatorBasarVarString_unset_exception )
{
	libcsc::VarString s;
	basar::VarString bs;
	CHECK_THROW( bs = s.operator const basar::VarString & (), libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END
	
void callWithConstStdString( const std::string & value )
{
	CHECK_EQUAL( "Hello", value );
}

FIXTURE_TEST_START( VarStringFixture, constOperatorBasarVarString_implicitConversion_works )
{
	libcsc::VarString s( "Hello" );
	callWithConstStdString( s );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, c_str_Hello_keepsHello )
{
	libcsc::VarString s( "Hello" );
	const char * c = s.c_str();
	CHECK_EQUAL( "Hello", c );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, c_str_unset_exception )
{
	libcsc::VarString s;
	const char * c;
	CHECK_THROW( c = s.c_str(), libcsc::exceptions::PropertyUnsetException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, toStream_Hello_stringHello )
{
	libcsc::VarString s( basar::VarString( "Hello" ) );
	std::stringstream ss;
	s.toStream( ss );
	CHECK_EQUAL( "Hello (DIRTY)", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( VarStringFixture, toStream_unset_stringUNSET )
{
	libcsc::VarString s;
	std::stringstream ss;
	s.toStream( ss );
	CHECK_EQUAL( "UNSET", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

