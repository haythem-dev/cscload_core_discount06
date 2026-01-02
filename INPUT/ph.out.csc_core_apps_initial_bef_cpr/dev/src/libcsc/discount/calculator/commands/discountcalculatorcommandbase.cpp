#include "discount/calculator/commands/discountcalculatorcommandbase.h"	
#include "discount/logger/discountlogger/idiscountlogger.h"
#include <discount/resultprocessor/iresultprocessor.h>
#include "discount/logger/hierarchylogger/ihierarchylogger.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"
#include "discount/basevalues/orderbasevalue/orderitembasevalue.h"

namespace libcsc
{
namespace discount
{
DiscountCalculatorCommandBase::DiscountCalculatorCommandBase( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType
		)
: m_ParentType( parentCalcType ),
  m_Type( calcType )
{
}

DiscountCalculatorCommandBase::~DiscountCalculatorCommandBase()
{
}

void DiscountCalculatorCommandBase::inject( IDiscountBaseValueGetterPtr baseValueGetter )
{
	m_DiscountBaseValueGetter = baseValueGetter;
}

void DiscountCalculatorCommandBase::inject( IOrderBaseValueGetterPtr baseValueGetter )
{
	m_OrderBaseValueGetter = baseValueGetter;
}

void DiscountCalculatorCommandBase::inject( IDiscountLoggerPtr logger )
{
	m_DiscountLogger = logger;
}

void DiscountCalculatorCommandBase::inject( IResultProcessorPtr logger )
{
	m_ResultLogger = logger;
}

void DiscountCalculatorCommandBase::inject( IHierarchyLoggerPtr logger )
{
	m_HierarchyLogger = logger;
}

void DiscountCalculatorCommandBase::logCalculation( const DiscountCalculatorResult & calcResult ) const
{
	m_DiscountLogger->log( m_Type, calcResult );
}

void DiscountCalculatorCommandBase::processResult() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::processResult()" );

