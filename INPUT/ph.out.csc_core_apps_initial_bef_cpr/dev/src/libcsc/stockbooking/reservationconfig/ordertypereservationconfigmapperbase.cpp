#include "ordertypereservationconfigmapperbase.h"
#include "ordertypereservationconfig.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace stockbooking {


OrderTypeReservationConfigMapperBase::OrderTypeReservationConfigMapperBase(OrderTypeReservationConfigPtr orderTypeReservationConfig) :
	m_OrderTypeReservationConfig(orderTypeReservationConfig)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigMapperBase::OrderTypeReservationConfigMapperBase()");
}

OrderTypeReservationConfigMapperBase::~OrderTypeReservationConfigMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigMapperBase::~OrderTypeReservationConfigMapperBase()");
}

void OrderTypeReservationConfigMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "OrderTypeReservationConfigMapperBase::map()");
	doMap();
}

void OrderTypeReservationConfigMapperBase::setId( const basar::Int32& id )
{
	m_OrderTypeReservationConfig->m_Id = id;
	m_OrderTypeReservationConfig->m_Id.setClean();
}

void OrderTypeReservationConfigMapperBase::setReservationType( const basar::Int32 reservationType )
{
	m_OrderTypeReservationConfig->m_ReservationType = reservationType;
	m_OrderTypeReservationConfig->m_ReservationType.setClean();
}

void OrderTypeReservationConfigMapperBase::setWithPharmacyGroup(const basar::Int16 withPharmacyGroup)
{
	m_OrderTypeReservationConfig->m_WithPharmacyGroup = libcsc::Bool(withPharmacyGroup != 0);
	m_OrderTypeReservationConfig->m_WithPharmacyGroup.setClean();
}

void OrderTypeReservationConfigMapperBase::setReservationName( const basar::VarString& reservationName )
{
	basar::VarString tmp = reservationName;
	tmp.trim();
	m_OrderTypeReservationConfig->m_ReservationName = tmp;
	m_OrderTypeReservationConfig->m_ReservationName.setClean();
}

void OrderTypeReservationConfigMapperBase::setOrderType(const basar::VarString& orderType)
{
	basar::VarString tmp = orderType;
	tmp.trim();
	m_OrderTypeReservationConfig->m_OrderType = tmp;
	m_OrderTypeReservationConfig->m_OrderType.setClean();
}

void OrderTypeReservationConfigMapperBase::setOrderTypeReservationConfigName(const basar::VarString& orderTypeReservationConfigName)
{
	basar::VarString tmp = orderTypeReservationConfigName;
	tmp.trim();
	m_OrderTypeReservationConfig->m_OrderTypeReservationConfigName = tmp;
	m_OrderTypeReservationConfig->m_OrderTypeReservationConfigName.setClean();
}

void OrderTypeReservationConfigMapperBase::setPriority(const basar::Int16 priority)
{
	m_OrderTypeReservationConfig->m_Priority = priority;
	m_OrderTypeReservationConfig->m_Priority.setClean();
}

void OrderTypeReservationConfigMapperBase::setReservedStockOnly(const basar::Int16 reservedStockOnly)
{
	m_OrderTypeReservationConfig->m_ReservedStockOnly = libcsc::Bool(reservedStockOnly != 0);
	m_OrderTypeReservationConfig->m_ReservedStockOnly.setClean();
}

void OrderTypeReservationConfigMapperBase::setFreeStockHasPriority(const basar::Int16 freeStockHasPriority)
{
	m_OrderTypeReservationConfig->m_FreeStockHasPriority = libcsc::Bool(freeStockHasPriority != 0);
	m_OrderTypeReservationConfig->m_FreeStockHasPriority.setClean();
}

}
}