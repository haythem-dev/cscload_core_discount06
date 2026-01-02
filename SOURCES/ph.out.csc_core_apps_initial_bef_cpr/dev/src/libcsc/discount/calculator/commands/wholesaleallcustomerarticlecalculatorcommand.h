#ifndef GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"
#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"

namespace libcsc
{
namespace discount
{
class WholesaleAllCustomerArticleCalculatorCommand : public DiscountCalculatorCommandBase
{
public:
	WholesaleAllCustomerArticleCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType
			);
	virtual ~WholesaleAllCustomerArticleCalculatorCommand();

	virtual const DiscountCalculatorResult & calculate() const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_WHOLESALE_ALL_CUSTOMER_ARTICLE_CALCULATOR_COMMAND_H
