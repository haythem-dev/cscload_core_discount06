#ifndef GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleIndustryAllCustomerManufacturerCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleIndustryAllCustomerManufacturerCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleIndustryAllCustomerManufacturerCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
