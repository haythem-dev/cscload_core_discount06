#include "reservationtypemapperbase.h"
#include "reservationtype.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace stockbooking {


ReservationTypeMapperBase::ReservationTypeMapperBase(ReservationTypePtr reservationType) :
	m_ReservationType(reservationType)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "ReservationTypeMapperBase::ReservationTypeMapperBase()");
}

ReservationTypeMapperBase::~ReservationTypeMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "ReservationTypeMapperBase::~ReservationTypeMapperBase()");
}

void ReservationTypeMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "ReservationTypeMapperBase::map()");
	doMap();
}

void ReservationTypeMapperBase::setId( const basar::Int32& id )
{
	m_ReservationType->m_Id = id;
	m_ReservationType->m_Id.setClean();
}

void ReservationTypeMapperBase::setReservationType( const basar::Int32& reservationType )
{
	m_ReservationType->m_ReservationType = reservationType;
	m_ReservationType->m_ReservationType.setClean();
}

void ReservationTypeMapperBase::setWithPharmacyGroup(const basar::Int16& withPharmacyGroup)
{
	m_ReservationType->m_WithPharmacyGroup = libcsc::Bool(withPharmacyGroup != 0);
    m_ReservationType->m_WithPharmacyGroup.setClean();
}

void ReservationTypeMapperBase::setReservationName( const basar::VarString& reservationName)
{
	basar::VarString tmp = reservationName;
	tmp.trim();
	m_ReservationType->m_ReservationName = tmp;
	m_ReservationType->m_ReservationName.setClean();
}

}
}