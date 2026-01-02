#ifndef GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"
#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"

namespace libcsc
{
namespace discount
{
class WholesaleCustomerGroupArticleCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleCustomerGroupArticleCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleCustomerGroupArticleCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_CUSTOMER_GROUP_ARTICLE_CALCULATOR_COMMAND_H
