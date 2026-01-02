#ifndef GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_COLLECTION_H
#define GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_COLLECTION_H

#include <discount/basevalues/orderbasevalue/iorderitembasevaluecollection.h>
#include <boost/shared_ptr.hpp>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_decimal.h>

namespace libcsc
{
namespace discount
{
class OrderItemBaseValueCollection : public IOrderItemBaseValueCollection
{
public:
	void insert( const basar::Int32 articleNo, libcsc::discount::OrderItemBaseValuePtr orderItemBaseValue );
	virtual basar::Int32 getArticleQuantity() const;
	virtual const basar::Decimal getArticleValue( const basar::Int32 positionNo = -1 ) const;
	virtual const basar::Decimal getRiKValue( const basar::Int32 positionNo = -1 ) const;
	virtual const basar::VarString getArticleNumbers() const;
	virtual bool isArticleContained( const basar::Int32 articleNo ) const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_COLLECTION_H
