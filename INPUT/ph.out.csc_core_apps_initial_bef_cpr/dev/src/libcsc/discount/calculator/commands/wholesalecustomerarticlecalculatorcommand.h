#ifndef GUARD_LIBCSC_WHOLESALE_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"
#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"

namespace libcsc
{
namespace discount
{
class WholesaleCustomerArticleCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleCustomerArticleCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleCustomerArticleCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H
