#include "discountcalculatorresult.h"
#include "discountcalculatortypemapper.h"
#include <algorithm>

namespace libcsc
{
namespace discount
{
DiscountSource::DiscountSource()
:	number( 0 ),
	type( DST_POSITION ),
	pharmacyGroup( "" ),
	promotionNo( 0 ),
	promotionName( "" )
{
	m_PropertyCollection.add( number );
	m_PropertyCollection.add( type );
	m_PropertyCollection.add( pharmacyGroup );
	m_PropertyCollection.add( promotionNo );
	m_PropertyCollection.add( promotionName );
}

DiscountSource::DiscountSource( const DiscountSource & rhs )
{
	this->operator=( rhs );
	m_PropertyCollection.add( number );
	m_PropertyCollection.add( type );
	m_PropertyCollection.add( pharmacyGroup );
	m_PropertyCollection.add( promotionNo );
	m_PropertyCollection.add( promotionName );
}

DiscountSource & DiscountSource::operator=( const DiscountSource & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	// Important: NO assignment of m_PropertyCollection,
	// because it contains pointers to member variables!

	number = rhs.number;
	number.setState( rhs.number.getState() );

	type = rhs.type;
	type.setState( rhs.type.getState() );

	pharmacyGroup = rhs.pharmacyGroup;
	pharmacyGroup.setState( rhs.pharmacyGroup.getState() );

	promotionNo = rhs.promotionNo;
	promotionNo.setState( rhs.promotionNo.getState() );

	promotionName = rhs.promotionName;
	promotionName.setState( rhs.promotionName.getState() );

	return *this;
}

bool DiscountSource::operator==( const DiscountSource & rhs ) const
{
	return (	number == rhs.number
			 && type == rhs.type
			 && pharmacyGroup == rhs.pharmacyGroup
			 && promotionNo == rhs.promotionNo
			 && promotionName == rhs.promotionName
			 && m_PropertyCollection == rhs.m_PropertyCollection );
}

std::ostream & DiscountSource::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "DiscountSource: number=<" << number << ">";
	strm << ", type=<";
	if( type.isUnset() )
	{
		strm << "UNSET";
	}
	else
	{
		switch( type )
		{
			case DST_POSITION: strm << "DST_POSITION"; break;
			case DST_MANUFACTURER: strm << "DST_MANUFACTURER"; break;
			case DST_ARTICLE_GROUP: strm << "DST_ARTICLE_GROUP"; break;
			case DST_MANUFACTURER_GROUP: strm << "DST_MANUFACTURER_GROUP"; break;
			default: strm << "UNKNOWN -" << static_cast<basar::Int32>( type ) << "-"; break;
		}
	}
	strm << ">";
	strm << ", pharmacyGroup=<" << pharmacyGroup << ">";
	return strm;
}

bool DiscountSource::containsUnset() const
{
	return m_PropertyCollection.containsUnset();
}

bool DiscountSource::containsClean() const
{
	return m_PropertyCollection.containsClean();
}

bool DiscountSource::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

bool DiscountSource::isUnset() const
{
	return m_PropertyCollection.isUnset();
}

bool DiscountSource::isClean() const
{
	return m_PropertyCollection.isClean();
}

bool DiscountSource::isDirty() const
{
	return m_PropertyCollection.isDirty();
}


RebateInKindValue::RebateInKindValue(
	const DiscountCalculatorTypeEnum _origin,
	const basar::Int32 _articleNo,
	const basar::Int32 _quantity,
	const basar::Decimal & _articlePrice,
	const bool _isManufacturerRebate
		)
: origin( _origin ),
  articleNo( _articleNo ),
  quantity( _quantity ),
  articlePrice( _articlePrice ),
  isManufacturerRebate( _isManufacturerRebate )
{
	m_PropertyCollection.add( articleNo );
	m_PropertyCollection.add( quantity );
	m_PropertyCollection.add( articlePrice );
}

RebateInKindValue::RebateInKindValue()
: origin( CT_UNSET ),
  articleNo( 0 ),
  quantity( 0 ),
  articlePrice( basar::Decimal( 0 ) ),
  isManufacturerRebate( false )
{
	m_PropertyCollection.add( articleNo );
	m_PropertyCollection.add( quantity );
	m_PropertyCollection.add( articlePrice );
}

RebateInKindValue::RebateInKindValue( const RebateInKindValue & rhs )
{
	this->operator=( rhs );
	m_PropertyCollection.add( articleNo );
	m_PropertyCollection.add( quantity );
	m_PropertyCollection.add( articlePrice );
}

RebateInKindValue & RebateInKindValue::operator=( const RebateInKindValue & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	// Important: NO assignment of m_PropertyCollection,
	// because it contains pointers to member variables!

	origin = rhs.origin;
	source = rhs.source;

	articleNo = rhs.articleNo;
	articleNo.setState( rhs.articleNo.getState() );

	quantity = rhs.quantity;
	quantity.setState( rhs.quantity.getState() );

	articlePrice = rhs.articlePrice;
	articlePrice.setState( rhs.articlePrice.getState() );

	isManufacturerRebate = rhs.isManufacturerRebate;

	return *this;
}

bool RebateInKindValue::operator==( const RebateInKindValue & rhs ) const
{
	return ( 
		   articleNo == rhs.articleNo		// for find in DiscountCalculatorResult::addRebateInKind, comparison of articleno only makes sense !?
		/*	&& quantity == rhs.quantity				
			&& articlePrice == rhs.articlePrice	*/
			);
}

bool RebateInKindValue::operator<( const RebateInKindValue & rhs ) const
{
	//return ( articleNo < rhs.articleNo ); // this doesn´t make sense!
	return ( (basar::Decimal(articlePrice)		* quantity)		< 
			 (basar::Decimal(rhs.articlePrice)	* rhs.quantity )	);
}

std::ostream & RebateInKindValue::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "RebateInKindValue: source=<";
	if( source.isUnset() )
	{
		strm << "UNSET";
	}
	else
	{
		strm << source;
	}

