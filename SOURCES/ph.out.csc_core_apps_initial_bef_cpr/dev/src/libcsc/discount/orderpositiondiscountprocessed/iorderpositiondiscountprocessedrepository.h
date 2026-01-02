#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H

#include <discount/orderpositiondiscountprocessed/iorderpositiondiscountprocessedcollectionptr.h>
#include <datatypes/int32.h>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountProcessedRepository
{
public:
	virtual ~IOrderPositionDiscountProcessedRepository() {}

	virtual IOrderPositionDiscountProcessedCollectionPtr get() const = 0;
	virtual IOrderPositionDiscountProcessedCollectionPtr findByID( const libcsc::Int32 orderNo ) const = 0;
	virtual void save() = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H
