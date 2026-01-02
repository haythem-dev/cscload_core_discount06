#include "discount/calculator/commands/retailcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

namespace libcsc
{
namespace discount
{
RetailCalculatorCommand::RetailCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

RetailCalculatorCommand::~RetailCalculatorCommand()
{
}

const DiscountCalculatorResult & RetailCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RetailCalculatorCommand::calculate()" );

	// only for single article level 
	// in Croatia, it is defined that Retail (discountspec = 3) is only on article level (no discount group level / no pharmacy group level / no customerno level) = not at closure of order !!!
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "OrderBaseValue: " << ( *orderBaseValue );
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollectionByArticleNo();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with retail discounts (discountspec = 3)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
		{
			std::stringstream ss;
			ss << "DiscountBaseValue: " << ( *discountBaseValue );
			LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
		}

		// in Croatia, it is defined that Retail (discountspec = 3) is only on article level (no discount group level / no pharmacy group level / no customerno level) 
		if (orderBaseValue->getArticleNo()			!= discountBaseValue->getArticleNo()	||	// retail only OK on article level, not on group level !
			PHARMACY_GROUP_UNIVERSAL				!= discountBaseValue->getPharmacyGrpId()||
			libcsc::Int32(0)						!= discountBaseValue->getCustomerNo()	||
			libcsc::Int32(0)						!= discountBaseValue->getDiscountGrpNo()||
													!areBaseValuesMatching(discountBaseValue) ||
			discountBaseValue->getDiscountSpec()	!= DISC_SPEC_RETAIL						)
		{
			continue;
		}

		// nur Bar- Rabatt / Cash, kein Natra auf Retail-Ebene !
		calculateDiscount( result, discountBaseValue, orderBaseValue->getPositionNo() );
	}

	setResult( result );
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
