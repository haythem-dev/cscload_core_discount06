#include "discountbasevaluecollection.h"
#include "discountbasevalue.h"

namespace libcsc
{
namespace discount
{
DiscountBaseValueCollection::DiscountBaseValueCollection()
{
}

DiscountBaseValueCollection::~DiscountBaseValueCollection()
{
	clear();
}

void DiscountBaseValueCollection::clear()
{
	// TODO: gefilterte listen leeren
	m_ValuesByArticleNo.clear();
	m_Values.clear();
}

bool DiscountBaseValueCollection::empty() const
{
	return m_Values.empty();
}

void DiscountBaseValueCollection::add( DiscountBaseValuePtr value )
{
	m_Values.push_back( value );
	addByArticleNo( value );
}

void DiscountBaseValueCollection::addByArticleNo( DiscountBaseValuePtr value )
{
	basar::Int32 articleNo = value->getArticleNo();
	if( 0 < articleNo )
	{
		m_ValuesByArticleNo.push_back( value );
	}
}

const DiscountBaseValueList & DiscountBaseValueCollection::getCollection() const
{
	return m_Values;
}

const FilteredDiscountBaseValueList & DiscountBaseValueCollection::getCollectionByArticleNo() const
{
	return m_ValuesByArticleNo;
}

} // end namespace discount
} // end namespace libcsc

