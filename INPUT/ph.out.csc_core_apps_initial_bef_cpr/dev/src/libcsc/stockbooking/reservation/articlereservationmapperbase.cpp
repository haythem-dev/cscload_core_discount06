#include "articlereservationmapperbase.h"
#include "articlereservation.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace stockbooking {

ArticleReservationMapperBase::ArticleReservationMapperBase(ArticleReservationPtr articleReservation):
	m_ArticleReservation(articleReservation)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ArticleReservationMapperBase::ArticleReservationMapperBase()");
}

ArticleReservationMapperBase::~ArticleReservationMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ArticleReservationMapperBase::~ArticleReservationMapperBase()");
}

void ArticleReservationMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ArticleReservationMapperBase::map()");
	doMap();
}


void ArticleReservationMapperBase::setBranchNo( const basar::Int16& branchNo )
{
	m_ArticleReservation->m_BranchNo = branchNo;
	m_ArticleReservation->m_BranchNo.setClean();

}

void ArticleReservationMapperBase::setPharmacyGroupId(const basar::VarString& pharmacyGroupId )
{
	m_ArticleReservation->m_PharmacyGroupId = pharmacyGroupId;
	m_ArticleReservation->m_PharmacyGroupId.setClean();
}

void ArticleReservationMapperBase::setArticleNo(const basar::Int32& articleNo)
{
	m_ArticleReservation->m_ArticleNo = articleNo;
	m_ArticleReservation->m_ArticleNo.setClean();
}

void ArticleReservationMapperBase::setReservType( const basar::Int16& reservType )
{
	m_ArticleReservation->m_ReservType = reservType;
	m_ArticleReservation->m_ReservType.setClean();
}

void ArticleReservationMapperBase::setMaxQty(const basar::Int32& maxQty)
{
	m_ArticleReservation->m_MaxQty = maxQty;
	m_ArticleReservation->m_MaxQty.setClean();
}

void ArticleReservationMapperBase::setReservedQty(const basar::Int32& reservedQty)
{
	m_ArticleReservation->m_ReservedQty = reservedQty;
	m_ArticleReservation->m_ReservedQty.setClean();
}

void ArticleReservationMapperBase::setReservePct(const basar::Int16& reservepct)
{
	m_ArticleReservation->m_ReservePct = reservepct;
	m_ArticleReservation->m_ReservePct.setClean();
}


}
}