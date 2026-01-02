#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMER_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMER_H

#include <libbasar_definitions.h>
#include <types/xmlinfolevelenum.inc>


namespace libcsc {
namespace customer {

class ICustomer
{
public:
	virtual ~ICustomer() {}

	virtual basar::Int16			getBranchNo() const = 0;
	virtual basar::Int32			getCustomerNo() const = 0;
	virtual basar::VarString const	getPharmacyName() const = 0;
	virtual basar::VarString const	getStreet() const = 0;
	virtual basar::VarString const	getPostalCode() const = 0;
	virtual basar::VarString const	getCity() const = 0;
	virtual basar::VarString const	getPharmacyOwner() const = 0;
	virtual basar::VarString const	getCustomerGroup() const = 0;
	virtual basar::Int32			getCustomerNoChain() const = 0;
	virtual bool					isActive() const = 0;
	virtual bool					hasTender() const = 0;
	virtual XMLInfoLevelEnum		getXMLInfoLevel() const = 0;
	virtual basar::VarString const	getMailAddress() const = 0;
	virtual basar::VarString const	getFaxNo() const = 0;
	virtual basar::VarString const	getLanguage() const = 0;
	virtual basar::Int16			getSalutationId() const = 0;
	virtual basar::Decimal			getLogisticSurchargePct() const = 0;
	virtual basar::Decimal			getLogisticSurchargeMinValue() const = 0;

	virtual basar::Int32			getPartnerNo() const = 0;
	virtual basar::Decimal			getLimit() const = 0;
	virtual basar::Decimal			getSumDebitSide() const = 0;
	virtual basar::Decimal			getSumCreditSide() const = 0;
	virtual basar::Decimal			getSumMonthTurnover() const = 0;
	virtual basar::Decimal			getSumDayTurnover() const = 0;
	virtual basar::Decimal			getSumReturns() const = 0;
	virtual basar::Decimal			getSumGoodsReceipt() const = 0;

};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMER_H
