#include "discount/calculator/commands/wholesalecustomermanufacturergroupcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/iarticleclassificationgetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
WholesaleCustomerManufacturerGroupCalculatorCommand::WholesaleCustomerManufacturerGroupCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

WholesaleCustomerManufacturerGroupCalculatorCommand::~WholesaleCustomerManufacturerGroupCalculatorCommand()
{
}

const DiscountCalculatorResult & WholesaleCustomerManufacturerGroupCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "WholesaleCustomerManufacturerGroupCalculatorCommand::calculate()" );

	// this command is only for closure of order (not single article level!)
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollection();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();

	ArticleClassificationCollectionPtr				classificationPtr = orderBaseValue->getArticleClassification()->getClassificationByManufacturerGroup(orderBaseValue);
	ArticleClassificationCollection::const_iterator iterClassification;
	basar::Int32									manufacturerGroup;		// key of classification
	OrderItemBaseValueCollectionPtr					itemsOfClassification;	// collection of all items belonging to key
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with wholesale discounts (discountspec = 2)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue = ( *iter );

		for( iterClassification = classificationPtr->begin(); iterClassification != classificationPtr->end(); ++iterClassification ) 
		{
			manufacturerGroup = iterClassification->first; // key
			itemsOfClassification = iterClassification->second;
			
			// this calculator command only takes discountspec = wholesale, special customer, special manufacturer group
			if (0												!= discountBaseValue->getArticleNo()	||
				0												!= discountBaseValue->getManufacturerNo() ||
				manufacturerGroup								!= discountBaseValue->getDiscountGrpNo() ||
				orderBaseValue->getCustomerNo()					!= discountBaseValue->getCustomerNo()	||
																!itemsOfClassification->isArticleContained(orderBaseValue->getArticleNo()) ||
																!areBaseValuesMatching(discountBaseValue, itemsOfClassification) ||
				discountBaseValue->getDiscountSpec()			!= DISC_SPEC_WHOLESALE						)
			{
				continue;
			}

			calculateDiscounts( result, discountBaseValue, itemsOfClassification, ART_CLASS_MANUFACTURER_GROUP );
			calculateRebateInKind( result, discountBaseValue, itemsOfClassification, true, ART_CLASS_MANUFACTURER_GROUP );
		}
	}

	setResult( result );
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
