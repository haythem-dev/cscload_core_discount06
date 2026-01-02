#ifndef GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SOURCE_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SOURCE_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
class DiscountSourceFixture : public libutil::unittest::TestFixtureBase
{
public:
	DiscountSourceFixture();
	virtual	~DiscountSourceFixture();

protected:
	libcsc::discount::DiscountSource	m_DiscountSource;

private:
	DiscountSourceFixture( const DiscountSourceFixture & );
	DiscountSourceFixture operator=( const DiscountSourceFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SOURCE_FIXTURE_H
