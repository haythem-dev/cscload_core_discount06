#ifndef GUARD_LIBCSC_UNITTEST_DATETIME_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_DATETIME_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestDateTime
{
class DateTimeFixture : public libutil::unittest::TestFixtureBase
{
public:
	DateTimeFixture();
	virtual	~DateTimeFixture();

protected:

private:
	DateTimeFixture( const DateTimeFixture & );
	DateTimeFixture operator=( const DateTimeFixture & );
};

} // end namespace SuiteTestDateTime
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_DATETIME_FIXTURE_H
