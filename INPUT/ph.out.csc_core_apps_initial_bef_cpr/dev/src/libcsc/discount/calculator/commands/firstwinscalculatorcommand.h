#ifndef GUARD_LIBCSC_FIRST_WINS_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_FIRST_WINS_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcompositecommandbase.h"

namespace libcsc
{
namespace discount
{
class FirstWinsCalculatorCommand : public DiscountCalculatorCompositeCommandBase
{
public:
	FirstWinsCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultProcessing
			);
	virtual ~FirstWinsCalculatorCommand();

protected:
	virtual const DiscountCalculatorResult & doCalculate() const;
	virtual void delegateResultProcessing() const;
	virtual void delegateResultProcessing( const DiscountCalculatorResult & result ) const;

private:
	mutable libcsc::discount::IDiscountCalculatorCommandPtr		m_Winner;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_FIRST_WINS_CALCULATOR_COMMAND_H
