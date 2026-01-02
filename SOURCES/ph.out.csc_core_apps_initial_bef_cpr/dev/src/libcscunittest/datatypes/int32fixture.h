#ifndef GUARD_LIBCSC_UNITTEST_INT32_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_INT32_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestInt32
{
class Int32Fixture : public libutil::unittest::TestFixtureBase
{
public:
	Int32Fixture();
	virtual	~Int32Fixture();

protected:

private:
	Int32Fixture( const Int32Fixture & );
	Int32Fixture operator=( const Int32Fixture & );
};

} // end namespace SuiteTestInt32
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_INT32_FIXTURE_H
