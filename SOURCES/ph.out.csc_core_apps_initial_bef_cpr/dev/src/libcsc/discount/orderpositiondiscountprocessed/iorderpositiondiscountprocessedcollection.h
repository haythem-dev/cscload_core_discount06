#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H

#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountProcessedCollection
{
public:
	~IOrderPositionDiscountProcessedCollection() {}

	virtual void insert(
		const basar::Int32 positionNo, 
		const libcsc::discount::OrderPositionDiscountProcessedPtr orderPositionDiscountProcessed
			) = 0;
	virtual bool contains( const basar::Int32 positionNo ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_COLLECTION_PROCESSED_H
