#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueRepository;
typedef boost::shared_ptr<libcsc::discount::DiscountBaseValueRepository> DiscountBaseValueRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_PTR_H
