#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_H

#include "idiscountbasevaluegetter.h"

namespace libcsc
{
namespace discount
{
class DiscountBaseValueCollection : public IDiscountBaseValueGetter
{
public:
	DiscountBaseValueCollection();
	virtual ~DiscountBaseValueCollection();

	void clear();
	bool empty() const;
	void add( DiscountBaseValuePtr value );

	virtual const DiscountBaseValueList & getCollection() const;
	virtual const FilteredDiscountBaseValueList & getCollectionByArticleNo() const;

private:
	void addByArticleNo( DiscountBaseValuePtr value );

	DiscountBaseValueList			m_Values;
	FilteredDiscountBaseValueList	m_ValuesByArticleNo;
	// TODO: weitere container anlegen
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_H
