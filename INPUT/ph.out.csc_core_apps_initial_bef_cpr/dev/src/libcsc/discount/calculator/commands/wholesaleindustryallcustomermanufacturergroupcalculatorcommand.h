#ifndef GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleIndustryAllCustomerManufacturerGroupCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleIndustryAllCustomerManufacturerGroupCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleIndustryAllCustomerManufacturerGroupCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_GROUP_CALCULATOR_COMMAND_H
