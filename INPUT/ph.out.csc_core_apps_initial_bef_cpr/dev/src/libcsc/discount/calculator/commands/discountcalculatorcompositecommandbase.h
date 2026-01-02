#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMPOSITE_COMMAND_BASE_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMPOSITE_COMMAND_BASE_H

#include "discount/calculator/commands/discountcalculatorcommandbase.h"
#include "discount/calculator/commands/idiscountcalculatorcommandptr.h"
#include <vector>

namespace libcsc
{
namespace discount
{
typedef std::vector<libcsc::discount::IDiscountCalculatorCommandPtr> CalculatorCollection;

class DiscountCalculatorCompositeCommandBase : public DiscountCalculatorCommandBase
{
public:
	DiscountCalculatorCompositeCommandBase( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultProcessing
			);
	virtual ~DiscountCalculatorCompositeCommandBase();

	void add( IDiscountCalculatorCommandPtr calculator );
	virtual const DiscountCalculatorResult & calculate() const;
	virtual void processResult() const;
	virtual void processResult( const DiscountCalculatorResult & result ) const;
	virtual void logHierarchy() const;

protected:
	virtual const DiscountCalculatorResult & doCalculate() const = 0;
	const CalculatorCollection & getCalculatorCollection() const;
	virtual void delegateResultProcessing() const = 0;
	virtual void delegateResultProcessing( const DiscountCalculatorResult & result ) const = 0;
	void copyFixedPriceValues( 
		DiscountResult & destination, 
		const DiscountResult & source 
			) const;
	void copyValueDiscountValues( 
		DiscountResult & destination, 
		const DiscountResult & source 
			) const;
	void copyPercentValues( 
		DiscountResult & destination, 
		const DiscountResult & source 
			) const;
	void copyRebateInKindValues( 
		DiscountCalculatorResult & destination, 
		const DiscountCalculatorResult & source 
			) const;
	void combineRebateInKindValues( 
		DiscountCalculatorResult & destination, 
		const DiscountCalculatorResult & source 
			) const;

private:
	CalculatorCollection	m_CalculatorCollection;
	bool					m_DelegateResultProcessing;		// client is able to choose delegate or not
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMPOSITE_COMMAND_BASE_H
