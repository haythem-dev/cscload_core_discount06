#ifndef GUARD_LIBCSC_UNITTEST_COMMON_REBATE_IN_KIND_VALUE_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_REBATE_IN_KIND_VALUE_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
class RebateInKindValueFixture : public libutil::unittest::TestFixtureBase
{
public:
	RebateInKindValueFixture();
	virtual	~RebateInKindValueFixture();

protected:
	libcsc::discount::RebateInKindValue		m_RebateInKindValue;

private:
	RebateInKindValueFixture( const RebateInKindValueFixture & );
	RebateInKindValueFixture operator=( const RebateInKindValueFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_REBATE_IN_KIND_VALUE_FIXTURE_H
