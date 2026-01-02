#include "discount/calculator/commands/wholesaleindustrycustomerarticlegroupcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/iarticleclassificationgetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
WholesaleIndustryCustomerArticleGroupCalculatorCommand::WholesaleIndustryCustomerArticleGroupCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleIndustryCustomerArticleGroupCalculatorCommand::~WholesaleIndustryCustomerArticleGroupCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleIndustryCustomerArticleGroupCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleIndustryCustomerArticleGroupCalculatorCommand::calculate()" );

	// this command is only for closure of order (not single article level!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollection();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();

	ArticleClassificationCollectionPtr				classificationPtr = orderBaseValue->getArticleClassification()->getClassificationByArticleGroup(orderBaseValue);
	ArticleClassificationCollection::const_iterator iterClassification;
	basar::Int32									articleGroup;			// key of classification
	OrderItemBaseValueCollectionPtr					itemsOfClassification;	// collection of all items belonging to key
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale industry discounts (discountspec = 7)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		for( iterClassification = classificationPtr->begin(); iterClassification != classificationPtr->end(); ++iterClassification ) 
		{
			articleGroup = iterClassification->first; // key
			itemsOfClassification = iterClassification->second;
			
			// this calculator command only takes discountspec = wholesale industry, special customer, special article group
			if (0												!= discountBaseValue->getArticleNo()	||
				0												!= discountBaseValue->getManufacturerNo() ||
				articleGroup									!= discountBaseValue->getDiscountGrpNo() ||
				orderBaseValue->getCustomerNo()					!= discountBaseValue->getCustomerNo()	||
																!itemsOfClassification->isArticleContained(orderBaseValue->getArticleNo()) ||
																!areBaseValuesMatching(discountBaseValue, itemsOfClassification) ||
				discountBaseValue->getDiscountSpec()			!= DISC_SPEC_WHOLESALE_INDUSTRY				)
			{
				continue;
			}

			calculateDiscounts( result, discountBaseValue, itemsOfClassification, ART_CLASS_ARTICLE_GROUP );
			calculateRebateInKind( result, discountBaseValue, itemsOfClassification, true, ART_CLASS_ARTICLE_GROUP );
		}
	}

	setResult( result );
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
