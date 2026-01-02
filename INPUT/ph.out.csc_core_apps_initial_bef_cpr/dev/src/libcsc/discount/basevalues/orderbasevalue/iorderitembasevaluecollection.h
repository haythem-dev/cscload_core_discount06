#ifndef GUARD_LIBCSC_I_ORDER_ITEM_BASE_VALUE_COLLECTION_H
#define GUARD_LIBCSC_I_ORDER_ITEM_BASE_VALUE_COLLECTION_H

#include <map>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_decimal.h>
#include <discount/basevalues/orderbasevalue/orderitembasevalueptr.h>

namespace libcsc
{
namespace discount
{
class IOrderItemBaseValueCollection : public std::multimap<basar::Int32, libcsc::discount::OrderItemBaseValuePtr>
{
public:
	virtual ~IOrderItemBaseValueCollection() {}

	virtual basar::Int32 getArticleQuantity() const = 0;
	virtual const basar::Decimal getArticleValue( const basar::Int32 positionNo = -1 ) const = 0;
	virtual const basar::Decimal getRiKValue( const basar::Int32 positionNo = -1 ) const = 0;
	virtual const basar::VarString getArticleNumbers() const = 0;
	virtual bool isArticleContained( const basar::Int32 articleNo ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_ITEM_BASE_VALUE_COLLECTION_H
