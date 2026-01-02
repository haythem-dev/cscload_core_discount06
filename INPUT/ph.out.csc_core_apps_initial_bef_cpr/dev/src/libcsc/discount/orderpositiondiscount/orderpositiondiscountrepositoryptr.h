#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountRepository;
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscountRepository> OrderPositionDiscountRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_PTR_H
