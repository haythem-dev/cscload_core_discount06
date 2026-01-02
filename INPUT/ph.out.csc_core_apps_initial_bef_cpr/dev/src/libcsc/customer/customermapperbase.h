#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERMAPPERBASE_H

#include <customer/customerptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class CustomerMapperBase
{
public:
	CustomerMapperBase(CustomerPtr customer);

	void map(bool withTender, bool withCreditLimit, bool withLogisticSurcharge, int countryPhoneCode);

protected:
	virtual ~CustomerMapperBase();
    
	virtual void doMap(int countryPhoneCode) = 0;
	virtual void doMapTender() = 0;
	virtual void doMapCreditLimit() = 0;
	virtual void doMapLogisticSurcharge() = 0;
    
	void setBranchNo(const basar::Int16 branchNo);
	void setCustomerNo(const basar::Int32 customerNo);
	void setPharmacyName(const basar::VarString& pharmacyName);
	void setStreet(const basar::VarString& street);
	void setPostalCode(const basar::VarString& postalCode);
	void setCity(const basar::VarString& city);
	void setPharmacyOwner(const basar::VarString& pharmacyOwner);
	void setCustomerGroup(const basar::VarString& customerGroup);
	void setCustomerNoChain(const basar::Int32 customerNoChain);
	void setIsActive(const bool isActive);
	void setHasTender(const bool hasTender);
	void setXmlInfoLevel(const basar::Int32 xmlinfolevel);
	void setMailAddress(const basar::VarString& mailAddress);
	void setFaxNo(const basar::VarString& faxNo);
	void setLanguage(const basar::VarString& language);
	void setSalutationId(const basar::Int16 salutationId);
	void setLogisticSurchargePct(const basar::Decimal& val);
	void setLogisticSurchargeMinValue(const basar::Decimal& val);

	void setPartnerNo(const basar::Int32 val);
	void setLimit(const basar::Decimal& val);
	void setSumDebitSide(const basar::Decimal& val);
	void setSumCreditSide(const basar::Decimal& val);
	void setSumMonthTurnover(const basar::Decimal& val);
	void setSumDayTurnover(const basar::Decimal& val);
	void setSumReturns(const basar::Decimal& val);
	void setSumGoodsReceipt(const basar::Decimal& val);

private:
	CustomerPtr   m_Customer;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERMAPPERBASE_H
