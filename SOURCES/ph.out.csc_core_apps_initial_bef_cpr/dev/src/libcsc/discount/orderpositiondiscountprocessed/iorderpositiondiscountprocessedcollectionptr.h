#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountProcessedCollection;
typedef boost::shared_ptr<libcsc::discount::IOrderPositionDiscountProcessedCollection> IOrderPositionDiscountProcessedCollectionPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H
