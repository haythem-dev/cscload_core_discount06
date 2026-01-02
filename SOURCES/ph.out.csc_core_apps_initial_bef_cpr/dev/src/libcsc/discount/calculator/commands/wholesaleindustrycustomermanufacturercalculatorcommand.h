#ifndef GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleIndustryCustomerManufacturerCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleIndustryCustomerManufacturerCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleIndustryCustomerManufacturerCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_MANUFACTURER_CALCULATOR_COMMAND_H
