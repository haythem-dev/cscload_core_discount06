#include "hrorderdiscountcalculatorcomponentmanager.h"
#include <discount/calculator/commands/discountcalculatorcompositecommandbase.h>

namespace libcsc
{
namespace discount
{
HROrderDiscountCalculatorComponentManager::HROrderDiscountCalculatorComponentManager()
{
}

HROrderDiscountCalculatorComponentManager::~HROrderDiscountCalculatorComponentManager()
{
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::getDiscountCalculator()
{
	return createSumAll( CT_ROOT );
}

// composite calculators
IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createSumAll( 
	const DiscountCalculatorTypeEnum parentCalcType 
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createSum( parentCalcType, CT_HR_SUM_ALL_TYPE, true ) );
	calc->add( createFixedPrice( CT_HR_SUM_ALL_TYPE ) );
	calc->add( createSumRetailWholesaleWholesaleIndustry( CT_HR_SUM_ALL_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createSumRetailWholesaleWholesaleIndustry(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createSum( parentCalcType, CT_HR_SUM_RE_WH_WI_TYPE, true ) );
	calc->add( createRetail( CT_HR_SUM_RE_WH_WI_TYPE ) );
	calc->add( createFirstWinsWholesale( CT_HR_SUM_RE_WH_WI_TYPE ) );
	calc->add( createFirstWinsWholesaleIndustry( CT_HR_SUM_RE_WH_WI_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createFirstWinsWholesale(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createFirstWins( parentCalcType, CT_HR_FIRST_WINS_WH_TYPE, true ) );
	calc->add( createBestOfWholesaleCustomer( CT_HR_FIRST_WINS_WH_TYPE ) );
	calc->add( createBestOfWholesaleCustomerGroup( CT_HR_FIRST_WINS_WH_TYPE ) );
	calc->add( createBestOfWholesaleAllCustomer( CT_HR_FIRST_WINS_WH_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createFirstWinsWholesaleIndustry(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createFirstWins( parentCalcType, CT_HR_FIRST_WINS_WI_TYPE, true ) );
	calc->add( createBestOfWholesaleIndustryCustomer( CT_HR_FIRST_WINS_WI_TYPE ) );
	calc->add( createBestOfWholesaleIndustryCustomerGroup( CT_HR_FIRST_WINS_WI_TYPE ) );
	calc->add( createBestOfWholesaleIndustryAllCustomer( CT_HR_FIRST_WINS_WI_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleCustomer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_CUSTOMER_TYPE, true ) );
	calc->add( createWholesaleCustomerArticle( CT_HR_BEST_OF_WH_CUSTOMER_TYPE ) );
	calc->add( createWholesaleCustomerArticleGroup( CT_HR_BEST_OF_WH_CUSTOMER_TYPE ) );
	calc->add( createWholesaleCustomerManufacturer( CT_HR_BEST_OF_WH_CUSTOMER_TYPE ) );
	calc->add( createWholesaleCustomerManufacturerGroup( CT_HR_BEST_OF_WH_CUSTOMER_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleCustomerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_CUSTOMER_GROUP_TYPE, true ) );
	calc->add( createWholesaleCustomerGroupArticle( CT_HR_BEST_OF_WH_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleCustomerGroupArticleGroup( CT_HR_BEST_OF_WH_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleCustomerGroupManufacturer( CT_HR_BEST_OF_WH_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleCustomerGroupManufacturerGroup( CT_HR_BEST_OF_WH_CUSTOMER_GROUP_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleAllCustomer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_ALL_CUSTOMER_TYPE, true ) );
	calc->add( createWholesaleAllCustomerArticle( CT_HR_BEST_OF_WH_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleAllCustomerArticleGroup( CT_HR_BEST_OF_WH_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleAllCustomerManufacturer( CT_HR_BEST_OF_WH_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleAllCustomerManufacturerGroup( CT_HR_BEST_OF_WH_ALL_CUSTOMER_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleIndustryCustomer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_TYPE, true ) );
	calc->add( createWholesaleIndustryCustomerArticle( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryCustomerArticleGroup( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryCustomerManufacturer( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryCustomerManufacturerGroup( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleIndustryCustomerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_GROUP_TYPE, true ) );
	calc->add( createWholesaleIndustryCustomerGroupArticle( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleIndustryCustomerGroupArticleGroup( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleIndustryCustomerGroupManufacturer( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_GROUP_TYPE ) );
	calc->add( createWholesaleIndustryCustomerGroupManufacturerGroup( CT_HR_BEST_OF_WH_INDUSTRY_CUSTOMER_GROUP_TYPE ) );
	return calc;
}

IDiscountCalculatorCommandPtr HROrderDiscountCalculatorComponentManager::createBestOfWholesaleIndustryAllCustomer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( createBestOf4CustomerCombined( parentCalcType, CT_HR_BEST_OF_WH_INDUSTRY_ALL_CUSTOMER_TYPE, true ) );
	calc->add( createWholesaleIndustryAllCustomerArticle( CT_HR_BEST_OF_WH_INDUSTRY_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryAllCustomerArticleGroup( CT_HR_BEST_OF_WH_INDUSTRY_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryAllCustomerManufacturer( CT_HR_BEST_OF_WH_INDUSTRY_ALL_CUSTOMER_TYPE ) );
	calc->add( createWholesaleIndustryAllCustomerManufacturerGroup( CT_HR_BEST_OF_WH_INDUSTRY_ALL_CUSTOMER_TYPE ) );
	return calc;
}

}// end namespace discount
} // end namespace libcsc
