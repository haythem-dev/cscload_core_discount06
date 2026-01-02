#include <customer/orderinfo/orderinfomapperbase.h>
#include <customer/orderinfo/orderinfo.h>

namespace libcsc {
namespace customer {

OrderInfoMapperBase::OrderInfoMapperBase(OrderInfoPtr orderInfo)
: m_OrderInfo(orderInfo)
{
}

OrderInfoMapperBase::~OrderInfoMapperBase()
{
}

void OrderInfoMapperBase::map()
{
    doMap();
}

void OrderInfoMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_OrderInfo->m_BranchNo = branchNo;
	m_OrderInfo->m_BranchNo.setClean();
}

void OrderInfoMapperBase::setCustomerNo(const basar::Int32 customerNo)
{
	m_OrderInfo->m_CustomerNo = customerNo;
	m_OrderInfo->m_CustomerNo.setClean();
}

void OrderInfoMapperBase::setOrderNo(const basar::Int32 orderNo)
{
	m_OrderInfo->m_OrderNo = orderNo;
	m_OrderInfo->m_OrderNo.setClean();
}

void OrderInfoMapperBase::setOrderDate(const basar::Date& orderDate)
{
	m_OrderInfo->m_OrderDate = orderDate;
	m_OrderInfo->m_OrderDate.setClean();
}

void OrderInfoMapperBase::setOrderType(const basar::VarString& orderType)
{
	m_OrderInfo->m_OrderType = orderType;
	m_OrderInfo->m_OrderType.setClean();
}



void OrderInfoMapperBase::setArticleNo(const basar::Int32 articleNo)
{
	m_OrderInfo->m_ArticleNo = articleNo;
	m_OrderInfo->m_ArticleNo.setClean();
}

void OrderInfoMapperBase::setQuantityOrdered(const basar::Int32 quantityOrdered)
{
	m_OrderInfo->m_QuantityOrdered = quantityOrdered;
	m_OrderInfo->m_QuantityOrdered.setClean();
}

void OrderInfoMapperBase::setQuantityConfirmed(const basar::Int32 quantityConfirmed)
{
	m_OrderInfo->m_QuantityConfirmed = quantityConfirmed;
	m_OrderInfo->m_QuantityConfirmed.setClean();
}

void OrderInfoMapperBase::setReferenceNo(const basar::VarString& referenceNo)
{
	m_OrderInfo->m_ReferenceNo = referenceNo;
	m_OrderInfo->m_ReferenceNo.setClean();
}


} // end namespace customer
} // end namespace libcsc

