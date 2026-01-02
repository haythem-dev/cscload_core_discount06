#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONMAPPERBASE_H

#include <customer/customercondition/customerconditionptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class CustomerConditionMapperBase
{
public:
	CustomerConditionMapperBase(CustomerConditionPtr cuco);

	void map();

protected:
	virtual ~CustomerConditionMapperBase();
    
	virtual void doMap() = 0;
    
	void setBranchNo(const basar::Int16 branchNo);
	void setCustomerNo(const basar::Int32 customerNo);
	void setArticleNo(const basar::Int32 articleNo);
	void setBaseQuantity(const basar::Int32 baseQuantity);
	void setPharmacyPurchasePrice(const basar::Decimal& pharmacyPurchasePrice);
	void setDiscountPercentage(const basar::Decimal& discountPercentage);
	void setDiscountPrice(const basar::Decimal& discountPrice);

	void setPTPaymentDays1(const basar::Int16 paymentDays);
	void setPTDiscountPercentage1(const basar::Decimal& dicountPct);
	void setPTDiscountPrice1(const basar::Decimal& discountPrice);

	void setPTPaymentDays2(const basar::Int16 paymentDays);
	void setPTDiscountPercentage2(const basar::Decimal& dicountPct);
	void setPTDiscountPrice2(const basar::Decimal& discountPrice);

	void setPTPaymentDays3(const basar::Int16 paymentDays);
	void setPTDiscountPercentage3(const basar::Decimal& dicountPct);
	void setPTDiscountPrice3(const basar::Decimal& discountPrice);

	void setPTPaymentDays4(const basar::Int16 paymentDays);
	void setPTDiscountPercentage4(const basar::Decimal& dicountPct);
	void setPTDiscountPrice4(const basar::Decimal& discountPrice);

	void setPTPaymentDays5(const basar::Int16 paymentDays);
	void setPTDiscountPercentage5(const basar::Decimal& dicountPct);
	void setPTDiscountPrice5(const basar::Decimal& discountPrice);

	void setPTPaymentDays6(const basar::Int16 paymentDays);
	void setPTDiscountPercentage6(const basar::Decimal& dicountPct);
	void setPTDiscountPrice6(const basar::Decimal& discountPrice);

private:
	CustomerConditionPtr   m_CustomerCondition;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITIONMAPPERBASE_H
