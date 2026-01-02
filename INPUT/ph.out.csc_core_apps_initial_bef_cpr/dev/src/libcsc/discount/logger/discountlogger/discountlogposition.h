#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_H

#include <datatypes/decimal.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <discount/calculator/discountcalculatortypeenum.h>

namespace libcsc
{
namespace discount
{
class DiscountLogPosition
{
	// because of OR mapping
	friend class DiscountLogPositionMapperBase;

public:
	DiscountLogPosition();

	const libcsc::Int32 & getOrderNo() const;
	const libcsc::Int32 & getPositionNo() const;
	const DiscountCalculatorType & getDiscountCalculatorType() const;
	const libcsc::Decimal & getDiscountValue() const;
	const libcsc::Decimal & getDiscountPercent() const;
	const libcsc::Int32 & getDiscountQty() const;
	const libcsc::Int32 & getRebateInKindPosNo() const;

	void setOrderNo( const libcsc::Int32 & orderNo );
	void setPositionNo( const libcsc::Int32 & positionNo );
	void setDiscountCalculatorType( const DiscountCalculatorType & discountCalculatorType );
	void setDiscountValue( const libcsc::Decimal & discountValue );
	void setDiscountPercent( const libcsc::Decimal & discountPercent );
	void setDiscountQty( const libcsc::Int32 & discountQty );
	void setRebateInKindPosNo( const libcsc::Int32 & rebateInKindPosNo );

private:
	DiscountCalculatorType			m_DiscountCalculatorType;
	libcsc::Int32					m_OrderNo;
	libcsc::Int32					m_PositionNo;
	libcsc::Decimal					m_DiscountValue;
	libcsc::Decimal					m_DiscountPercent;
	libcsc::Int32					m_DiscountQty;
	libcsc::Int32					m_RebateInKindPosNo;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_H
