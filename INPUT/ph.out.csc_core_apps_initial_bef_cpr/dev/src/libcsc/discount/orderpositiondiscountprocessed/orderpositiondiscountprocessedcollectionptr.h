#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H

#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedcollection.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
typedef boost::shared_ptr<libcsc::discount::OrderPositionDiscountProcessedCollection> OrderPositionDiscountProcessedCollectionPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_COLLECTION_PTR_H
