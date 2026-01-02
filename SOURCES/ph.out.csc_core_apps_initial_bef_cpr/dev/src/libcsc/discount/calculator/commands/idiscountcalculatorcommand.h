#ifndef GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_H

#include "discount/calculator/discountcalculatorresult.h"

namespace libcsc
{
namespace discount
{
class IDiscountCalculatorCommand
{
public:
	virtual ~IDiscountCalculatorCommand() {}

	virtual const DiscountCalculatorResult & calculate() const = 0;
	virtual void processResult() const = 0;
	virtual void logHierarchy() const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_CALCULATOR_COMMAND_H
