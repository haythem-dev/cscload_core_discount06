#include "discount/calculator/commands/wholesaleindustrycustomergrouparticlegroupcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/iarticleclassificationgetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand::WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand::~WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand::calculate()" );

	// this command is only for closure of order (not single article level!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollection();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();

	ArticleClassificationCollectionPtr				classificationPtr = orderBaseValue->getArticleClassification()->getClassificationByArticleGroup(orderBaseValue); // collection of all relevant groups for current order
	ArticleClassificationCollection::const_iterator iterClassification;		// iterator for all relevant groups
	basar::Int32									articleGroup;			// key (group no) of current classification / group
	OrderItemBaseValueCollectionPtr					itemsOfClassification;	// collection of all articles belonging to one group
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale industry discounts (discountspec = 7)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		for( iterClassification = classificationPtr->begin(); iterClassification != classificationPtr->end(); ++iterClassification ) 
		{
			articleGroup = iterClassification->first; // key
			itemsOfClassification = iterClassification->second;
			
			// this calculator command only takes discountspec = wholesale industry, special customer group, special article group
			if (0												!= discountBaseValue->getArticleNo()	||
				0												!= discountBaseValue->getManufacturerNo() ||
				articleGroup									!= discountBaseValue->getDiscountGrpNo() ||
				0												!= discountBaseValue->getCustomerNo()	||
				PHARMACY_GROUP_UNIVERSAL						== discountBaseValue->getPharmacyGrpId()||
																!itemsOfClassification->isArticleContained(orderBaseValue->getArticleNo()) ||
																!areBaseValuesMatching(discountBaseValue, itemsOfClassification) ||
				discountBaseValue->getDiscountSpec()			!= DISC_SPEC_WHOLESALE_INDUSTRY	)
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
