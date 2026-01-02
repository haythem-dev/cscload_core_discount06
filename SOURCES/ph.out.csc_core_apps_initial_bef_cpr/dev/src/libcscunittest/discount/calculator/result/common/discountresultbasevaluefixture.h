#ifndef GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_BASE_VALUE_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_BASE_VALUE_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
class DiscountResultBaseValueFixture : public libutil::unittest::TestFixtureBase
{
public:
	DiscountResultBaseValueFixture();
	virtual	~DiscountResultBaseValueFixture();

protected:
	libcsc::discount::DiscountResultBaseValue	m_DiscountResultBaseValue;

private:
	DiscountResultBaseValueFixture( const DiscountResultBaseValueFixture & );
	DiscountResultBaseValueFixture operator=( const DiscountResultBaseValueFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_RESULT_BASE_VALUE_FIXTURE_H
