#include "hrpositiondiscountcalculatorcomponentmanager.h"
#include <discount/calculator/commands/discountcalculatorcompositecommandbase.h>

namespace libcsc
{
namespace discount
{
HRPositionDiscountCalculatorComponentManager::HRPositionDiscountCalculatorComponentManager()
{
}

HRPositionDiscountCalculatorComponentManager::~HRPositionDiscountCalculatorComponentManager()
{
}

IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::getDiscountCalculator()
{
	return createSumAll( CT_ROOT );
}

// composite calculators
IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::createSumAll(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createSum( parentCalcType, CT_HR_SUM_ALL_TYPE, true ) );
	calc->add( createFixedPrice( CT_HR_SUM_ALL_TYPE ) );
	calc->add( createSumRetailWholesaleWholesaleIndustry( CT_HR_SUM_ALL_TYPE ) );
	return calc;
}

//IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::createFixedPriceBeatsAll(
//	const DiscountCalculatorTypeEnum parentCalcType
//		) const
//{
//	DiscountCalculatorCompositeCommandBasePtr calc( createFirstWins( parentCalcType, CT_HR_FIXED_PRICE_BEATS_ALL_TYPE, true ) );
//	calc->add( createFixedPrice( CT_HR_FIXED_PRICE_BEATS_ALL_TYPE ) );
//	calc->add( createSumRetailWholesaleWholesaleIndustry( CT_HR_FIXED_PRICE_BEATS_ALL_TYPE ) );
//	return calc;
//}

IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::createSumRetailWholesaleWholesaleIndustry(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createSum( parentCalcType, CT_HR_SUM_RE_WH_WI_TYPE, true ) );
	calc->add( createRetail( CT_HR_SUM_RE_WH_WI_TYPE ) );
	calc->add( createFirstWinsWholesale( CT_HR_SUM_RE_WH_WI_TYPE ) );
	calc->add( createFirstWinsWholesaleIndustry( CT_HR_SUM_RE_WH_WI_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::createFirstWinsWholesale(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createFirstWins( parentCalcType, CT_HR_FIRST_WINS_WH_TYPE, true ) );
	calc->add( createWholesaleCustomerArticle( CT_HR_FIRST_WINS_WH_TYPE ) );
	calc->add( createWholesaleCustomerGroupArticle( CT_HR_FIRST_WINS_WH_TYPE ) );
	calc->add( createWholesaleAllCustomerArticle( CT_HR_FIRST_WINS_WH_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HRPositionDiscountCalculatorComponentManager::createFirstWinsWholesaleIndustry(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createFirstWins( parentCalcType, CT_HR_FIRST_WINS_WI_TYPE, true ) );
	calc->add( createWholesaleIndustryCustomerArticle( CT_HR_FIRST_WINS_WI_TYPE ) );
	calc->add( createWholesaleIndustryCustomerGroupArticle( CT_HR_FIRST_WINS_WI_TYPE ) );
	calc->add( createWholesaleIndustryAllCustomerArticle( CT_HR_FIRST_WINS_WI_TYPE ) );
	return calc;
}

}// end namespace discount
} // end namespace libcsc