	m_ResultLogger->process( m_Type, m_OrderBaseValueGetter, m_Result );
}

void DiscountCalculatorCommandBase::processResult( const DiscountCalculatorResult & result ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::processResult(const DiscountCalculatorResult &)" );

	DiscountCalculatorResult tempResult;
	copyOriginValues( tempResult, result );
	if( tempResult.isUnset() )
	{
		return;
	}
	m_ResultLogger->process( m_Type, m_OrderBaseValueGetter, tempResult );
}

void DiscountCalculatorCommandBase::logHierarchy() const
{
	m_HierarchyLogger->log( m_ParentType, m_Type, m_Result );
}

const DiscountCalculatorResult & DiscountCalculatorCommandBase::getResult() const
{
	return m_Result;
}

IDiscountBaseValueGetterPtr DiscountCalculatorCommandBase::getDiscountBaseValueGetter() const
{
	return m_DiscountBaseValueGetter;
}

IOrderBaseValueGetterPtr DiscountCalculatorCommandBase::getOrderBaseValueGetter() const
{
	return m_OrderBaseValueGetter;
}

void DiscountCalculatorCommandBase::setResult( const DiscountCalculatorResult & calcResult ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::setResult()" );

	m_Result = calcResult;
}

DiscountCalculatorTypeEnum DiscountCalculatorCommandBase::getType() const
{
	return m_Type;
}

void DiscountCalculatorCommandBase::setDiscountCalculatorType(const DiscountCalculatorTypeEnum type) const
{
	m_Type = type;
}


void DiscountCalculatorCommandBase::setResultBaseValues(
	DiscountCalculatorResult & calcResult
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::setResultBaseValues()" );

	if( calcResult.baseValue.isUnset() ) // only once, if no result yet
	{
		calcResult.baseValue.articleNo = m_OrderBaseValueGetter->getArticleNo();
		calcResult.baseValue.quantity = m_OrderBaseValueGetter->getItemQty();
		calcResult.baseValue.baseArticlePrice = m_OrderBaseValueGetter->getItemPrice();
	}
}

void DiscountCalculatorCommandBase::setDiscountSourceValues( 
	DiscountSource & discountSource, 
	DiscountBaseValuePtr discountBaseValue, 
	const ArticleClassificationEnum artClass
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::setDiscountSourceValues()" );

	discountSource.pharmacyGroup = discountBaseValue->getPharmacyGrpId();
	discountSource.promotionNo = discountBaseValue->getPromotionNo();
	discountSource.promotionName = discountBaseValue->getPromotionName();

	switch( artClass )
	{
		case ART_CLASS_MANUFACTURER:
			discountSource.number = discountBaseValue->getManufacturerNo();
			discountSource.type = DiscountSource::DST_MANUFACTURER;
			break;
		case ART_CLASS_MANUFACTURER_GROUP:
			discountSource.number = discountBaseValue->getDiscountGrpNo();
			discountSource.type = DiscountSource::DST_MANUFACTURER_GROUP;
			break;
		case ART_CLASS_ARTICLE_GROUP:
			discountSource.number = discountBaseValue->getDiscountGrpNo();
			discountSource.type = DiscountSource::DST_ARTICLE_GROUP;
			break;
		case ART_CLASS_NONE:
			discountSource.number = m_OrderBaseValueGetter->getPositionNo();
			discountSource.type = DiscountSource::DST_POSITION;
		default: 
			break;
	}
}	

void DiscountCalculatorCommandBase::calculateDiscounts( 
	DiscountCalculatorResult & calcResult, 
	DiscountBaseValuePtr discountBaseValue, 
	OrderItemBaseValueCollectionPtr articleClassificationList,
	const ArticleClassificationEnum artClass
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateDiscounts()" );

	OrderItemBaseValueCollection::const_iterator iter = articleClassificationList->begin();
	for( ; iter != articleClassificationList->end(); ++iter )
	{
		if (0 >= iter->second->getItemQty())
			continue; // do not grant discount % for natra positions granted before on position level !!!
		
		DiscountResult & discountResult( calcResult.getDiscountResult( iter->second->getPositionNo() ) );
		setDiscountSourceValues( discountResult.source, discountBaseValue, artClass );
		calculateDiscountPct( discountResult, discountBaseValue );
	}
}

void DiscountCalculatorCommandBase::calculateDiscount( 
	DiscountCalculatorResult & calcResult, 
	DiscountBaseValuePtr discountBaseValue,
	const basar::Int32 positionNo
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateDiscount()" );

	DiscountResult & discountResult( calcResult.getDiscountResult( positionNo ) );
	setResultBaseValues( calcResult );
	setDiscountSourceValues( discountResult.source, discountBaseValue, ART_CLASS_NONE );
	calculateDiscountPct( discountResult, discountBaseValue );
}

void DiscountCalculatorCommandBase::calculateDiscountPct(
	DiscountResult & discountResult, 
	DiscountBaseValuePtr discountBaseValue 
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateDiscountPct()" );

	const libcsc::Decimal & discountPct = discountBaseValue->getDiscountValuePct(); // Bar- Rabatt / Cash

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "DiscountResult: " << discountResult;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	// search for a better pct:
	if(    libcsc::Decimal::zero() != discountPct
		&& (    discountResult.discountPercent.isUnset()
		     || basar::Decimal( discountPct ) > discountResult.discountPercent ) )
	{
		discountResult.discountPercent = discountPct; // overwrite worse result (could happen even on article level, if there is more than 1 matching base value!) - no combination!
		discountResult.discountPercentOrigin = getType();
		discountResult.source.pharmacyGroup = discountBaseValue->getPharmacyGrpId();
		discountResult.source.promotionNo = discountBaseValue->getPromotionNo();
		discountResult.source.promotionName = discountBaseValue->getPromotionName();

	}
}

void DiscountCalculatorCommandBase::calculateRebateInKind(
	DiscountCalculatorResult & calcResult, 
	DiscountBaseValuePtr discountBaseValue,
	OrderItemBaseValueCollectionPtr orderRangeValue,
	const bool isRangeCalc, 
	const ArticleClassificationEnum artClass
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateRebateInKind() - Range" );

	libcsc::Int32 discountQty = discountBaseValue->getDiscountQty(); // Natra- Menge
	if(	(0 < discountBaseValue->getBaseQty() || discountBaseValue->getBaseValue() != libcsc::Decimal::zero())
		&& discountBaseValue->getNoMultipleQty() != "1" )
	{
		basar::Int32 multiple = 1;
		if( 0 < discountBaseValue->getBaseQty() )
		{
			multiple = orderRangeValue->getArticleQuantity() / discountBaseValue->getBaseQty();
		}
		else if( discountBaseValue->getBaseValue() != libcsc::Decimal::zero() )
		{
			multiple = basar::Decimal( orderRangeValue->getArticleValue() / discountBaseValue->getBaseValue() ).toInt32();
		}

		discountQty = discountQty * multiple;
	}

	calculateRebateInKind( calcResult, discountBaseValue, discountQty, isRangeCalc, artClass );
}

void DiscountCalculatorCommandBase::calculateRebateInKind(
	DiscountCalculatorResult & calcResult, 
	DiscountBaseValuePtr discountBaseValue, 
	const bool isRangeCalc, 
	const ArticleClassificationEnum artClass
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateRebateInKind() - Article" );

	libcsc::Int32 discountQty = discountBaseValue->getDiscountQty(); // Natra- Menge
	if(	   0 < discountBaseValue->getBaseQty() 
		&& discountBaseValue->getNoMultipleQty() != "1" )
	{
		basar::Int32 multiple = 1;
		if( 0 < discountBaseValue->getBaseQty() )
		{
			multiple = getOrderBaseValueGetter()->getItemQty() / discountBaseValue->getBaseQty();
		}
		else if( discountBaseValue->getBaseValue() != libcsc::Decimal::zero() )
		{
			multiple = basar::Decimal( getOrderBaseValueGetter()->getItemValue() / discountBaseValue->getBaseValue() ).toInt32();
		}

		discountQty = discountQty * multiple;
	}

	calculateRebateInKind( calcResult, discountBaseValue, discountQty, isRangeCalc, artClass );
}

void DiscountCalculatorCommandBase::calculateRebateInKind(
	DiscountCalculatorResult & calcResult, 
	DiscountBaseValuePtr discountBaseValue, 
	const libcsc::Int32 & discountQty,
	const bool isRangeCalc, 
	const ArticleClassificationEnum artClass
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCommandBase::calculateRebateInKind()" );

	libcsc::Int32 discountArticle			= discountBaseValue->getDiscountArticle(); // Natra- PZN
	libcsc::Decimal discountArticlePrice	= discountBaseValue->getDiscountArticlePrice();// AEP der Natra- PZN

	if ( 0 < discountQty && 0 == discountArticle && !isRangeCalc) // Natra- Menge gesetzt, aber keine Natra- PZN ==> Zusatzmenge derselben PZN. (only on article level)
	{
		discountArticle		 = getOrderBaseValueGetter()->getArticleNo(); 
		discountArticlePrice = getOrderBaseValueGetter()->getItemPrice();
	}

	// search for a better rebate in kind:
	if( 0 < discountQty )
	{	
		RebateInKindValue rikv( getType(), discountArticle, discountQty, discountArticlePrice, libcsc::Decimal::zero() != discountBaseValue->getRefundPct() );
		RebateInKindValueCollection::iterator iterRikv = calcResult.rebateInKindArticles.begin();

		setDiscountSourceValues( rikv.source, discountBaseValue, artClass );
		if( false == isRangeCalc )
		{
			setResultBaseValues( calcResult ); // only on article level
		}

		if( iterRikv == calcResult.rebateInKindArticles.end() ) 
		{
			calcResult.addRebateInKind ( rikv ); // no rebate in kind set before = add 
		}
		else if ((((*iterRikv).articleNo == rikv.articleNo 
			       || (((*iterRikv).articlePrice == libcsc::Decimal::zero() && rikv.articlePrice == libcsc::Decimal::zero())))
				 && ((*iterRikv).quantity) < (rikv.quantity))
			    ||  *iterRikv	< rikv )
		{
			// there must have been a worse result before, so replace this:
			*iterRikv = rikv; // don´t add, because no combination = there can only be one RebateInKindValue within one calculator!
		}
		// else: already set result is better --> nothing to do (no overwritting, no combining!)
	}
}

bool DiscountCalculatorCommandBase::areBaseValuesMatching(DiscountBaseValuePtr discountBaseValue) const
{
	return	( getOrderBaseValueGetter()->getItemQty()	>= discountBaseValue->getBaseQty()		&& discountBaseValue->getBaseQty()	 > 0 )	||
			( getOrderBaseValueGetter()->getItemValue() >= discountBaseValue->getBaseValue()	&& discountBaseValue->getBaseValue() != libcsc::Decimal::zero());
}

bool DiscountCalculatorCommandBase::areBaseValuesMatching(DiscountBaseValuePtr discountBaseValue, OrderItemBaseValueCollectionPtr orderRangeValue) const
{
	return	( orderRangeValue->getArticleQuantity()	>= discountBaseValue->getBaseQty()		&& discountBaseValue->getBaseQty()	 > 0 )	||
			( orderRangeValue->getArticleValue()	>= discountBaseValue->getBaseValue()	&& discountBaseValue->getBaseValue() != libcsc::Decimal::zero());
}

void DiscountCalculatorCommandBase::copyBaseValues( 
	DiscountResultBaseValue & destination, 
	const DiscountResultBaseValue & source 
		) const
{
	// TODO: for debugging only - remove
	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "BaseValue before: " << destination;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	if (source.isUnset())
	{
		destination.baseArticlePrice.setUnset();
		destination.quantity.setUnset();
		destination.articleNo.setUnset();
	}
	else
	{
		if( source.baseArticlePrice.isDirty() )
		{
			destination.baseArticlePrice = source.baseArticlePrice;
		}
		if( source.quantity.isDirty() )
		{
			destination.quantity = source.quantity;
		}
		if( source.articleNo.isDirty() )
		{
			destination.articleNo = source.articleNo;
		}
	}

	// TODO: for debugging only - remove
	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "BaseValue after: " << destination;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}
}

