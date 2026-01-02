#ifndef GUARD_LIBCSC_UNITTEST_PROPERTY_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_PROPERTY_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestProperty
{
class PropertyFixture : public libutil::unittest::TestFixtureBase
{
public:
	PropertyFixture();
	virtual	~PropertyFixture();

protected:

private:
	PropertyFixture( const PropertyFixture & );
	PropertyFixture operator=( const PropertyFixture & );
};

} // end namespace SuiteTestProperty
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_PROPERTY_FIXTURE_H
