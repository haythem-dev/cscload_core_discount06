#ifndef GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleAllCustomerManufacturerGroupCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleAllCustomerManufacturerGroupCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleAllCustomerManufacturerGroupCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H
