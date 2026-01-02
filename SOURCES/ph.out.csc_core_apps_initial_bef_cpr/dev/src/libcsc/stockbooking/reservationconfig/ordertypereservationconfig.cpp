#include "ordertypereservationconfig.h"
#include "ordertypereservationconfigpharmacygroup.h"
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace stockbooking {

OrderTypeReservationConfig::OrderTypeReservationConfig()
{
	m_PharmacyGroups = boost::make_shared<IOrderTypeReservationConfigPharmacyGroupCollection>();
}

OrderTypeReservationConfig::~OrderTypeReservationConfig()
{
}

const basar::Int32& OrderTypeReservationConfig::getId() const
{
	return m_Id;
}

const basar::Int32& OrderTypeReservationConfig::getReservationType() const
{
	return m_ReservationType;
}

const bool& OrderTypeReservationConfig::getWithPharmacyGroup() const
{
	return m_WithPharmacyGroup;
}

const basar::VarString& OrderTypeReservationConfig::getReservationName() const
{
	return m_ReservationName;
}

const basar::VarString& OrderTypeReservationConfig::getOrderType() const
{
	return m_OrderType;
}

const basar::VarString& OrderTypeReservationConfig::getOrderTypeReservationConfigName() const
{
	return m_OrderTypeReservationConfigName;
}

const basar::Int16& OrderTypeReservationConfig::getPriority() const
{
	return m_Priority;
}

const bool& OrderTypeReservationConfig::getReservedStockOnly() const
{
	return m_ReservedStockOnly;
}

const bool& OrderTypeReservationConfig::getFreeStockHasPriority() const
{
	return m_FreeStockHasPriority;
}

const IOrderTypeReservationConfigPharmacyGroupCollectionPtr OrderTypeReservationConfig::getPharmacyGroups() const
{
	return m_PharmacyGroups;
}

IOrderTypeReservationConfigPharmacyGroupPtr OrderTypeReservationConfig::addPharmacyGroup(const basar::VarString& pharmacyGroup)
{
	OrderTypeReservationConfigPharmacyGroupPtr pharmGrp = boost::make_shared<OrderTypeReservationConfigPharmacyGroup>();
	pharmGrp->setOrderTypeReservationConfigId(this->getId());
	pharmGrp->setPharmacyGroupId(pharmacyGroup);
	m_PharmacyGroups->push_back(pharmGrp);
	return pharmGrp;
}

bool OrderTypeReservationConfig::containsPharmacyGroup(const basar::VarString& pharmacyGroup)
{
	IOrderTypeReservationConfigPharmacyGroupCollection::const_iterator it;
	it = m_PharmacyGroups->begin();
	while (it != m_PharmacyGroups->end())
	{
		if ((*it)->getPharmacyGroupId() == pharmacyGroup)
		{
			return true;
		}
		++it;
	}
	return false;
}

void OrderTypeReservationConfig::setId(const basar::Int32& id)
{
	m_Id = id;
}

void OrderTypeReservationConfig::setOrderType(const basar::VarString& orderType)
{
	m_OrderType = orderType;
}

void OrderTypeReservationConfig::setReservationType(const basar::Int32& reservationType)
{
	m_ReservationType = reservationType;
}

void OrderTypeReservationConfig::setOrderTypeReservationConfigName(const basar::VarString& name)
{
	m_OrderTypeReservationConfigName = name;
}

void OrderTypeReservationConfig::setPriority(const basar::Int16& priority)
{
	m_Priority = priority;
}

void OrderTypeReservationConfig::setReservedStockOnly(const bool& reservedOnly)
{
	m_ReservedStockOnly = reservedOnly;
}

void OrderTypeReservationConfig::setFreeStockHasPriority(const bool& freeStockHasPriority)
{
	m_FreeStockHasPriority = freeStockHasPriority;
}

bool OrderTypeReservationConfig::isInsertable() const
{
	return	m_Id.isUnset() &&

		m_Priority.isDirty() &&
		m_OrderType.isDirty() &&
		m_OrderTypeReservationConfigName.isDirty() &&
		m_ReservationType.isDirty() &&
		m_ReservedStockOnly.isDirty() &&
		m_FreeStockHasPriority.isDirty();
}

bool OrderTypeReservationConfig::isUpdatable() const
{
	return m_Id.isClean() &&
		(
			m_Priority.isDirty() &&
			m_OrderType.isDirty() &&
			m_OrderTypeReservationConfigName.isDirty() &&
			m_ReservationType.isDirty() &&
			m_ReservedStockOnly.isDirty() &&
			m_FreeStockHasPriority.isDirty()
		);
}


bool OrderTypeReservationConfig::isClean() const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "OrderTypeReservationConfig::isClean()");
	return m_Priority.isClean() &&
			m_OrderType.isClean() &&
			m_OrderTypeReservationConfigName.isClean() &&
			m_ReservationType.isClean() &&
			m_ReservedStockOnly.isClean() &&
			m_FreeStockHasPriority.isClean();
}

bool OrderTypeReservationConfig::operator < (const IOrderTypeReservationConfig& rhs) const
{
	// TODO FN clarify priority 1-15 or 15-1...
	return getPriority() > rhs.getPriority();
}


} // namespace stockbooking
} // namespace libcsc
