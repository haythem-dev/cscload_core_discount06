#include "ordertypereservationconfigpharmacygroupmapperbase.h"
#include "ordertypereservationconfigpharmacygroup.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace stockbooking {


OrderTypeReservationConfigPharmacyGroupMapperBase::OrderTypeReservationConfigPharmacyGroupMapperBase(OrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup):
	m_OrderTypeReservationConfigPharmacyGroup(orderTypeReservationConfigPharmacyGroup)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigPharmacyGroupMapperBase::OrderTypeReservationConfigPharmacyGroupMapperBase()");
}

OrderTypeReservationConfigPharmacyGroupMapperBase::~OrderTypeReservationConfigPharmacyGroupMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigPharmacyGroupMapperBase::~OrderTypeReservationConfigPharmacyGroupMapperBase()");
}

void OrderTypeReservationConfigPharmacyGroupMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigPharmacyGroupMapperBase::map()");
	doMap();
}

void OrderTypeReservationConfigPharmacyGroupMapperBase::setId( const basar::Int32& id )
{
	m_OrderTypeReservationConfigPharmacyGroup->m_Id = id;
	m_OrderTypeReservationConfigPharmacyGroup->m_Id.setClean();
}

void OrderTypeReservationConfigPharmacyGroupMapperBase::setPharmcyGroupId( const basar::VarString& pharmacyGroupId )
{
	m_OrderTypeReservationConfigPharmacyGroup->m_PharmacyGroupId = pharmacyGroupId;
	m_OrderTypeReservationConfigPharmacyGroup->m_PharmacyGroupId.setClean();
}

void OrderTypeReservationConfigPharmacyGroupMapperBase::setOrderTypeReservationConfigId(const basar::Int32 OrderTypeReservationConfigId )
{
	m_OrderTypeReservationConfigPharmacyGroup->m_OrderTypeReservationConfigId = OrderTypeReservationConfigId;
	m_OrderTypeReservationConfigPharmacyGroup->m_OrderTypeReservationConfigId.setClean();
}


}
}