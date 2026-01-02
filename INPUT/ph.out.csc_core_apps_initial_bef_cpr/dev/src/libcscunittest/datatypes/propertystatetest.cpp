#include "cmnut.h"
#include "propertystatefixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE( TestPropertyState )
{
//										  methodName_condition_expectation
FIXTURE_TEST_START( PropertyStateFixture, PropertyState_stdCtor_isUnset )
{
	PropertyState4Test ps;
	CHECK( ps.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, PropertyState_clean_isClean )
{
	PropertyState4Test ps( libcsc::CLEAN );
	CHECK( ps.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, operatorEqual_unsetUnset_equal )
{
	PropertyState4Test ps1;
	PropertyState4Test ps2;
	CHECK_EQUAL( true, ps1.operator==( ps2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, operatorEqual_dirtyDirty_equal )
{
	PropertyState4Test ps1;
	ps1.setDirty();
	PropertyState4Test ps2;
	ps2.setDirty();
	CHECK_EQUAL( true, ps1.operator==( ps2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, operatorEqual_dirtyClean_notEqual )
{
	PropertyState4Test ps1;
	ps1.setDirty();
	PropertyState4Test ps2;
	ps2.setClean();
	CHECK_EQUAL( false, ps1.operator==( ps2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setState_clean_isClean )
{
	PropertyState4Test ps( libcsc::UNSET );
	ps.setState( libcsc::CLEAN );
	CHECK( ps.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setUnset_unset_isUnset )
{
	PropertyState4Test ps( libcsc::UNSET );
	ps.setUnset();
	CHECK( ps.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setUnset_clean_isUnset )
{
	PropertyState4Test ps( libcsc::CLEAN );
	ps.setUnset();
	CHECK( ps.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setUnset_dirty_isUnset )
{
	PropertyState4Test ps( libcsc::DIRTY );
	ps.setUnset();
	CHECK( ps.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setClean_clean_isClean )
{
	PropertyState4Test ps( libcsc::CLEAN );
	ps.setClean();
	CHECK( ps.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setClean_unset_isClean )
{
	PropertyState4Test ps( libcsc::UNSET );
	ps.setClean();
	CHECK( ps.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setClean_dirty_isClean )
{
	PropertyState4Test ps( libcsc::DIRTY );
	ps.setClean();
	CHECK( ps.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setDirty_dirty_isDirty )
{
	PropertyState4Test ps( libcsc::DIRTY );
	ps.setDirty();
	CHECK( ps.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setDirty_unset_isDirty )
{
	PropertyState4Test ps( libcsc::UNSET );
	ps.setDirty();
	CHECK( ps.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, setDirty_clean_isDirty )
{
	PropertyState4Test ps( libcsc::CLEAN );
	ps.setDirty();
	CHECK( ps.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( PropertyStateFixture, getState_dirty_isDirty )
{
	PropertyState4Test ps( libcsc::DIRTY );
	CHECK_EQUAL( libcsc::DIRTY, ps.getState() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

