#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_H

#include <discount/orderpositiondiscount/orderpositiondiscountptr.h>
#include <list>

namespace libcsc
{
namespace discount
{
typedef std::list<libcsc::discount::OrderPositionDiscountPtr> OrderPositionDiscountList;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_H
