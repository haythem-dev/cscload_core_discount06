#ifndef GUARD_LIBCSC_UNITTEST_VARSTRING_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_VARSTRING_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestVarString
{
class VarStringFixture : public libutil::unittest::TestFixtureBase
{
public:
	VarStringFixture();
	virtual	~VarStringFixture();

protected:

private:
	VarStringFixture( const VarStringFixture & );
	VarStringFixture operator=( const VarStringFixture & );
};

} // end namespace SuiteTestVarString
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_VARSTRING_FIXTURE_H
