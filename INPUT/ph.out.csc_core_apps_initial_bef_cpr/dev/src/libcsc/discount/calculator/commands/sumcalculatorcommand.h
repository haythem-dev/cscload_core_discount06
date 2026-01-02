#ifndef GUARD_LIBCSC_SUM_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_SUM_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcompositecommandbase.h"

namespace libcsc
{
namespace discount
{
class SumCalculatorCommand : public DiscountCalculatorCompositeCommandBase
{
public:
	SumCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultProcessing
			);
	virtual ~SumCalculatorCommand();

protected:
	virtual const DiscountCalculatorResult & doCalculate() const;
	virtual void delegateResultProcessing() const;
	virtual void delegateResultProcessing( const DiscountCalculatorResult & result ) const;

private:
	void addResult( 
		DiscountCalculatorResult & result, 
		const DiscountCalculatorResult & rhs
			) const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_SUM_CALCULATOR_COMMAND_H
