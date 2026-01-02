#include "customerstockreserved.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

CustomerStockReserved::CustomerStockReserved()
{
}

CustomerStockReserved::~CustomerStockReserved()
{
}

const basar::Int16& CustomerStockReserved::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32& CustomerStockReserved::getCustomerNo() const
{
	return m_CustomerNo;
}

const basar::Int32& CustomerStockReserved::getArticleNo() const
{
	return m_ArticleNo;
}

const basar::Int32& CustomerStockReserved::getReservedQty() const
{
	return m_ReservedQty;
}

const basar::Int32& CustomerStockReserved::getDateFrom() const
{
	return m_DateFrom;
}

const basar::Int32& CustomerStockReserved::getTimeFrom() const
{
	return m_TimeFrom;
}

const basar::Int32& CustomerStockReserved::getDateTo() const
{
	return m_DateTo;
}

const basar::Int32& CustomerStockReserved::getTimeTo() const
{
	return m_TimeTo;
}

const basar::Int32& CustomerStockReserved::getKdAuftragNr() const
{
	return m_KdAuftragNr;
}

const basar::Int16& CustomerStockReserved::getReservType() const
{
	return m_ReservType;
}

void CustomerStockReserved::setBranchNo(const basar::Int16& branchno)
{
	m_BranchNo = branchno;
}

void CustomerStockReserved::setCustomerNo(const basar::Int32& customerNo)
{
	m_CustomerNo = customerNo;
}

void CustomerStockReserved::setArticleNo(const basar::Int32& articleNo)
{
	m_ArticleNo = articleNo;
}

void CustomerStockReserved::setReservedQty(const basar::Int32& reservedQty)
{
	m_ReservedQty = reservedQty;
}

void CustomerStockReserved::setDateFrom(const basar::Int32& dateFrom)
{
	m_DateFrom = dateFrom;
}

void CustomerStockReserved::setTimeFrom(const basar::Int32& timeFrom)
{
	m_TimeFrom = timeFrom;
}

void CustomerStockReserved::setDateTo(const basar::Int32& dateTo)
{
	m_DateTo = dateTo;
}

void CustomerStockReserved::setTimeTo(const basar::Int32& timeTo)
{
	m_TimeTo = timeTo;
}

void CustomerStockReserved::setKdAuftragNr(const basar::Int32& kdAuftragNr)
{
	m_KdAuftragNr = kdAuftragNr;
}

void CustomerStockReserved::setReservType(const basar::Int16& reservType)
{
	m_ReservType = reservType;
}



bool CustomerStockReserved::isInsertable() const
{
	return m_BranchNo.isDirty() &&
			m_CustomerNo.isDirty() &&
			m_ArticleNo.isDirty() &&
			m_ReservedQty.isDirty() &&
			m_DateFrom.isDirty() &&
			m_TimeFrom.isDirty() &&
			m_DateTo.isDirty() &&
			m_TimeTo.isDirty() &&
			m_KdAuftragNr.isDirty() &&
			m_ReservType.isDirty();
}

bool CustomerStockReserved::isUpdatable() const
{
	return m_ReservedQty.isDirty() && 
	m_DateTo.isDirty() && 
	m_TimeTo.isDirty() ;

}

bool CustomerStockReserved::isClean() const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "CustomerStockReserved::isClean()");

	return m_ReservedQty.isClean() && 
		m_DateTo.isClean() && 
		m_TimeTo.isClean() ;

}

bool CustomerStockReserved::isDirty() const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "CustomerStockReserved::isClean()");
	return m_BranchNo.isDirty() &&
			m_CustomerNo.isDirty() &&
			m_ArticleNo.isDirty() &&
			m_ReservedQty.isDirty() &&
			m_DateFrom.isDirty() &&
			m_TimeFrom.isDirty() &&
			m_DateTo.isDirty() &&
			m_TimeTo.isDirty() &&
			m_KdAuftragNr.isDirty() &&
			m_ReservType.isDirty();

}


}
}