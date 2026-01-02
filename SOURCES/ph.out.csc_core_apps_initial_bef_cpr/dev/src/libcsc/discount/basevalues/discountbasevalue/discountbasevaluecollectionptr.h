#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_PTR_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueCollection;
typedef boost::shared_ptr<libcsc::discount::DiscountBaseValueCollection> DiscountBaseValueCollectionPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_COLLECTION_PTR_H
