#ifndef GUARD_LIBCSC_FIXED_PRICE_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_FIXED_PRICE_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class FixedPriceCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	FixedPriceCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~FixedPriceCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_FIXED_PRICE_CALCULATOR_COMMAND_H
