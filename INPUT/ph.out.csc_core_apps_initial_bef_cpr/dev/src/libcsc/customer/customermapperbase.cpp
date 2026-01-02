#include <customer/customermapperbase.h>
#include <customer/customer.h>

namespace libcsc {
namespace customer {

CustomerMapperBase::CustomerMapperBase(CustomerPtr customer)
: m_Customer(customer)
{
}

CustomerMapperBase::~CustomerMapperBase()
{
}

void CustomerMapperBase::map(bool withTender, bool withCreditLimit, bool withLogisticSurcharge, int countryPhoneCode)
{
    doMap(countryPhoneCode);
	if (true == withTender)
		doMapTender();
	if (true == withCreditLimit)
		doMapCreditLimit();
	if (true == withLogisticSurcharge)
		doMapLogisticSurcharge();
}

void CustomerMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_Customer->m_BranchNo = branchNo;
	m_Customer->m_BranchNo.setClean();
}

void CustomerMapperBase::setCustomerNo(const basar::Int32 customerNo)
{
	m_Customer->m_CustomerNo = customerNo;
	m_Customer->m_CustomerNo.setClean();
}

void CustomerMapperBase::setPharmacyName(const basar::VarString& pharmacyName)
{
	m_Customer->m_PharmacyName = pharmacyName;
	m_Customer->m_PharmacyName.setClean();
}

void CustomerMapperBase::setStreet(const basar::VarString& street)
{
	m_Customer->m_Street = street;
	m_Customer->m_Street.setClean();
}

void CustomerMapperBase::setPostalCode(const basar::VarString& postalCode)
{
	m_Customer->m_PostalCode = postalCode;
	m_Customer->m_PostalCode.setClean();
}

void CustomerMapperBase::setCity(const basar::VarString& city)
{
	m_Customer->m_City = city;
	m_Customer->m_City.setClean();
}

void CustomerMapperBase::setPharmacyOwner(const basar::VarString& pharmacyOwner)
{
	m_Customer->m_PharmacyOwner = pharmacyOwner;
	m_Customer->m_PharmacyOwner.setClean();
}

void CustomerMapperBase::setCustomerGroup(const basar::VarString& customerGroup)
{
	m_Customer->m_CustomerGroup = customerGroup;
	m_Customer->m_CustomerGroup.setClean();
}

void CustomerMapperBase::setCustomerNoChain(const basar::Int32 customerNoChain)
{
	m_Customer->m_CustomerNoChain = customerNoChain;
	m_Customer->m_CustomerNoChain.setClean();
}

void CustomerMapperBase::setIsActive(const bool isActive)
{
	m_Customer->m_IsActive = isActive;
	m_Customer->m_IsActive.setClean();
}

void CustomerMapperBase::setHasTender(const bool hasTender)
{
	m_Customer->m_HasTender = hasTender;
	m_Customer->m_HasTender.setClean();
}

void CustomerMapperBase::setXmlInfoLevel(const basar::Int32 xmlinfolevel)
{
	m_Customer->m_XMLInfoLevel = static_cast<XMLInfoLevelEnum>(xmlinfolevel);
}

void CustomerMapperBase::setMailAddress(const basar::VarString& mailAddress)
{
	m_Customer->m_MailAddress = mailAddress;
	m_Customer->m_MailAddress.setClean();
}

void CustomerMapperBase::setFaxNo(const basar::VarString& faxNo)
{
	m_Customer->m_FaxNo = faxNo;
	m_Customer->m_FaxNo.setClean();
}

void CustomerMapperBase::setLanguage(const basar::VarString& language)
{
	m_Customer->m_Language = language;
	m_Customer->m_Language.setClean();
}

void CustomerMapperBase::setSalutationId(const basar::Int16 salutationId)
{
	m_Customer->m_SalutationId = salutationId;
	m_Customer->m_SalutationId.setClean();
}

void CustomerMapperBase::setLogisticSurchargePct(const basar::Decimal& val)
{
	m_Customer->m_LogisticSurchargePct = val;
	m_Customer->m_LogisticSurchargePct.setClean();
}

void CustomerMapperBase::setLogisticSurchargeMinValue(const basar::Decimal& val)
{
	m_Customer->m_LogisticSurchargeMinValue = val;
	m_Customer->m_LogisticSurchargeMinValue.setClean();
}

void CustomerMapperBase::setPartnerNo(const basar::Int32 val)
{
	m_Customer->m_PartnerNo = val;
	m_Customer->m_PartnerNo.setClean();
}

void CustomerMapperBase::setLimit(const basar::Decimal& val)
{
	m_Customer->m_Limit = val;
	m_Customer->m_Limit.setClean();
}

void CustomerMapperBase::setSumDebitSide(const basar::Decimal& val)
{
	m_Customer->m_SumDebitSide = val;
	m_Customer->m_SumDebitSide.setClean();
}

void CustomerMapperBase::setSumCreditSide(const basar::Decimal& val)
{
	m_Customer->m_SumCreditSide = val;
	m_Customer->m_SumCreditSide.setClean();
}

void CustomerMapperBase::setSumMonthTurnover(const basar::Decimal& val)
{
	m_Customer->m_SumMonthTurnover = val;
	m_Customer->m_SumMonthTurnover.setClean();
}

void CustomerMapperBase::setSumDayTurnover(const basar::Decimal& val)
{
	m_Customer->m_SumDayTurnover = val;
	m_Customer->m_SumDayTurnover.setClean();
}

void CustomerMapperBase::setSumReturns(const basar::Decimal& val)
{
	m_Customer->m_SumReturns = val;
	m_Customer->m_SumReturns.setClean();
}

void CustomerMapperBase::setSumGoodsReceipt(const basar::Decimal& val)
{
	m_Customer->m_SumGoodsReceipt = val;
	m_Customer->m_SumGoodsReceipt.setClean();
}


} // end namespace customer
} // end namespace libcsc

