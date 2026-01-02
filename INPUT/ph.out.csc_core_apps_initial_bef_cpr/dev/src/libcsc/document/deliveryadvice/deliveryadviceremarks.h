#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>
#include <datatypes/orderremarktypeenum.h>


namespace libcsc {
namespace document {

class DeliveryAdviceRemarks
{
	friend class DeliveryAdviceRemarksMapperBase;
	friend class DeliveryAdviceLineRemarksSQLMapper;

public:
	DeliveryAdviceRemarks();
	virtual ~DeliveryAdviceRemarks();

	virtual const basar::Int16&				getBranchNo() const;
	virtual const basar::Int32&				getCustomerNo() const;
	virtual const basar::Date&				getDeliveryAdviceDate() const;
	virtual const basar::Int32&				getCSCOrderNo() const;
	virtual const basar::Int32&				getCSCOrderPosNo() const;

	virtual const ::OrderRemarkTypeEnum&	getRemarkType() const;
	virtual const basar::Int16&				getSerialNo() const;
	
	virtual const basar::VarString&			getRemarkText() const;

protected:

private:
	libcsc::Int16							m_BranchNo;
	libcsc::Int32							m_CustomerNo;
	libcsc::Date							m_DeliveryAdviceDate;
	libcsc::Int32							m_CSCOrderNo;
	libcsc::Int32							m_CSCOrderPosNo;

	libcsc::OrderRemarkTypeEnum				m_RemarkType;
	libcsc::Int16							m_SerialNo;

	libcsc::VarString						m_RemarkText;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_H
