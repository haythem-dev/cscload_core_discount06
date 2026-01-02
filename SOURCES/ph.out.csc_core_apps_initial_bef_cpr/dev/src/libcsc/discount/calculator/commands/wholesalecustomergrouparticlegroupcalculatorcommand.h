#ifndef GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"

namespace libcsc
{
namespace discount
{
class WholesaleCustomerGroupArticleGroupCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleCustomerGroupArticleGroupCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleCustomerGroupArticleGroupCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_GROUP_CALCULATOR_COMMAND_H
