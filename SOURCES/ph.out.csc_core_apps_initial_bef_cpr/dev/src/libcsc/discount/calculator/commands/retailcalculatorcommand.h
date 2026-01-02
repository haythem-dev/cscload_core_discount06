#ifndef GUARD_LIBCSC_RETAIL_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_RETAIL_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class RetailCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	RetailCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~RetailCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_RETAIL_CALCULATOR_COMMAND_H
