#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_H

#include <datatypes/decimal.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>
#include <iostream>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscount
{
	// because of OR mapping
	friend class OrderPositionDiscountMapperBase;

public:
	OrderPositionDiscount();
	virtual ~OrderPositionDiscount();

	const libcsc::Int32 & getOrderNo() const;
	const libcsc::Int32 & getPositionNo() const;
	const OrderPositionDiscountMode & getDiscountMode() const;
	const libcsc::Decimal & getDiscountValue() const;
	const libcsc::Decimal & getDiscountPercent() const;
	const libcsc::Int32 & getDiscountQty() const;
	const libcsc::Int32 & getRebateInKindPositionNo() const;
	const libcsc::Int32 & getRebateInKindOrderNo() const;
	const libcsc::VarString& getPharmacyGroupId() const;

	void setOrderNo( const libcsc::Int32 & orderNo );
	void setPositionNo( const libcsc::Int32 & positionNo );
	void setDiscountMode( const OrderPositionDiscountMode & discountMode );
	void setDiscountValue( const libcsc::Decimal & discountValue );
	void setDiscountPercent( const libcsc::Decimal & discountPercent );
	void setDiscountQty( const libcsc::Int32 & discountQty );
	void setRebateInKindPositionNo( const libcsc::Int32 & rebateInKindPositionNo );
	void setRebateInKindOrderNo(const libcsc::Int32 & rebateInKindOrderNo);
	void setPharmacyGroupId(const libcsc::VarString& pharmacyGroup);

	bool isDiscountValid() const;
	bool isRebateInKind() const;
	bool isRebateInKindExtraPosition() const;
	bool isDiscountFixedPrice() const;
	bool isDiscountValuePercent() const;

	virtual std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	OrderPositionDiscountMode		m_DiscountMode;
	libcsc::Int32					m_OrderNo;
	libcsc::Int32					m_PositionNo;
	libcsc::Decimal					m_DiscountValue;
	libcsc::Decimal					m_DiscountPercent;
	libcsc::Int32					m_DiscountQty;
	libcsc::Int32					m_RebateInKindPositionNo;
	libcsc::Int32					m_RebateInKindOrderNo;
	libcsc::VarString				m_PharmacyGroupId;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::OrderPositionDiscount & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_H
