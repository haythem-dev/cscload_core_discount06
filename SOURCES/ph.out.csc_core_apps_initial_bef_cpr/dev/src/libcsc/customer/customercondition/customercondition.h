#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITION_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITION_H

#include <customer/customercondition/icustomercondition.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/decimal.h>

namespace libcsc {
namespace customer {

class CustomerCondition : public ICustomerCondition
{
    // because of OR mapping
    friend class CustomerConditionMapperBase;

public:
	CustomerCondition();
    virtual ~CustomerCondition();

	virtual basar::Int16			getBranchNo() const;
	virtual basar::Int32			getCustomerNo() const;
	virtual basar::Int32			getArticleNo() const;
	virtual basar::Int32			getBaseQuantity() const;
	virtual basar::Decimal			getPharmacyPurchasePrice() const;
	virtual basar::Decimal			getDiscountPercentage() const;
	virtual basar::Decimal			getDiscountPrice() const;

	virtual basar::Int16			getPTPaymentDays1() const;
	virtual basar::Decimal			getPTDiscountPercentage1() const;
	virtual basar::Decimal			getPTDiscountPrice1() const;

	virtual basar::Int16			getPTPaymentDays2() const;
	virtual basar::Decimal			getPTDiscountPercentage2() const;
	virtual basar::Decimal			getPTDiscountPrice2() const;

	virtual basar::Int16			getPTPaymentDays3() const;
	virtual basar::Decimal			getPTDiscountPercentage3() const;
	virtual basar::Decimal			getPTDiscountPrice3() const;

	virtual basar::Int16			getPTPaymentDays4() const;
	virtual basar::Decimal			getPTDiscountPercentage4() const;
	virtual basar::Decimal			getPTDiscountPrice4() const;

	virtual basar::Int16			getPTPaymentDays5() const;
	virtual basar::Decimal			getPTDiscountPercentage5() const;
	virtual basar::Decimal			getPTDiscountPrice5() const;

	virtual basar::Int16			getPTPaymentDays6() const;
	virtual basar::Decimal			getPTDiscountPercentage6() const;
	virtual basar::Decimal			getPTDiscountPrice6() const;

private:
    libcsc::Int16		m_BranchNo;
	libcsc::Int32		m_CustomerNo;
	libcsc::Int32		m_ArticleNo;
	libcsc::Int32		m_BaseQuantity;

	libcsc::Decimal		m_PharmacyPurchasePrice;
	libcsc::Decimal		m_DiscountPercentage;
	libcsc::Decimal		m_DiscountPrice;

	libcsc::Int16			m_PTPaymentDays1;
	libcsc::Decimal			m_PTDiscountPercentage1;
	libcsc::Decimal			m_PTDiscountPrice1;

	libcsc::Int16			m_PTPaymentDays2;
	libcsc::Decimal			m_PTDiscountPercentage2;
	libcsc::Decimal			m_PTDiscountPrice2;

	libcsc::Int16			m_PTPaymentDays3;
	libcsc::Decimal			m_PTDiscountPercentage3;
	libcsc::Decimal			m_PTDiscountPrice3;

	libcsc::Int16			m_PTPaymentDays4;
	libcsc::Decimal			m_PTDiscountPercentage4;
	libcsc::Decimal			m_PTDiscountPrice4;

	libcsc::Int16			m_PTPaymentDays5;
	libcsc::Decimal			m_PTDiscountPercentage5;
	libcsc::Decimal			m_PTDiscountPrice5;

	libcsc::Int16			m_PTPaymentDays6;
	libcsc::Decimal			m_PTDiscountPercentage6;
	libcsc::Decimal			m_PTDiscountPrice6;

};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERCONDITION_H
