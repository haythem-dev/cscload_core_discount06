#ifndef GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IDiscountLogPositionRepository;
typedef boost::shared_ptr<libcsc::discount::IDiscountLogPositionRepository> IDiscountLogPositionRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_PTR_H
