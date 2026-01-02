#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PTR_H

#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscountList> OrderPositionDiscountListPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PTR_H
