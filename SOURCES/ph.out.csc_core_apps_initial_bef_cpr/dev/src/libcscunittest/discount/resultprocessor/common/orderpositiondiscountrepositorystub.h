#ifndef GUARD_LIBCSC_UNITTEST_ORDER_POSITION_DISCOUNT_REPOSITORY_STUB_H
#define GUARD_LIBCSC_UNITTEST_ORDER_POSITION_DISCOUNT_REPOSITORY_STUB_H

#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>

namespace libcscUnitTest
{
namespace discount
{
class OrderPositionDiscountRepositoryStub : public libcsc::discount::IOrderPositionDiscountRepository
{
public:
	OrderPositionDiscountRepositoryStub();
	virtual ~OrderPositionDiscountRepositoryStub();

	virtual void reset();
	virtual libcsc::discount::OrderPositionDiscountPtr getOrderPositionDiscount( const basar::Int32 positionNo, const libcsc::discount::OrderPositionDiscountMode discountMode );
	virtual libcsc::discount::OrderPositionDiscountListPtr get();
	virtual void save();
	virtual void erase( libcsc::discount::OrderPositionDiscountPtr orderPositionDiscount );
	virtual libcsc::discount::OrderPositionDiscountListPtr findByID( const basar::Int32 orderNo, const basar::Int32 positionNo = 0 ) const;

private:
	OrderPositionDiscountRepositoryStub( const OrderPositionDiscountRepositoryStub & );
	OrderPositionDiscountRepositoryStub & operator=( const OrderPositionDiscountRepositoryStub & );

};

} // end namespace discount
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_ORDER_POSITION_DISCOUNT_REPOSITORY_STUB_H
