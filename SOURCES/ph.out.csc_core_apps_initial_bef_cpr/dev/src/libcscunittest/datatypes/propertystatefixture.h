#ifndef GUARD_LIBCSC_UNITTEST_PROPERTY_STATE_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_PROPERTY_STATE_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <datatypes/propertystate.h>

namespace libcscUnitTest
{
namespace SuiteTestPropertyState
{
class PropertyState4Test : public libcsc::PropertyState
{
	// derived, because class PropertyState is abstract
public:
	PropertyState4Test() : PropertyState()
	{
	}

	PropertyState4Test( const libcsc::PropertyStateEnum state ) : PropertyState( state )
	{
	}
};

class PropertyStateFixture : public libutil::unittest::TestFixtureBase
{
public:
	PropertyStateFixture();
	virtual	~PropertyStateFixture();

protected:

private:
	PropertyStateFixture( const PropertyStateFixture & );
	PropertyStateFixture operator=( const PropertyStateFixture & );
};

} // end namespace SuiteTestPropertyState
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_PROPERTY_STATE_FIXTURE_H
