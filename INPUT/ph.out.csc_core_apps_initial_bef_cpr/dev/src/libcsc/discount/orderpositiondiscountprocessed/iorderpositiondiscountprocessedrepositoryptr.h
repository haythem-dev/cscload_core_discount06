#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountProcessedRepository;
typedef boost::shared_ptr<libcsc::discount::IOrderPositionDiscountProcessedRepository> IOrderPositionDiscountProcessedRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_PTR_H
