#include "ordertypereservationconfigpharmacygroup.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

OrderTypeReservationConfigPharmacyGroup::OrderTypeReservationConfigPharmacyGroup()
{
	m_DeletionFlag = false;
}

OrderTypeReservationConfigPharmacyGroup::~OrderTypeReservationConfigPharmacyGroup()
{
}

const basar::Int32& OrderTypeReservationConfigPharmacyGroup::getId() const
{
	return m_Id;
}

const basar::Int32& OrderTypeReservationConfigPharmacyGroup::getOrderTypeReservationConfigId() const
{
	return m_OrderTypeReservationConfigId;
}

const basar::VarString& OrderTypeReservationConfigPharmacyGroup::getPharmacyGroupId() const
{
	return m_PharmacyGroupId;
}


void OrderTypeReservationConfigPharmacyGroup::setId(const basar::Int32& id)
{
	m_Id = id;
}

void OrderTypeReservationConfigPharmacyGroup::setPharmacyGroupId(const basar::VarString& pharmacyGroupId)
{
	m_PharmacyGroupId = pharmacyGroupId;
}

void OrderTypeReservationConfigPharmacyGroup::setOrderTypeReservationConfigId(const basar::Int32& reservationId)
{
	m_OrderTypeReservationConfigId = reservationId;
}

void OrderTypeReservationConfigPharmacyGroup::markForDeletion()
{
	m_DeletionFlag = true;
}
bool OrderTypeReservationConfigPharmacyGroup::isMarkedForDeletion()
{
	return m_DeletionFlag;
}

bool OrderTypeReservationConfigPharmacyGroup::isInsertable() const
{
	return	m_Id.isUnset() &&

		m_PharmacyGroupId.isDirty() &&
		m_OrderTypeReservationConfigId.isDirty();
}

bool OrderTypeReservationConfigPharmacyGroup::isUpdatable() const
{
	return m_Id.isClean() &&
		(
			m_PharmacyGroupId.isDirty() &&
			m_OrderTypeReservationConfigId.isDirty()
		);
}


bool OrderTypeReservationConfigPharmacyGroup::isClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "OrderTypeReservationConfigPharmacyGroup::isClean()");
	return m_PharmacyGroupId.isClean() &&
			m_OrderTypeReservationConfigId.isClean();
}

bool OrderTypeReservationConfigPharmacyGroup::isDirty()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "OrderTypeReservationConfigPharmacyGroup::isDirty()");
	return m_PharmacyGroupId.isDirty() &&
		m_OrderTypeReservationConfigId.isDirty();
}

std::ostream& operator << (std::ostream& str, const libcsc::stockbooking::OrderTypeReservationConfigPharmacyGroup& data)
{
	str << "OrderTypeReservationConfigPharmacyGroup ID = " << data.getId() << " PharmacyGroupId = " << data.getPharmacyGroupId()
		<< " configID = " << data.getOrderTypeReservationConfigId() << std::endl;
	return str;
}


} // namespace stockbooking
} // namespace libcsc
