#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNT_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNT_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>
#include "types/kindofdiscountenum.inc"

namespace libcsc {
namespace document {

class DeliveryAdviceLineDiscount
{
	friend class DeliveryAdviceLineDiscountMapperBase;
	friend class DeliveryAdviceLineDiscountSQLMapper;

public:
	DeliveryAdviceLineDiscount();
	virtual ~DeliveryAdviceLineDiscount();

	virtual const basar::Int16&				getBranchNo() const;
	virtual const basar::Int32&				getCustomerNo() const;
	virtual const basar::Date&				getDeliveryAdviceDate() const;
	virtual const basar::Int32&			    getPharmosOrderNo() const;
	virtual const basar::Int32&				getPharmosOrderPosNo() const;

	virtual const basar::Int16&				getDiscountMode() const;
	virtual const basar::VarString&			getDiscountModeName() const;

	virtual const basar::Decimal&			getDiscount() const;
	virtual const basar::VarString&			getOrigin() const;
	virtual const basar::Int16&				getDeleteReason() const;
	virtual const basar::Decimal&			getDiscountValue() const;
	virtual const basar::Int16&				getDiscountType() const;
	virtual const basar::Int16&				getHierarchy() const;
	virtual const basar::Int16&				getCalculationBasis() const;
	virtual const enum KindOfDiscountEnum&	getKindOfDiscount() const;

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::Int32                       m_PharmosOrderNo;
	libcsc::Int32						m_PharmosOrderPosNo;

	libcsc::Int16						m_DiscountMode;
	libcsc::VarString					m_DiscountModeName;

	libcsc::Decimal						m_Discount;
	libcsc::VarString					m_Origin;
	libcsc::Int16						m_DeleteReason;
	libcsc::Decimal						m_DiscountValue;
	libcsc::Int16						m_DiscountType;
	libcsc::Int16						m_Hierarchy;
	libcsc::Int16						m_CalculationBasis;
	enum KindOfDiscountEnum				m_KindOfDiscount;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DISCOUNT_H
