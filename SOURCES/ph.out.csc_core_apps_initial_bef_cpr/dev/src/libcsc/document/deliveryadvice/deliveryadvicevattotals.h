#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALS_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALS_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>


namespace libcsc {
namespace document {

class DeliveryAdviceVatTotals
{
	friend class DeliveryAdviceVatTotalsMapperBase;
	friend class DeliveryAdviceVatTotalsSQLMapper;

public:
	DeliveryAdviceVatTotals();
	virtual ~DeliveryAdviceVatTotals();

	virtual const basar::Int16 &		getBranchNo() const;
	virtual const basar::Int32 &		getCustomerNo() const;
	virtual const basar::Date&			getDeliveryAdviceDate() const;
	virtual const basar::VarString &	getDeliveryAdviceNo() const;

	virtual const basar::VarString&		getVat() const;

	virtual const basar::Decimal&		getVatPercentage() const;
	virtual const basar::Decimal&		getNetValue() const;
	virtual const basar::Decimal&		getVatValue() const;
    virtual const basar::Decimal&		getSumLineFee() const;
    virtual const basar::Decimal&		getSumPackageFee() const;

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::VarString					m_DeliveryAdviceNo;

	libcsc::VarString					m_Vat;

	libcsc::Decimal						m_VatPercentage;
	libcsc::Decimal						m_NetValue;
	libcsc::Decimal						m_VatValue;
    libcsc::Decimal						m_SumLineFee;
    libcsc::Decimal						m_SumPackageFee;

};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALS_H
