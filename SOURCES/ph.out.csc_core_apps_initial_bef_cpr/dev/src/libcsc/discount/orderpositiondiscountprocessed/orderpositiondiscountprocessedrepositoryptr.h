#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedRepository;
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscountProcessedRepository> OrderPositionDiscountProcessedRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H