void DiscountCalculatorCommandBase::copyOriginValues( 
	DiscountCalculatorResult & destination, 
	const DiscountCalculatorResult & source
		) const
{
	DiscountCalculatorTypeEnum myType = getType();
	DiscountResultCollection::const_iterator iter = source.results.begin();
	for( ; iter != source.results.end(); ++iter )
	{
		const basar::Int32 positionNo( iter->first );
		const DiscountResult & sourceDiscountResult( iter->second );

		if(    sourceDiscountResult.discountPercent.isDirty()
			&& myType == sourceDiscountResult.discountPercentOrigin )
		{
			DiscountResult & destinationResult = destination.getDiscountResult( positionNo );
			destinationResult.source = sourceDiscountResult.source;
			destinationResult.discountPercent = sourceDiscountResult.discountPercent;
			destinationResult.discountPercentOrigin = sourceDiscountResult.discountPercentOrigin;
		}
		if(    sourceDiscountResult.discountValue.isDirty()
			&& myType == sourceDiscountResult.discountValueOrigin )
		{
			DiscountResult & destinationResult = destination.getDiscountResult( positionNo );
			destinationResult.source = sourceDiscountResult.source;
			destinationResult.discountValue = sourceDiscountResult.discountValue;
			destinationResult.discountValueOrigin = sourceDiscountResult.discountValueOrigin;
		}
		if(    sourceDiscountResult.discountedArticlePrice.isDirty()
			&& myType == sourceDiscountResult.discountedArticlePriceOrigin )
		{
			DiscountResult & destinationResult = destination.getDiscountResult( positionNo );
			destinationResult.source = sourceDiscountResult.source;
			destinationResult.discountedArticlePrice = sourceDiscountResult.discountedArticlePrice;
			destinationResult.discountedArticlePriceOrigin = sourceDiscountResult.discountedArticlePriceOrigin;
		}
	}

	RebateInKindValueCollection::const_iterator iterRiK = source.rebateInKindArticles.begin();
	for( ; iterRiK != source.rebateInKindArticles.end(); ++iterRiK )
	{
		const RebateInKindValue & rebate( *iterRiK );
		if( myType == rebate.origin )
		{
			destination.addRebateInKind( rebate );
		}
	}

	if( destination.containsDirty() )
	{
		copyBaseValues( destination.baseValue, source.baseValue );
	}
}

} // end namespace discount
} // end namespace libcsc
