#ifndef GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleAllCustomerManufacturerCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleAllCustomerManufacturerCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleAllCustomerManufacturerCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
