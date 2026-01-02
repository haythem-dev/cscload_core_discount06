#ifndef GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
class DiscountResultFixture : public libutil::unittest::TestFixtureBase
{
public:
	DiscountResultFixture();
	virtual	~DiscountResultFixture();

protected:
	libcsc::discount::DiscountResult	m_DiscountResult;

private:
	DiscountResultFixture( const DiscountResultFixture & );
	DiscountResultFixture operator=( const DiscountResultFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_FIXTURE_H
