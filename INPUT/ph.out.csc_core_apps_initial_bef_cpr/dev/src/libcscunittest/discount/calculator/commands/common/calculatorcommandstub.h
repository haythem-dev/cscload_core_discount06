#ifndef GUARD_LIBCSC_UNITTEST_CALCULATOR_COMMAND_STUB_H
#define GUARD_LIBCSC_UNITTEST_CALCULATOR_COMMAND_STUB_H

#include <discount/calculator/commands/idiscountcalculatorcommand.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
class CalculatorCommandStub : public libcsc::discount::IDiscountCalculatorCommand
{
public:
	CalculatorCommandStub( 
		const libcsc::discount::DiscountCalculatorResult & result
			);
	virtual ~CalculatorCommandStub();

	virtual const libcsc::discount::DiscountCalculatorResult & calculate() const;
	virtual void processResult() const;
	virtual void logHierarchy() const;

private:
	CalculatorCommandStub( const CalculatorCommandStub & );
	CalculatorCommandStub & operator=( const CalculatorCommandStub & );

	const libcsc::discount::DiscountCalculatorResult		m_Result;
};

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_CALCULATOR_COMMAND_STUB_H
