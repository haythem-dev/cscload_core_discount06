#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscount;
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscount> OrderPositionDiscountPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PTR_H
