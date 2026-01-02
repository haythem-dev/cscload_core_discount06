#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H

#include <discount/orderpositiondiscountprocessed/iorderpositiondiscountprocessedcollection.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedptr.h>
#include <map>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedCollection : public IOrderPositionDiscountProcessedCollection,
												 public std::map<basar::Int32, libcsc::discount::OrderPositionDiscountProcessedPtr>
{
public:
	virtual void insert(
		const basar::Int32 positionNo, 
		const libcsc::discount::OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed
			);
	virtual bool contains( const basar::Int32 positionNo ) const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H
