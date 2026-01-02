#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURN_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURN_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>


namespace libcsc {
namespace document {

class DeliveryAdviceLineReturn
{
	friend class DeliveryAdviceLineReturnMapperBase;
	friend class DeliveryAdviceLineReturnSQLMapper;

public:
	DeliveryAdviceLineReturn();
	virtual ~DeliveryAdviceLineReturn();

	virtual const basar::Int16&         getBranchNo() const;
	virtual const basar::Int32&         getCustomerNo() const;
	virtual const basar::Date&          getDeliveryAdviceDate() const;
	virtual const basar::VarString&     getDeliveryAdviceNo() const;
	virtual const basar::Int32&         getDeliveryAdvicePosNo() const;

	virtual const basar::Int16&         getBlockedForreturns() const;
	virtual const basar::Int32&         getQuantityReturned() const;
	virtual const basar::Int32&         getQuantityReturnedRebateInKind() const;
	virtual const basar::Int32&         getQuantityReturnRejected() const;

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::VarString					m_DeliveryAdviceNo;
	libcsc::Int32						m_DeliveryAdvicePosNo;

	libcsc::Int16						m_BlockedForreturns;
	libcsc::Int32						m_QuantityReturned;
	libcsc::Int32						m_QuantityReturnedRebateInKind;
	libcsc::Int32						m_QuantityReturnRejected;

};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_RETURN_H
