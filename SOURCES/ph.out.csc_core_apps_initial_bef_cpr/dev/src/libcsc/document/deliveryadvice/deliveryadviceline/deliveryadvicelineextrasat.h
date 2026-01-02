#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>
#include <datatypes/boolean.h>


namespace libcsc {
namespace document {

class DeliveryAdviceLineExtrasAT
{
	friend class DeliveryAdviceLineExtrasATMapperBase;
	friend class DeliveryAdviceLineExtrasATSQLMapper;

public:
	DeliveryAdviceLineExtrasAT();
	virtual ~DeliveryAdviceLineExtrasAT();

	virtual const basar::Int16&			getBranchNo() const;
	virtual const basar::Int32&			getCustomerNo() const;
	virtual const basar::Date&			getDeliveryAdviceDate() const;
	virtual const basar::Int32&			getPharmosOrderNo() const;
	virtual const basar::Int32&			getPharmosOrderPosNo() const;
	virtual const basar::Int32&			getDeliveryPosNo() const;

	virtual bool						isNarcotic() const;
	virtual bool						isRX() const;
	virtual bool						isPsychotropic() const;
	virtual bool						isVeterinary() const;
	virtual bool						isHazardous() const;

	virtual bool						isReportable() const;
	virtual bool						isShortExpiry() const;

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::Int32						m_PharmosOrderNo;
	libcsc::Int32						m_PharmosOrderPosNo;
	libcsc::Int32						m_DeliveryPosNo;

	libcsc::Bool						m_IsNarcotic;
	libcsc::Bool						m_IsRX;
	libcsc::Bool						m_IsPsychotropic;
	libcsc::Bool						m_IsVeterinary;
	libcsc::Bool						m_IsHazardous;
	libcsc::Bool						m_IsReportable;
	libcsc::Bool						m_IsShortExpiry;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_EXTRAS_AT_H
