#include "cmnut.h"
#include "orderpositiondiscountrepositorystub.h"

namespace libcscUnitTest
{
namespace discount
{
using namespace libcsc::discount;

OrderPositionDiscountRepositoryStub::OrderPositionDiscountRepositoryStub()
{
}

OrderPositionDiscountRepositoryStub::~OrderPositionDiscountRepositoryStub()
{
}

void OrderPositionDiscountRepositoryStub::reset()
{
}

OrderPositionDiscountPtr OrderPositionDiscountRepositoryStub::getOrderPositionDiscount( const basar::Int32 positionNo, const OrderPositionDiscountMode discountMode )
{
	positionNo;discountMode;
	return OrderPositionDiscountPtr();
}

OrderPositionDiscountListPtr OrderPositionDiscountRepositoryStub::get()
{
	return OrderPositionDiscountListPtr();
}

void OrderPositionDiscountRepositoryStub::save()
{
}

void OrderPositionDiscountRepositoryStub::erase( OrderPositionDiscountPtr orderPositionDiscount )
{
}

OrderPositionDiscountListPtr OrderPositionDiscountRepositoryStub::findByID( const basar::Int32 orderNo, const basar::Int32 positionNo /* = 0 */ ) const
{
	orderNo;positionNo;
	return OrderPositionDiscountListPtr();
}

} // end namespace discount
} // end namespace libcscUnitTest

