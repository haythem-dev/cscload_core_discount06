#ifndef GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_RESULT_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_RESULT_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/calculator/discountcalculatorresult.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
class DiscountCalculatorResultFixture : public libutil::unittest::TestFixtureBase
{
public:
	DiscountCalculatorResultFixture();
	virtual	~DiscountCalculatorResultFixture();

protected:
	const libcsc::discount::DiscountResultBaseValue getDiscountResultBaseValue() const;
	const libcsc::discount::DiscountResult getDiscountResult() const;
	const libcsc::discount::RebateInKindValue getRebateInKindValue() const;

	const libcsc::discount::DiscountResultBaseValue getCleanDiscountResultBaseValue() const;
	const libcsc::discount::DiscountResult getCleanDiscountResult() const;
	const libcsc::discount::RebateInKindValue getCleanRebateInKindValue() const;

	const libcsc::discount::DiscountResultBaseValue getUnsetDiscountResultBaseValue() const;
	const libcsc::discount::DiscountResult getUnsetDiscountResult() const;
	const libcsc::discount::RebateInKindValue getUnsetRebateInKindValue() const;

	libcsc::discount::DiscountCalculatorResult	m_DiscountCalculatorResult;

private:
	DiscountCalculatorResultFixture( const DiscountCalculatorResultFixture & );
	DiscountCalculatorResultFixture operator=( const DiscountCalculatorResultFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_RESULT_FIXTURE_H
