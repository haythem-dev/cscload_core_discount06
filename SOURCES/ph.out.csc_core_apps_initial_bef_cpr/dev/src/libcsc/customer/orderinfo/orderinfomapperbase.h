#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFOMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFOMAPPERBASE_H

#include <customer/orderinfo/orderinfoptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class OrderInfoMapperBase
{
public:
	OrderInfoMapperBase(OrderInfoPtr orderInfo);

	void map();

protected:
	virtual ~OrderInfoMapperBase();
    
	virtual void doMap() = 0;
    
	void setBranchNo(const basar::Int16 branchNo);
	void setCustomerNo(const basar::Int32 customerNo);
	void setOrderNo(const basar::Int32 orderNo);
	void setOrderDate(const basar::Date& orderDate);
	void setOrderType(const basar::VarString& orderType);

	void setArticleNo(const basar::Int32 articleNo);
	void setQuantityOrdered(const basar::Int32 quantityOrdered);
	void setQuantityConfirmed(const basar::Int32 quantityConfirmed);
	void setReferenceNo(const basar::VarString& referenceNo);

private:
	OrderInfoPtr   m_OrderInfo;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFOMAPPERBASE_H
