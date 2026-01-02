#include <customer/customer.h>

namespace libcsc {
namespace customer {

Customer::Customer()
{
}

Customer::~Customer()
{
}

basar::Int16 Customer::getBranchNo() const
{
	return m_BranchNo;
}

basar::Int32 Customer::getCustomerNo() const
{
	return m_CustomerNo;
}

basar::VarString const Customer::getPharmacyName() const
{
	return m_PharmacyName;
}

basar::VarString const Customer::getStreet() const
{
	return m_Street;
}

basar::VarString const Customer::getPostalCode() const
{
	return m_PostalCode;
}

basar::VarString const Customer::getCity() const
{
	return m_City;
}

basar::VarString const Customer::getPharmacyOwner() const
{
	return m_PharmacyOwner;
}

basar::VarString const Customer::getCustomerGroup() const
{
	return m_CustomerGroup;
}

basar::Int32 Customer::getCustomerNoChain() const
{
	return m_CustomerNoChain;
}

bool Customer::isActive() const
{
	return m_IsActive;
}

bool Customer::hasTender() const
{
	return m_HasTender;
}

XMLInfoLevelEnum Customer::getXMLInfoLevel() const
{
	return m_XMLInfoLevel;
}

basar::VarString const Customer::getMailAddress() const
{
	return m_MailAddress;
}

basar::VarString const Customer::getFaxNo() const
{
	return m_FaxNo;
}

basar::VarString const Customer::getLanguage() const
{
	return m_Language;
}

basar::Int16 Customer::getSalutationId() const
{
	return m_SalutationId;
}

basar::Decimal Customer::getLogisticSurchargePct() const
{
	return m_LogisticSurchargePct;
}

basar::Decimal Customer::getLogisticSurchargeMinValue() const
{
	return m_LogisticSurchargeMinValue;
}


basar::Int32 Customer::getPartnerNo() const
{
	return m_PartnerNo;
}

basar::Decimal Customer::getLimit() const
{
	return m_Limit;
}

basar::Decimal Customer::getSumDebitSide() const
{
	return m_SumDebitSide;
}

basar::Decimal Customer::getSumCreditSide() const
{
	return m_SumCreditSide;
}

basar::Decimal Customer::getSumMonthTurnover() const
{
	return m_SumMonthTurnover;
}

basar::Decimal Customer::getSumDayTurnover() const
{
	return m_SumDayTurnover;
}

basar::Decimal Customer::getSumReturns() const
{
	return m_SumReturns;
}

basar::Decimal Customer::getSumGoodsReceipt() const
{
	return m_SumGoodsReceipt;
}


} // end namespace customer
} // end namespace libcsc

