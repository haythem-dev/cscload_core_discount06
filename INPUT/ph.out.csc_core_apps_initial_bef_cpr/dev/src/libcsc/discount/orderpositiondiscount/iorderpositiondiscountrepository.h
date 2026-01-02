#ifndef GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_REPOSITORY_H
#define GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_REPOSITORY_H

#include <discount/orderpositiondiscount/iorderpositiondiscountfinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscountcollectionptr.h>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>
#include <datatypes/int32.h>
#include <datatypes/decimal.h>

namespace libcsc
{
namespace discount
{
class IOrderPositionDiscountRepository : public IOrderPositionDiscountFinder
{
public:
	virtual ~IOrderPositionDiscountRepository() {}

	virtual void reset() = 0;
	virtual OrderPositionDiscountPtr getOrderPositionDiscount( const basar::Int32 positionNo, const OrderPositionDiscountMode discountMode ) = 0;
	virtual OrderPositionDiscountPtr getOrderPositionDiscount(const basar::Int32 positionNo, const OrderPositionDiscountMode discountMode, const basar::Int32 rebInKindPosNo, const basar::Int32 rebInKindOrderNo) = 0;
	virtual OrderPositionDiscountListPtr get() = 0;
	virtual void save() = 0;
	virtual void erase( OrderPositionDiscountPtr orderPositionDiscount ) = 0;
	virtual OrderPositionDiscountListPtr findByID( const basar::Int32 orderNo, const basar::Int32 positionNo = 0 ) const = 0;
	virtual OrderPositionDiscountListPtr findByIDBackward(const basar::Int32 rebateinkindorderno, const basar::Int32 rebateinkindpositionNo = 0) const = 0;

};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_POSITION_DISCOUNT_REPOSITORY_H