	strm << ">, origin=<";
	DiscountCalculatorTypeMapper::toStream( strm, origin );
	strm << ">";
	strm << ", quantity=<" << quantity << ">";
	strm << ", articleNo=<" << articleNo << ">";
	strm << ", articlePrice=<" << articlePrice << ">";
	return strm;
}

bool RebateInKindValue::containsUnset() const
{
	return ( m_PropertyCollection.containsUnset() || source.containsUnset() );
}

bool RebateInKindValue::containsClean() const
{
	return ( m_PropertyCollection.containsClean() || source.containsClean() );
}

bool RebateInKindValue::containsDirty() const
{
	return ( m_PropertyCollection.containsDirty() || source.containsDirty() );
}

bool RebateInKindValue::isUnset() const
{
	return ( m_PropertyCollection.isUnset() && source.isUnset() );
}

bool RebateInKindValue::isClean() const
{
	return ( m_PropertyCollection.isClean() && source.isClean() );
}

bool RebateInKindValue::isDirty() const
{
	return ( m_PropertyCollection.isDirty() && source.isDirty() );
}



DiscountResult::DiscountResult()
: discountPercentOrigin( CT_UNSET ),
  discountValueOrigin( CT_UNSET ),
  discountedArticlePriceOrigin( CT_UNSET )
{
	m_PropertyCollection.add( discountPercent );
	m_PropertyCollection.add( discountValue );
	m_PropertyCollection.add( discountedArticlePrice );
}

DiscountResult::DiscountResult( const DiscountResult & rhs )
{
	m_PropertyCollection.add( discountPercent );
	m_PropertyCollection.add( discountValue );
	m_PropertyCollection.add( discountedArticlePrice );
	this->operator=( rhs );
}

DiscountResult & DiscountResult::operator=( const DiscountResult & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	// Important: NO assignment of m_PropertyCollection,
	// because it contains pointers to member variables!

	source = rhs.source;

	discountPercent = rhs.discountPercent;
	discountPercent.setState( rhs.discountPercent.getState() );
	discountPercentOrigin = rhs.discountPercentOrigin;

	discountValue = rhs.discountValue;
	discountValue.setState( rhs.discountValue.getState() );
	discountValueOrigin = rhs.discountValueOrigin;

	discountedArticlePrice = rhs.discountedArticlePrice;
	discountedArticlePrice.setState( rhs.discountedArticlePrice.getState() );
	discountedArticlePriceOrigin = rhs.discountedArticlePriceOrigin;

	return *this;
}

bool DiscountResult::operator==( const DiscountResult & rhs ) const
{
	return (	source == rhs.source
		     && discountPercent == rhs.discountPercent
		     && discountPercentOrigin == rhs.discountPercentOrigin
		     && discountValue == rhs.discountValue
		     && discountValueOrigin == rhs.discountValueOrigin
		     && discountedArticlePrice == rhs.discountedArticlePrice
		     && discountedArticlePriceOrigin == rhs.discountedArticlePriceOrigin
		     && m_PropertyCollection == rhs.m_PropertyCollection );
}

