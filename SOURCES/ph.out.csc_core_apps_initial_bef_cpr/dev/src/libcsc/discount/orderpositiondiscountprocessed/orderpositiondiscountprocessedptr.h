#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessed;
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscountProcessed> OrderPositionDiscountProcessedPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_PTR_H
