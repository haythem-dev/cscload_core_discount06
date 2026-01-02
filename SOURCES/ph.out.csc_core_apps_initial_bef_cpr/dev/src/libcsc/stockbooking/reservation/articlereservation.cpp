#include "articlereservation.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

ArticleReservation::ArticleReservation()
{
}

ArticleReservation::~ArticleReservation()
{
}

const basar::Int16& ArticleReservation::getBranchNo() const
{
	return m_BranchNo;
}

const basar::VarString& ArticleReservation::getPharmacyGroupId() const
{
	return m_PharmacyGroupId;
}

const basar::Int32& ArticleReservation::getArticleNo() const
{
	return m_ArticleNo;
}

const basar::Int16& ArticleReservation::getReservType() const
{
	return m_ReservType;
}

const basar::Int32& ArticleReservation::getMaxQty() const
{
	return m_MaxQty;
}

const basar::Int32& ArticleReservation::getReservedQty() const
{
	return m_ReservedQty;
}

const basar::Int16& ArticleReservation::getReservePct() const
{
	return m_ReservePct;
}

void ArticleReservation::setBranchNo(const basar::Int16& branchNo)
{
	m_BranchNo = branchNo;
}

void ArticleReservation::setPharmacyGroupId(const basar::VarString& pharmacyGroupId)
{
	m_PharmacyGroupId = pharmacyGroupId;
}

void ArticleReservation::setArticleNo(const basar::Int32& articleNo)
{
	m_ArticleNo = articleNo;
}

void ArticleReservation::setReservType(const basar::Int16& reservType)
{
	m_ReservType = reservType;
}

void ArticleReservation::setMaxQty(const basar::Int32& maxQty)
{
	m_MaxQty = maxQty;
}

void ArticleReservation::setReservedQty(const basar::Int32& reservedQty)
{
	m_ReservedQty = reservedQty;
}

void ArticleReservation::setReservePct(const basar::Int16& reservePct)
{
	m_ReservePct = reservePct;
}

bool ArticleReservation::isInsertable() const
{
	return	m_BranchNo.isDirty() &&
		m_PharmacyGroupId.isDirty() &&
		m_ArticleNo.isDirty() &&
		m_ReservType.isDirty() && 
		m_MaxQty.isDirty() && 
		m_ReservedQty.isDirty() && 
		m_ReservePct.isDirty() ;
}

bool ArticleReservation::isUpdatable() const
{
	return m_MaxQty.isDirty() && 
		m_ReservedQty.isDirty() && 
		m_ReservePct.isDirty() ;
}


bool ArticleReservation::isClean() const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ArticleReservation::isClean()");
	return m_MaxQty.isClean() && 
		m_ReservedQty.isClean() && 
		m_ReservePct.isClean() ;
}

bool ArticleReservation::isDirty() const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ArticleReservation::isDirty()");
	return m_BranchNo.isDirty() &&
		m_PharmacyGroupId.isDirty() &&
		m_ArticleNo.isDirty() &&
		m_ReservType.isDirty() && 
		m_MaxQty.isDirty() && 
		m_ReservedQty.isDirty() && 
		m_ReservePct.isDirty() ;
}


}
}