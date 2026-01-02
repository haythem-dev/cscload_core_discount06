#ifndef GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleIndustryCustomerGroupManufacturerCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleIndustryCustomerGroupManufacturerCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleIndustryCustomerGroupManufacturerCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_CALCULATOR_COMMAND_H
