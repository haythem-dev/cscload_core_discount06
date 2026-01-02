#ifndef GUARD_LIBCSC_BEST_OF_FOR_CUSTOMER_COMBINED_CALCULATOR_COMMAND_H
#define GUARD_LIBCSC_BEST_OF_FOR_CUSTOMER_COMBINED_CALCULATOR_COMMAND_H

#include "discount/calculator/commands/discountcalculatorcompositecommandbase.h"

namespace libcsc
{
namespace discount
{
class BestOf4CustomerCombinedCalculatorCommand : public DiscountCalculatorCompositeCommandBase
{
public:
	BestOf4CustomerCombinedCalculatorCommand( 
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultProcessing
			);
	virtual ~BestOf4CustomerCombinedCalculatorCommand();

protected:
	virtual const DiscountCalculatorResult & doCalculate() const;
	virtual void delegateResultProcessing() const;
	virtual void delegateResultProcessing( const DiscountCalculatorResult & result ) const;

private:
	struct WinnerStruct
	{
		IDiscountCalculatorCommandPtr		command;
		DiscountCalculatorResult			result;
	};

	enum DiscountType
	{
		DT_FIXED_PRICE = 1,
		DT_VALUE,
		DT_PERCENT,
		DT_REBATE_IN_KIND
	};

	void compare( 
		IDiscountCalculatorCommandPtr cmd,
		const DiscountCalculatorResult & rhs
			) const;
	void compareFixedPriceResults( 
		IDiscountCalculatorCommandPtr cmd,
		const DiscountCalculatorResult & rhs 
			) const;
	void compareValueResults( 
		IDiscountCalculatorCommandPtr cmd,
		const DiscountCalculatorResult & rhs 
			) const;
	void comparePercentResults( 
		IDiscountCalculatorCommandPtr cmd,
		const DiscountCalculatorResult & rhs 
			) const;
	void compareRebateInKindResults( 
		IDiscountCalculatorCommandPtr cmd,
		const DiscountCalculatorResult & rhs 
			) const;
	basar::Int32 compareResults( 
		const basar::Decimal & lhs, 
		const basar::Decimal & rhs
			) const;
	basar::Int32 compareRebateInKindQuantity( 
		const DiscountCalculatorResult & lhs, 
		const DiscountCalculatorResult & rhs 
			) const;
	const basar::Decimal getFixedPriceDiscountValue( 
		const DiscountResult & result,
		const DiscountResultBaseValue & baseValue
			) const;
	const basar::Decimal getValueDiscountValue( 
		const DiscountResult & result,
		const DiscountResultBaseValue & baseValue
			) const;
	const basar::Decimal getPercentDiscountValue( 
		const DiscountResult & result,
		const DiscountResultBaseValue & baseValue
			) const;
	const basar::Decimal getRebateInKindDiscountValue( 
		const DiscountCalculatorResult & result
			) const;
	void combineResults(
		DiscountCalculatorResult & result
			) const;
	WinnerStruct & getWinner( 
		const basar::Int32 positionNo,
		const DiscountType type
			) const;

	//struct WinnerStruct
	//{
	//	IDiscountCalculatorCommandPtr		fixedPriceCommand;
	//	DiscountCalculatorResult			fixedPriceResult;
	//	IDiscountCalculatorCommandPtr		valueCommand;
	//	DiscountCalculatorResult			valueResult;
	//	IDiscountCalculatorCommandPtr		percentCommand;
	//	DiscountCalculatorResult			percentResult;
	//	IDiscountCalculatorCommandPtr		rebateInKindCommand;
	//	DiscountCalculatorResult			rebateInKindResult;
	//};


	typedef std::map<DiscountType, WinnerStruct> TypeCollection;		// type -> winner
	typedef std::map<basar::Int32, TypeCollection> WinnerCollection;	// position -> list of winners

	mutable WinnerCollection		m_Winners;
	mutable WinnerStruct			m_RebateInKindWinner;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_BEST_OF_FOR_CUSTOMER_COMBINED_CALCULATOR_COMMAND_H