std::ostream & DiscountResult::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "DiscountResult: source=<" << source << ">";
	strm << ", discountPercent=<" << discountPercent << ">";
	strm << ", discountPercentOrigin=<";
	DiscountCalculatorTypeMapper::toStream( strm, discountPercentOrigin );
	strm << ">";
	strm << ", discountValue=<" << discountValue << ">";
	strm << ", discountValueOrigin=<";
	DiscountCalculatorTypeMapper::toStream( strm, discountValueOrigin );
	strm << ">";
	strm << ", discountedArticlePrice=<" << discountedArticlePrice << ">";
	strm << ", discountedArticlePriceOrigin=<";
	DiscountCalculatorTypeMapper::toStream( strm, discountedArticlePriceOrigin );
	strm << ">";
	return strm;
}

bool DiscountResult::containsUnset() const
{
	return m_PropertyCollection.containsUnset();
}

bool DiscountResult::containsClean() const
{
	return m_PropertyCollection.containsClean();
}

bool DiscountResult::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

bool DiscountResult::isUnset() const
{
	return m_PropertyCollection.isUnset();
}

bool DiscountResult::isClean() const
{
	return m_PropertyCollection.isClean();
}

bool DiscountResult::isDirty() const
{
	return m_PropertyCollection.isDirty();
}


DiscountResultBaseValue::DiscountResultBaseValue()
{
	m_PropertyCollection.add( articleNo );
	m_PropertyCollection.add( quantity );
	m_PropertyCollection.add( baseArticlePrice );
}

DiscountResultBaseValue::DiscountResultBaseValue( const DiscountResultBaseValue & rhs )
{
	m_PropertyCollection.add( articleNo );
	m_PropertyCollection.add( quantity );
	m_PropertyCollection.add( baseArticlePrice );
	this->operator=( rhs );
}

DiscountResultBaseValue & DiscountResultBaseValue::operator=( const DiscountResultBaseValue & rhs )
{
	if( this == &rhs )
	{
		return *this;
	}

	// Important: NO assignment of m_PropertyCollection,
	// because it contains pointers to member variables!

	articleNo = rhs.articleNo;
	articleNo.setState( rhs.articleNo.getState() );

	quantity = rhs.quantity;
	quantity.setState( rhs.quantity.getState() );

	baseArticlePrice = rhs.baseArticlePrice;
	baseArticlePrice.setState( rhs.baseArticlePrice.getState() );

	return *this;
}

bool DiscountResultBaseValue::operator==( const DiscountResultBaseValue & rhs ) const
{
	return (    articleNo == rhs.articleNo
			 && quantity == rhs.quantity
			 && baseArticlePrice == rhs.baseArticlePrice 
			 && m_PropertyCollection == rhs.m_PropertyCollection );
}

std::ostream & DiscountResultBaseValue::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "DiscountResultBaseValue: articleNo=<" << articleNo << ">";
	strm << ", quantity=<" << quantity << ">";
	strm << ", baseArticlePrice=<" << baseArticlePrice << ">";
	return strm;
}

bool DiscountResultBaseValue::containsUnset() const
{
	return m_PropertyCollection.containsUnset();
}

bool DiscountResultBaseValue::containsClean() const
{
	return m_PropertyCollection.containsClean();
}

bool DiscountResultBaseValue::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

bool DiscountResultBaseValue::isUnset() const
{
	return m_PropertyCollection.isUnset();
}

bool DiscountResultBaseValue::isClean() const
{
	return m_PropertyCollection.isClean();
}

bool DiscountResultBaseValue::isDirty() const
{
	return m_PropertyCollection.isDirty();
}



DiscountResult & DiscountCalculatorResult::getDiscountResult( const basar::Int32 positionNo )
{
	DiscountResultCollection::iterator iter = results.find( positionNo );
	if( iter == results.end() )
	{
		DiscountResult dr;
		results[ positionNo ] = dr;
		iter = results.find( positionNo );
	}
	return iter->second;
}

void DiscountCalculatorResult::addRebateInKind( const RebateInKindValue & rebate )
{
	RebateInKindValueCollection::iterator iter = std::find( rebateInKindArticles.begin(), rebateInKindArticles.end(), rebate );
	if( iter != rebateInKindArticles.end() )
	{
		RebateInKindValue & rebateInList( *iter );
		rebateInList.quantity = rebateInList.quantity + rebate.quantity;
		return;
	}

	rebateInKindArticles.push_back( rebate );
}

bool  DiscountCalculatorResult::operator==( const DiscountCalculatorResult & rhs ) const
{
	return (    baseValue == rhs.baseValue 
			 && results == rhs.results
			 && rebateInKindArticles == rhs.rebateInKindArticles );
}

