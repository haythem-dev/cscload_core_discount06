#include "discount/calculator/commands/wholesaleallcustomerarticlecalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

namespace libcsc
{
namespace discount
{
WholesaleAllCustomerArticleCalculatorCommand::WholesaleAllCustomerArticleCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleAllCustomerArticleCalculatorCommand::~WholesaleAllCustomerArticleCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleAllCustomerArticleCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleAllCustomerArticleCalculatorCommand::calculate()" );

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

		// this calculator command only takes discountspec = wholesale, customer group, special article
		if (orderBaseValue->getArticleNo()			!= discountBaseValue->getArticleNo()	||
			0										!= discountBaseValue->getCustomerNo()	||
			PHARMACY_GROUP_UNIVERSAL				!= discountBaseValue->getPharmacyGrpId()||
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
