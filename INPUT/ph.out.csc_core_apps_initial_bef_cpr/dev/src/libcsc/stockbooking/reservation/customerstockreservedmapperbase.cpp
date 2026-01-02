#include "customerstockreservedmapperbase.h"
#include "customerstockreserved.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace stockbooking {

CustomerStockReservedMapperBase::CustomerStockReservedMapperBase(CustomerStockReservedPtr customerStockReserved):
	m_CustomerStockReserved(customerStockReserved)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "CustomerStockReservedMapperBase::CustomerStockReservedMapperBase()");
}

CustomerStockReservedMapperBase::~CustomerStockReservedMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "CustomerStockReservedMapperBase::~CustomerStockReservedMapperBase()");
}

void CustomerStockReservedMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "CustomerStockReservedMapperBase::map()");
	doMap();
}

void CustomerStockReservedMapperBase::setBranchNo( const basar::Int16& branchNo )
{
	m_CustomerStockReserved->m_BranchNo = branchNo;
	m_CustomerStockReserved->m_BranchNo.setClean();
}

void CustomerStockReservedMapperBase::setCustomerNo(const basar::Int32& customerNo)
{
	m_CustomerStockReserved->m_CustomerNo = customerNo;
	m_CustomerStockReserved->m_CustomerNo.setClean();
}

void CustomerStockReservedMapperBase::setArticleNo(const basar::Int32& articleNo )
{
	m_CustomerStockReserved->m_ArticleNo = articleNo;
	m_CustomerStockReserved->m_ArticleNo.setClean();

}

void CustomerStockReservedMapperBase::setReservedQty(const basar::Int32& reservedQty )
{
	m_CustomerStockReserved->m_ReservedQty= reservedQty;
	m_CustomerStockReserved->m_ReservedQty.setClean();
}

void CustomerStockReservedMapperBase::setDateFrom(const basar::Int32& dateFrom )
{
	m_CustomerStockReserved->m_DateFrom = dateFrom;
	m_CustomerStockReserved->m_DateFrom.setClean();

}

void CustomerStockReservedMapperBase::setTimeFrom(const basar::Int32& timeFrom )
{
	m_CustomerStockReserved->m_TimeFrom = timeFrom;
	m_CustomerStockReserved->m_TimeFrom.setClean();

}

void CustomerStockReservedMapperBase::setDateTo(const basar::Int32& dateTo )
{
	m_CustomerStockReserved->m_DateTo = dateTo;
	m_CustomerStockReserved->m_DateTo.setClean();

}

void CustomerStockReservedMapperBase::setTimeTo(const basar::Int32& timeTo )
{
	m_CustomerStockReserved->m_TimeTo = timeTo;
	m_CustomerStockReserved->m_TimeTo.setClean();

}


void CustomerStockReservedMapperBase::setKdAuftragNr(const basar::Int32& kdAuftragNr)
{
	m_CustomerStockReserved->m_KdAuftragNr = kdAuftragNr;
	m_CustomerStockReserved->m_KdAuftragNr.setClean();

}

void CustomerStockReservedMapperBase::setReservType(const basar::Int16& reservType)
{
	m_CustomerStockReserved->m_ReservType = reservType;
	m_CustomerStockReserved->m_ReservType.setClean();
}

}
}