#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_CHAIN_COMMAND_BASE_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_CHAIN_COMMAND_BASE_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"
#include "discount/calculator/commands/discountcalculatorcommandbaseptr.h"

/*
	NOT USED ATM, NOT TESTED
*/

namespace libcsc
{
namespace discount
{
class DiscountCalculatorChainCommandBase : public DiscountCalculatorCommandBase
{
public:
	DiscountCalculatorChainCommandBase( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultProcessing
			);
	virtual ~DiscountCalculatorChainCommandBase();

	void injectPreviousCalculator( DiscountCalculatorCommandBasePtr calculator );
	virtual void processResult() const;
	virtual void processResult( const DiscountCalculatorResult & result ) const;
	virtual void logHierarchy() const;

protected:
	const DiscountCalculatorCommandBasePtr getPreviousCalculator() const;
	const DiscountCalculatorResult & calculatePreviousResult() const;

private:
	DiscountCalculatorCommandBasePtr	m_PreviousCalculator;
	bool								m_DelegateResultProcessing;		// client is able to choose delegate or not
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_CHAIN_COMMAND_BASE_H
