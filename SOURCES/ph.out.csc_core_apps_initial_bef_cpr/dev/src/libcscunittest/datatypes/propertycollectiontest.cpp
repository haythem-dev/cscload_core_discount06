#include "cmnut.h"
#include "propertycollectionfixture.h"
#include <exceptions/emptycollectionexception.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc;

SUITE( TestPropertyCollection )
{
//											   methodName_condition_expectation
FIXTURE_TEST_START( PropertyCollectionFixture, isUnset_empty_exception )
{
	PropertyCollection pc;
	CHECK_THROW( pc.isUnset(), libcsc::exceptions::EmptyCollectionException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, operatorEqual_emptyEmpty_true )
{
	PropertyCollection pc1;
	PropertyCollection pc2;
	CHECK_EQUAL( true, pc1.operator==( pc2 ) );
}
FIXTURE_TEST_END

struct PropertyCollectionTestStruct
{
	libcsc::Decimal dec2;
	libcsc::Int32 int2;
	libcsc::VarString string2;
	libcsc::DateTime dateTime2;
} dummy;

FIXTURE_TEST_START( PropertyCollectionFixture, operatorEqual_equalSizeEqualStates_true )
{
	m_Decimal.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();

	PropertyCollection pc2;
	pc2.add( dummy.dec2 );
	pc2.add( dummy.int2 );
	pc2.add( dummy.string2 );
	pc2.add( dummy.dateTime2 );
	dummy.dec2.setClean();
	dummy.string2.setClean();
	dummy.dateTime2.setClean();

	CHECK_EQUAL( true, m_Collection.operator==( pc2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, operatorEqual_equalSizeDifferentStates_false )
{
	m_Decimal.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();

	PropertyCollection pc2;
	pc2.add( dummy.dec2 );
	pc2.add( dummy.int2 );
	pc2.add( dummy.string2 );
	pc2.add( dummy.dateTime2 );
	dummy.dec2.setDirty();
	dummy.string2.setClean();
	dummy.dateTime2.setUnset();

	CHECK_EQUAL( false, m_Collection.operator==( pc2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, operatorEqual_differentSize_false )
{
	m_Decimal.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();

	PropertyCollection pc2;
	pc2.add( dummy.dec2 );
	pc2.add( dummy.string2 );
	pc2.add( dummy.dateTime2 );

	CHECK_EQUAL( false, m_Collection.operator==( pc2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isUnset_allUnset_true )
{
	CHECK_EQUAL( true, m_Collection.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isUnset_1Unset_false )
{
	m_Decimal.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();
	CHECK_EQUAL( false, m_Collection.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isClean_empty_exception )
{
	PropertyCollection pc;
	CHECK_THROW( pc.isClean(), libcsc::exceptions::EmptyCollectionException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isClean_allClean_true )
{
	m_Decimal.setClean();
	m_Int32.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();
	CHECK_EQUAL( true, m_Collection.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isClean_1Clean_false )
{
	m_VarString.setClean();
	CHECK_EQUAL( false, m_Collection.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isDirty_empty_exception )
{
	PropertyCollection pc;
	CHECK_THROW( pc.isDirty(), libcsc::exceptions::EmptyCollectionException );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isDirty_allDirty_true )
{
	m_Decimal.setDirty();
	m_Int32.setDirty();
	m_VarString.setDirty();
	m_DateTime.setDirty();
	CHECK_EQUAL( true, m_Collection.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, isDirty_1Dirty_false )
{
	m_VarString.setDirty();
	CHECK_EQUAL( false, m_Collection.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsUnset_empty_false )
{
	PropertyCollection pc;
	CHECK_EQUAL( false, pc.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsUnset_allUnset_true )
{
	CHECK_EQUAL( true, m_Collection.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsUnset_1Unset_true )
{
	m_Decimal.setDirty();
	m_Int32.setDirty();
	m_VarString.setDirty();
	CHECK_EQUAL( true, m_Collection.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsClean_empty_false )
{
	PropertyCollection pc;
	CHECK_EQUAL( false, pc.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsClean_allClean_true )
{
	m_Decimal.setClean();
	m_Int32.setClean();
	m_VarString.setClean();
	m_DateTime.setClean();
	CHECK_EQUAL( true, m_Collection.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsClean_1Clean_true )
{
	m_Decimal.setClean();
	CHECK_EQUAL( true, m_Collection.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsDirty_empty_false )
{
	PropertyCollection pc;
	CHECK_EQUAL( false, pc.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsDirty_allDirty_true )
{
	m_Decimal.setDirty();
	m_Int32.setDirty();
	m_VarString.setDirty();
	m_DateTime.setDirty();
	CHECK_EQUAL( true, m_Collection.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyCollectionFixture, containsDirty_1Dirty_true )
{
	m_Decimal.setDirty();
	CHECK_EQUAL( true, m_Collection.containsDirty() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

