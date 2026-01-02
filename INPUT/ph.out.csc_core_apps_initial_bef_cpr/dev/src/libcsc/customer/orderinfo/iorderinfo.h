#ifndef GUARD_LIBCSC_CUSTOMER_IORDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_IORDERINFO_H

#include <libbasar_definitions.h>


namespace libcsc {
namespace customer {

class IOrderInfo
{
public:
	virtual ~IOrderInfo() {}

	virtual basar::Int16			getBranchNo() const = 0;
	virtual basar::Int32			getCustomerNo() const = 0;
	virtual basar::Int32			getOrderNo() const = 0;
	virtual basar::Date				getOrderDate() const = 0;
	virtual basar::VarString		getOrderType() const = 0;

	virtual basar::Int32			getArticleNo() const = 0;
	virtual basar::Int32			getQuantityOrdered() const = 0;
	virtual basar::Int32			getQuantityConfirmed() const = 0;
	virtual basar::VarString		getReferenceNo() const = 0;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IORDERINFO_H
