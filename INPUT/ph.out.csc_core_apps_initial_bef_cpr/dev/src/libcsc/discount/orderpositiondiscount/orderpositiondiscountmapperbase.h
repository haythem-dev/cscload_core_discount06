#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MAPPER_BASE_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MAPPER_BASE_H

#include <discount/orderpositiondiscount/orderpositiondiscountptr.h>
#include <libbasar_definitions.h>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountMapperBase
{
public:
	OrderPositionDiscountMapperBase( OrderPositionDiscountPtr positionDiscount );

	void map();

protected:
	virtual ~OrderPositionDiscountMapperBase();

	virtual void doMap() = 0;

	void setOrderNo( const basar::Int32 orderNo );
	void setPositionNo( const basar::Int32 positionNo );
	void setDiscountMode( const OrderPositionDiscountMode discountMode );
	void setDiscountValue( const basar::Decimal discountValue );
	void setDiscountPercent( const basar::Decimal discountPercent );
	void setDiscountQty( const basar::Int16 discountQty );
	void setRebateInKindPositionNo( const basar::Int32 rebateInKindPositionNo );
	void setRebateInKindOrderNo(const basar::Int32 rebateInKindOrderNo);
	void setPharmacyGroupId(const basar::VarString pharmacyGroup);

private:
	OrderPositionDiscountPtr	m_PositionDiscount;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_MAPPER_BASE_H
