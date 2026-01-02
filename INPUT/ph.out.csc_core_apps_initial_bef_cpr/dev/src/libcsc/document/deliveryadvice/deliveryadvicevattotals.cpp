#include "deliveryadvicevattotals.h"

namespace libcsc {
namespace document {

DeliveryAdviceVatTotals::DeliveryAdviceVatTotals()
{
}

DeliveryAdviceVatTotals::~DeliveryAdviceVatTotals()
{
}

const basar::Int16 & DeliveryAdviceVatTotals::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32 & DeliveryAdviceVatTotals::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Date & DeliveryAdviceVatTotals::getDeliveryAdviceDate() const
{
	return m_DeliveryAdviceDate;
}

const basar::VarString & DeliveryAdviceVatTotals::getDeliveryAdviceNo() const
{
	return m_DeliveryAdviceNo;
}

const basar::VarString& DeliveryAdviceVatTotals::getVat() const
{
	return m_Vat;
}

const basar::Decimal& DeliveryAdviceVatTotals::getVatPercentage() const
{
	return m_VatPercentage;
}

const basar::Decimal& DeliveryAdviceVatTotals::getNetValue() const
{
	return m_NetValue;
}

const basar::Decimal& DeliveryAdviceVatTotals::getVatValue() const
{
	return m_VatValue;
}

const basar::Decimal& DeliveryAdviceVatTotals::getSumLineFee() const
{
    return m_SumLineFee;
}

const basar::Decimal& DeliveryAdviceVatTotals::getSumPackageFee() const
{
    return m_SumPackageFee;
}


} // namespace document
} // namespace libcsc
