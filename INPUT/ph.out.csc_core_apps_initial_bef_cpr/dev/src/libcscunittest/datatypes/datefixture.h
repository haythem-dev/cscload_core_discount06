#ifndef GUARD_LIBCSC_UNITTEST_DATE_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_DATE_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestDate
{
class DateFixture : public libutil::unittest::TestFixtureBase
{
public:
	DateFixture();
	virtual	~DateFixture();

protected:

private:
	DateFixture( const DateFixture & );
	DateFixture operator=( const DateFixture & );
};

} // end namespace SuiteTestDate
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_DATE_FIXTURE_H
