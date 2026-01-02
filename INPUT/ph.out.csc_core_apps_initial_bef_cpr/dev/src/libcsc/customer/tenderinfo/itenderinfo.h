#ifndef GUARD_LIBCSC_CUSTOMER_ITENDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_ITENDERINFO_H

#include <libbasar_definitions.h>


namespace libcsc {
namespace customer {

class ITenderInfo
{
public:
	virtual ~ITenderInfo() {}

	virtual basar::Int16			getBranchNo() const = 0;
	virtual basar::Int32			getCustomerNo() const = 0;
	virtual basar::Int32			getTenderNo() const = 0;
	virtual const basar::VarString&	getContractNo() const = 0;
	virtual const basar::Date&		getValidFromDate() const = 0;
	virtual const basar::Date&		getValidToDate() const = 0;
	virtual basar::Int32			getChainNo() const = 0;

	virtual basar::Int32			getArticleNo() const = 0;
	virtual basar::Int32			getTenderQuantity() const = 0;
	virtual basar::Int32			getFreeTenderQuantity() const = 0;
	virtual basar::Int32			getDeliveredTenderQuantity() const = 0;
	virtual basar::Int32			getReturnedTenderQuantity() const = 0;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ITENDERINFO_H
