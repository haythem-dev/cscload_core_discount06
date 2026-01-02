#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITION_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITION_H

#include <libbasar_definitions.h>


namespace libcsc {
namespace customer {

class ICustomerCondition
{
public:
	virtual ~ICustomerCondition() {}

	virtual basar::Int16			getBranchNo() const = 0;
	virtual basar::Int32			getCustomerNo() const = 0;
	virtual basar::Int32			getArticleNo() const = 0;
	virtual basar::Int32			getBaseQuantity() const = 0;
	virtual basar::Decimal			getPharmacyPurchasePrice() const = 0;
	virtual basar::Decimal			getDiscountPercentage() const = 0;
	virtual basar::Decimal			getDiscountPrice() const = 0;

	virtual basar::Int16			getPTPaymentDays1() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage1() const = 0;
	virtual basar::Decimal			getPTDiscountPrice1() const = 0;

	virtual basar::Int16			getPTPaymentDays2() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage2() const = 0;
	virtual basar::Decimal			getPTDiscountPrice2() const = 0;

	virtual basar::Int16			getPTPaymentDays3() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage3() const = 0;
	virtual basar::Decimal			getPTDiscountPrice3() const = 0;
	
	virtual basar::Int16			getPTPaymentDays4() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage4() const = 0;
	virtual basar::Decimal			getPTDiscountPrice4() const = 0;

	virtual basar::Int16			getPTPaymentDays5() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage5() const = 0;
	virtual basar::Decimal			getPTDiscountPrice5() const = 0;

	virtual basar::Int16			getPTPaymentDays6() const = 0;
	virtual basar::Decimal			getPTDiscountPercentage6() const = 0;
	virtual basar::Decimal			getPTDiscountPrice6() const = 0;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMERCONDITION_H
