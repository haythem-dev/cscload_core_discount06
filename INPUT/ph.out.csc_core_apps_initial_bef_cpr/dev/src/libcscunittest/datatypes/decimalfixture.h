#ifndef GUARD_LIBCSC_UNITTEST_DECIMAL_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_DECIMAL_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestDecimal
{
class DecimalFixture : public libutil::unittest::TestFixtureBase
{
public:
	DecimalFixture();
	virtual	~DecimalFixture();

protected:

private:
	DecimalFixture( const DecimalFixture & );
	DecimalFixture operator=( const DecimalFixture & );
};

} // end namespace SuiteTestDecimal
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_DECIMAL_FIXTURE_H
