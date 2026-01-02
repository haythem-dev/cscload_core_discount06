#ifndef GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_INDUSTRY_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H
