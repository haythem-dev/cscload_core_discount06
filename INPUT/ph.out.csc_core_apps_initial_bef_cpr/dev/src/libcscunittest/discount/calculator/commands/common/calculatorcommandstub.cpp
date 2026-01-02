#include "cmnut.h"
#include "calculatorcommandstub.h"

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
CalculatorCommandStub::CalculatorCommandStub( 
	const libcsc::discount::DiscountCalculatorResult & result
		)
: m_Result( result )
{
}

CalculatorCommandStub::~CalculatorCommandStub()
{
}

const libcsc::discount::DiscountCalculatorResult & CalculatorCommandStub::calculate() const
{
	return m_Result;
}

void CalculatorCommandStub::processResult() const
{
}

void CalculatorCommandStub::logHierarchy() const
{
}

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

