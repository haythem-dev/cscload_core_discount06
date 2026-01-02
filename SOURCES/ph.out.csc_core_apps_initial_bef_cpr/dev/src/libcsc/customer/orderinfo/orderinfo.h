#ifndef GUARD_LIBCSC_CUSTOMER_ORDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_ORDERINFO_H

#include <customer/orderinfo/iorderinfo.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/date.h>

namespace libcsc {
namespace customer {

class OrderInfo : public IOrderInfo
{
    // because of OR mapping
    friend class OrderInfoMapperBase;

public:
	OrderInfo();
    virtual ~OrderInfo();

	virtual basar::Int16			getBranchNo() const;
	virtual basar::Int32			getCustomerNo() const;
	virtual basar::Int32			getOrderNo() const;
	virtual basar::Date				getOrderDate() const;
	virtual basar::VarString		getOrderType() const;

	virtual basar::Int32			getArticleNo() const;
	virtual basar::Int32			getQuantityOrdered() const;
	virtual basar::Int32			getQuantityConfirmed() const;
	virtual basar::VarString		getReferenceNo() const;

private:
    libcsc::Int16		m_BranchNo;
	libcsc::Int32		m_CustomerNo;
	libcsc::Int32		m_OrderNo;
	libcsc::Date		m_OrderDate;
	libcsc::VarString	m_OrderType;

	libcsc::Int32		m_ArticleNo;
	libcsc::Int32		m_QuantityOrdered;
	libcsc::Int32		m_QuantityConfirmed;
	libcsc::VarString	m_ReferenceNo;

};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERINFO_H
