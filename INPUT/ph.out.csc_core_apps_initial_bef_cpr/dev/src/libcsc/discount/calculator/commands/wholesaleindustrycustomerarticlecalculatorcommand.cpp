#include "discount/calculator/commands/wholesaleindustrycustomerarticlecalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

namespace libcsc
{
namespace discount
{
WholesaleIndustryCustomerArticleCalculatorCommand::WholesaleIndustryCustomerArticleCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleIndustryCustomerArticleCalculatorCommand::~WholesaleIndustryCustomerArticleCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleIndustryCustomerArticleCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleIndustryCustomerArticleCalculatorCommand::calculate()" );

	// this command is only for single article level (not closure of order!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollectionByArticleNo();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale industry discounts (discountspec = 7)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		// this calculator command only takes discountspec = wholesale, special customer, special article
		if (orderBaseValue->getArticleNo()			!= discountBaseValue->getArticleNo()	||
			orderBaseValue->getCustomerNo()			!= discountBaseValue->getCustomerNo()	||
													!areBaseValuesMatching(discountBaseValue)	||
			discountBaseValue->getDiscountSpec()	!= DISC_SPEC_WHOLESALE_INDUSTRY				)
		{
			continue;
		}

		calculateDiscount( result, discountBaseValue, orderBaseValue->getPositionNo() );
		calculateRebateInKind( result, discountBaseValue );
	}
	setResult( result );
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
