#ifndef GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IDiscountBaseValueRepository;
typedef boost::shared_ptr<libcsc::discount::IDiscountBaseValueRepository> IDiscountBaseValueRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H
