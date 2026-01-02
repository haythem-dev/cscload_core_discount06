#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILS_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILS_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>


namespace libcsc {
namespace document {

class DeliveryAdviceLineDetails
{
	friend class DeliveryAdviceLineDetailsMapperBase;
	friend class DeliveryAdviceLineDetailsSQLMapper;

public:
	DeliveryAdviceLineDetails();
	virtual ~DeliveryAdviceLineDetails();

	virtual const basar::Int16&			getBranchNo() const;
	virtual const basar::Int32&			getCustomerNo() const;
	virtual const basar::Date&			getDeliveryAdviceDate() const;
	virtual const basar::Int32&			getPharmosOrderNo() const;
	virtual const basar::Int32&			getPharmosOrderPosNo() const;
	virtual const basar::Int32&			getDeliveryPosNo() const;

	virtual const basar::Int32&			getQuantityDelivery() const;
	virtual const basar::VarString&		getBatch() const;
	virtual const basar::Date&			getExpiryDate() const;
	virtual const basar::Int32&			getPackageId() const;
	virtual const basar::VarString&		getTrackingId() const;
	virtual const basar::Int32&			getQuantityLack() const;
	virtual const basar::Int16&			getPreCalcBatchChanged() const;

	virtual bool						isPreCalcBatchChanged() const;

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::Int32						m_PharmosOrderNo;
	libcsc::Int32						m_PharmosOrderPosNo;
	libcsc::Int32						m_DeliveryPosNo;

	libcsc::Int32						m_QuantityDelivery;
	libcsc::VarString					m_Batch;
	libcsc::Date						m_ExpiryDate;
	libcsc::Int32						m_PackageId;
	libcsc::VarString					m_TrackingId;
	libcsc::Int32						m_QuantityLack;
	libcsc::Int16						m_PreCalcBatchChanged;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_DETAILS_H
