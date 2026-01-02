#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMER_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMER_H

#include <customer/icustomer.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/boolean.h>
#include <datatypes/decimal.h>

namespace libcsc {
namespace customer {

class Customer : public ICustomer
{
    // because of OR mapping
    friend class CustomerMapperBase;
//	friend class CSCOrderTypeRepository;

public:
	Customer();
    virtual ~Customer();

	virtual basar::Int16			getBranchNo() const;
	virtual basar::Int32			getCustomerNo() const;
	virtual basar::VarString const	getPharmacyName() const;
	virtual basar::VarString const	getStreet() const;
	virtual basar::VarString const	getPostalCode() const;
	virtual basar::VarString const	getCity() const;
	virtual basar::VarString const	getPharmacyOwner() const;
	virtual basar::VarString const	getCustomerGroup() const;
	virtual basar::Int32			getCustomerNoChain() const;
	virtual bool					isActive() const;
	virtual bool					hasTender() const;
	virtual XMLInfoLevelEnum		getXMLInfoLevel() const;
	virtual basar::VarString const	getMailAddress() const;
	virtual basar::VarString const	getFaxNo() const;
	virtual basar::VarString const	getLanguage() const;
	virtual basar::Int16			getSalutationId() const;
	virtual basar::Decimal			getLogisticSurchargePct() const;
	virtual basar::Decimal			getLogisticSurchargeMinValue() const;

	virtual basar::Int32			getPartnerNo() const;
	virtual basar::Decimal			getLimit() const;
	virtual basar::Decimal			getSumDebitSide() const;
	virtual basar::Decimal			getSumCreditSide() const;
	virtual basar::Decimal			getSumMonthTurnover() const;
	virtual basar::Decimal			getSumDayTurnover() const;
	virtual basar::Decimal			getSumReturns() const;
	virtual basar::Decimal			getSumGoodsReceipt() const;

private:
    libcsc::Int16		m_BranchNo;
	libcsc::Int32		m_CustomerNo;
	libcsc::VarString	m_PharmacyName;
	libcsc::VarString	m_Street;
	libcsc::VarString	m_PostalCode;
	libcsc::VarString	m_City;
	libcsc::VarString	m_PharmacyOwner;
	libcsc::VarString	m_CustomerGroup;
	libcsc::Int32		m_CustomerNoChain;
	libcsc::Bool		m_IsActive;
	XMLInfoLevelEnum	m_XMLInfoLevel;
	libcsc::Bool		m_HasTender;
	libcsc::VarString	m_MailAddress;
	libcsc::VarString	m_FaxNo;
	libcsc::VarString	m_Language;
	libcsc::Int16		m_SalutationId;
	libcsc::Decimal		m_LogisticSurchargePct;
	libcsc::Decimal		m_LogisticSurchargeMinValue;

	libcsc::Int32		m_PartnerNo;
	libcsc::Decimal		m_Limit;
	libcsc::Decimal		m_SumDebitSide;
	libcsc::Decimal		m_SumCreditSide;
	libcsc::Decimal		m_SumMonthTurnover;
	libcsc::Decimal		m_SumDayTurnover;
	libcsc::Decimal		m_SumReturns;
	libcsc::Decimal		m_SumGoodsReceipt;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMER_H
