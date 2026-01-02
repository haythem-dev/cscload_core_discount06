#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_FINDER_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_FINDER_H

#include <discount/orderpositiondiscount/orderpositiondiscountcollectionptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountFinder
{
public:
	virtual ~IOrderPositionDiscountFinder() {}

	virtual OrderPositionDiscountListPtr findByID( const basar::Int32 orderNo, const basar::Int32 positionNo = 0 ) const = 0;
//	virtual basar::Int16				 findNumOfAdditionalPosDiscounts( const basar::Int32 orderNo, const basar::Int32 positionNo ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_FINDER_H
