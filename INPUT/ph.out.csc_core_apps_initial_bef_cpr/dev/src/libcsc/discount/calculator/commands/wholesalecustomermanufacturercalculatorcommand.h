#ifndef GUARD_LIBCSC_WHOLESALE_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleCustomerManufacturerCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleCustomerManufacturerCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleCustomerManufacturerCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
