#include "discount/calculator/commands/wholesaleindustrycustomergroupmanufacturercalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/iarticleclassificationgetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
WholesaleIndustryCustomerGroupManufacturerCalculatorCommand::WholesaleIndustryCustomerGroupManufacturerCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleIndustryCustomerGroupManufacturerCalculatorCommand::~WholesaleIndustryCustomerGroupManufacturerCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleIndustryCustomerGroupManufacturerCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleIndustryCustomerGroupManufacturerCalculatorCommand::calculate()" );

	// this command is only for closure of order (not single article level!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollection();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();

	ArticleClassificationCollectionPtr				classificationPtr = orderBaseValue->getArticleClassification()->getClassificationByManufacturer(orderBaseValue);
	ArticleClassificationCollection::const_iterator iterClassification;
	basar::Int32									manufacturerNo;			// key of classification
	OrderItemBaseValueCollectionPtr					itemsOfClassification;	// collection of all items belonging to key
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale industry discounts (discountspec = 7)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		for( iterClassification = classificationPtr->begin(); iterClassification != classificationPtr->end(); ++iterClassification ) 
		{
			manufacturerNo = iterClassification->first; // key
			itemsOfClassification = iterClassification->second;
			
			// this calculator command only takes discountspec = wholesale industry, special customer group, special manufacturer
			if (0												!= discountBaseValue->getArticleNo()	||
				manufacturerNo									!= discountBaseValue->getManufacturerNo() ||
				0												!= discountBaseValue->getCustomerNo()	||
				0												!= discountBaseValue->getDiscountGrpNo() ||
				PHARMACY_GROUP_UNIVERSAL						== discountBaseValue->getPharmacyGrpId()||
																!itemsOfClassification->isArticleContained(orderBaseValue->getArticleNo()) ||
																!areBaseValuesMatching(discountBaseValue, itemsOfClassification) ||
				discountBaseValue->getDiscountSpec()			!= DISC_SPEC_WHOLESALE_INDUSTRY				)
			{
				continue;
			}

			calculateDiscounts( result, discountBaseValue, itemsOfClassification, ART_CLASS_MANUFACTURER );
			calculateRebateInKind( result, discountBaseValue, itemsOfClassification, true, ART_CLASS_MANUFACTURER );
		}
	}

	setResult( result );
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