std::ostream & DiscountCalculatorResult::toStream( std::ostream & strm /* = std::cout */ ) const
{
	strm << "DiscountCalculatorResult:" << std::endl << "baseValue=<";
	if( baseValue.isUnset() )
	{
		strm << "UNSET";
	}
	else
	{
		strm << baseValue;
	}
	strm << ">" << std::endl;

	strm << "results=" << std::endl;
	if( !results.empty() )
	{
		DiscountResultCollection::const_iterator iter = results.begin();
		for( ; iter != results.end(); ++iter )
		{
			const DiscountResult & result( iter->second );
			strm << iter->first << ": " << result << std::endl;
		}
	}
	else
	{
		strm << "<UNSET>" << std::endl;
	}

	strm << "rebate in kind=" << std::endl;
	if( !rebateInKindArticles.empty() )
	{
		RebateInKindValueCollection::const_iterator iter = rebateInKindArticles.begin();
		for( ; iter != rebateInKindArticles.end(); ++iter )
		{
			const RebateInKindValue & rebate( *iter );
			strm << rebate << std::endl;
		}
	}
	else
	{
		strm << "<UNSET>" << std::endl;
	}

	return strm;	
}

bool DiscountCalculatorResult::containsUnset() const
{
	bool ret = baseValue.containsUnset();
	if( !ret )
	{
		DiscountResultCollection::const_iterator iter = results.begin();
		for( ; iter != results.end(); ++iter )
		{
			ret |= iter->second.containsUnset();
		}
	}
	if( !ret )
	{
		RebateInKindValueCollection::const_iterator iter = rebateInKindArticles.begin();
		for( ; iter != rebateInKindArticles.end(); ++iter )
		{
			ret |= iter->containsUnset();
		}
	}
	return ret;
}

bool DiscountCalculatorResult::containsClean() const
{
	bool ret = baseValue.containsClean();
	if( !ret )
	{
		DiscountResultCollection::const_iterator iter = results.begin();
		for( ; iter != results.end(); ++iter )
		{
			ret |= iter->second.containsClean();
		}
	}
	if( !ret )
	{
		RebateInKindValueCollection::const_iterator iter = rebateInKindArticles.begin();
		for( ; iter != rebateInKindArticles.end(); ++iter )
		{
			ret |= iter->containsClean();
		}
	}
	return ret;
}

bool DiscountCalculatorResult::containsDirty() const
{
	bool ret = baseValue.containsDirty();
	if( !ret )
	{
		DiscountResultCollection::const_iterator iter = results.begin();
		for( ; iter != results.end(); ++iter )
		{
			ret |= iter->second.containsDirty();
		}
	}
	if( !ret )
	{
		RebateInKindValueCollection::const_iterator iter = rebateInKindArticles.begin();
		for( ; iter != rebateInKindArticles.end(); ++iter )
		{
			ret |= iter->containsDirty();
		}
	}
	return ret;
}

bool DiscountCalculatorResult::isUnset() const
{
	bool ret = baseValue.isUnset();
	DiscountResultCollection::const_iterator iter = results.begin();
	for( ; iter != results.end(); ++iter )
	{
		ret &= iter->second.isUnset();
	}
	RebateInKindValueCollection::const_iterator rikIter = rebateInKindArticles.begin();
	for( ; rikIter != rebateInKindArticles.end(); ++rikIter )
	{
		ret &= rikIter->isUnset();
	}
	return ret;
}

bool DiscountCalculatorResult::isClean() const
{
	bool ret = baseValue.isClean();
	DiscountResultCollection::const_iterator iter = results.begin();
	for( ; iter != results.end(); ++iter )
	{
		ret &= iter->second.isClean();
	}
	RebateInKindValueCollection::const_iterator rikIter = rebateInKindArticles.begin();
	for( ; rikIter != rebateInKindArticles.end(); ++rikIter )
	{
		ret &= rikIter->isClean();
	}
	return ret;
}

bool DiscountCalculatorResult::isDirty() const
{
	bool ret = baseValue.isDirty();
	DiscountResultCollection::const_iterator iter = results.begin();
	for( ; iter != results.end(); ++iter )
	{
		ret &= iter->second.isDirty();
	}
	RebateInKindValueCollection::const_iterator rikIter = rebateInKindArticles.begin();
	for( ; rikIter != rebateInKindArticles.end(); ++rikIter )
	{
		ret &= rikIter->isDirty();
	}
	return ret;
}

} // end namespace discount
} // end namespace libcsc

