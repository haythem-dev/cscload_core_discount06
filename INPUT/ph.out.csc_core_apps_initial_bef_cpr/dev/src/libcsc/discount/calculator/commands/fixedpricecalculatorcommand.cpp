#include "discount/calculator/commands/fixedpricecalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

namespace libcsc
{
namespace discount
{
FixedPriceCalculatorCommand::FixedPriceCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType )
{
}

FixedPriceCalculatorCommand::~FixedPriceCalculatorCommand()
{
}

const DiscountCalculatorResult & FixedPriceCalculatorCommand::calculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "FixedPriceCalculatorCommand::calculate()" );

	// only for single article level - fixed price should also not be calculated on group level = not at closure of order !!!
	DiscountCalculatorResult result;
	IOrderBaseValueGetterPtr orderBaseValue = getOrderBaseValueGetter();
	
	/* 	OrderBaseValues zum Abgleich nötig, um herauszufinden, ob DiscountBaseValues auch angewendet werden dürfen:
		- Bestellmenge >= baseqty							(Artikel-  + Auftragsebene)
		- Bestellwert  >= basevalue							(Artikel-  + Auftragsebene)
		- discountspec - muss zum CalculatorCommand passen	(Artikel-  + Auftragsebene)
		- articleno											(nur Auftragsebene)
		- Artikelgruppen eines Artikels						(nur Auftragsebene) --> einmalig für abzuschließenden Auftrag ermitteln und orderBaseValue hinzufügen !?
		- Hersteller eines Artikels							(nur Auftragsebene) --> einmalig für abzuschließenden Auftrag ermitteln und orderBaseValue hinzufügen !?
		- Herstellergruppen zu Herstellern eines Artikels	(nur Auftragsebene) --> einmalig für abzuschließenden Auftrag ermitteln und orderBaseValue hinzufügen !?
			
		--> nicht geprüft werden müssen:
				- articleno (auf Artikelebene)
				- customerno (generell)
				- pharmacygroupid (generell)
				- base_mult_std_qty (wird in HR nicht verwendet) */
	
	const FilteredDiscountBaseValueList & list = getDiscountBaseValueGetter()->getCollectionByArticleNo();
	FilteredDiscountBaseValueList::const_iterator iter = list.begin();
	
	// running over all valid discounts (invalid datefrom / dateto, pharmacygroup, customerno, discountgroup already filtered via SQL), 
	// looking for rows with fixedprice (independent from discountspec)
	for( ; iter != list.end(); ++iter ) 
	{
		DiscountBaseValuePtr discountBaseValue( *iter );

		if (orderBaseValue->getArticleNo()		!= discountBaseValue->getArticleNo()	||	// fixedprice only OK on article level, not on group level !
												!areBaseValuesMatching(discountBaseValue))
		{
			continue;
		}

		const libcsc::Decimal & fixedPrice = discountBaseValue->getFixedPrice(); // Netto- Rabatt
		DiscountResult & discountResult( result.getDiscountResult( orderBaseValue->getPositionNo() ) );

		if(    libcsc::Decimal::zero() != fixedPrice
			&& (    discountResult.discountedArticlePrice.isUnset()
				 || basar::Decimal( fixedPrice ) < discountResult.discountedArticlePrice ) )
		{
			// set any property of result only, if there is a "real" result!? Otherwise, fixed price would always win according to FirstWinsCalculatorCommand::doCalculate(), because a property in state "DIRTY" is contained ...
			setResultBaseValues( result );
			setDiscountSourceValues( discountResult.source, discountBaseValue, ART_CLASS_NONE );
			discountResult.discountedArticlePrice = fixedPrice; // overwrite worse result
			discountResult.discountedArticlePriceOrigin = getType();
		}
	}

	if( result.containsDirty() )
	{
		setResult( result );
	}
	logCalculation( result );
	return getResult();
}

} // end namespace discount
} // end namespace libcsc
