#include <customer/orderinfo/orderinfo.h>

namespace libcsc {
namespace customer {

OrderInfo::OrderInfo()
{
}

OrderInfo::~OrderInfo()
{
}

basar::Int16 OrderInfo::getBranchNo() const
{
	return m_BranchNo;
}

basar::Int32 OrderInfo::getCustomerNo() const
{
	return m_CustomerNo;
}

basar::Int32 OrderInfo::getOrderNo() const
{
	return m_OrderNo;
}

basar::Date OrderInfo::getOrderDate() const
{
	return m_OrderDate;
}

basar::VarString OrderInfo::getOrderType() const
{
	return m_OrderType;
}


basar::Int32 OrderInfo::getArticleNo() const
{
	return m_ArticleNo;
}

basar::Int32 OrderInfo::getQuantityOrdered() const
{
	return m_QuantityOrdered;
}

basar::Int32 OrderInfo::getQuantityConfirmed() const
{
	return m_QuantityConfirmed;
}

basar::VarString OrderInfo::getReferenceNo() const
{
	return m_ReferenceNo;
}


} // end namespace customer
} // end namespace libcsc

