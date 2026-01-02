#include "discount/calculator/commands/wholesalecustomerarticlecalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

namespace libcsc
{
namespace discount
{
WholesaleCustomerArticleCalculatorCommand::WholesaleCustomerArticleCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleCustomerArticleCalculatorCommand::~WholesaleCustomerArticleCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleCustomerArticleCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleCustomerArticleCalculatorCommand::calculate()" );

	// this command is only for single article level (not closure of order!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollectionByArticleNo();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale discounts (discountspec = 2)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		// this calculator command only takes discountspec = wholesale, special customer, special article
		if (orderBaseValue->getArticleNo()			!= discountBaseValue->getArticleNo()	||
			orderBaseValue->getCustomerNo()			!= discountBaseValue->getCustomerNo()	||
													!areBaseValuesMatching(discountBaseValue)	||
			discountBaseValue->getDiscountSpec()	!= DISC_SPEC_WHOLESALE						)
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
