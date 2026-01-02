#include "reservationconfigrepository.h"
#include <stockbooking/reservationconfig/reservationtypesqlmapper.h>
#include <stockbooking/reservationconfig/reservationtype.h>
#include <stockbooking/reservationconfig/ordertypereservationconfigsqlmapper.h>
#include <stockbooking/reservationconfig/ordertypereservationconfig.h>
#include <stockbooking/reservationconfig/ordertypereservationconfigpharmacygroupsqlmapper.h>
#include <stockbooking/reservationconfig/ordertypereservationconfigpharmacygroup.h>
#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace stockbooking {

ReservationConfigRepository::ReservationConfigRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::ReservationConfigRepository()");
}

ReservationConfigRepository::~ReservationConfigRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::~ReservationConfigRepository()");

	m_SelectReservationTypesAccessor.reset();
	m_SelectOrderTypeReservationConfigAccessor.reset();
	m_InsertOrderTypeReservationConfigAccessor.reset();
	m_UpdateOrderTypeReservationConfigAccessor.reset();
	m_DeleteOrderTypeReservationConfigAccessor.reset();
	m_SelectOrderTypeReservationConfigPharmacyGroupAccessor.reset();
	m_InsertOrderTypeReservationConfigPharmacyGroupAccessor.reset();
	m_DeleteOrderTypeReservationConfigPharmacyGroupAccessor.reset();

}

void ReservationConfigRepository::reset()
{
	m_ReservationTypeList.reset();
	m_OrderTypesReservationConfigMap.reset();
}

void ReservationConfigRepository::injectSelectReservationTypesAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectSelectReservationTypesAccessor()");

	m_SelectReservationTypesAccessor = accessor;
}

void ReservationConfigRepository::injectSelectOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectSelectOrderTypesReservationConfigAccessor()");
	m_SelectOrderTypeReservationConfigAccessor = accessor;
}

void ReservationConfigRepository::injectInsertOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectInsertOrderTypesReservationConfigAccessor()");
	m_InsertOrderTypeReservationConfigAccessor = accessor;
}

void ReservationConfigRepository::injectUpdateOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectUpdateOrderTypesReservationConfigAccessor()");
	m_UpdateOrderTypeReservationConfigAccessor = accessor;
}

void ReservationConfigRepository::injectDeleteOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectDeleteOrderTypesReservationConfigAccessor()");
	m_DeleteOrderTypeReservationConfigAccessor = accessor;
}

void ReservationConfigRepository::injectSelectOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectSelectOrderTypesReservationConfigPharmacyGroupAccessor()");
	m_SelectOrderTypeReservationConfigPharmacyGroupAccessor = accessor;
}

void ReservationConfigRepository::injectInsertOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectInsertOrderTypesReservationConfigPharmacyGroupAccessor()");
	m_InsertOrderTypeReservationConfigPharmacyGroupAccessor = accessor;
}

void ReservationConfigRepository::injectDeleteOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::injectDeleteOrderTypesReservationConfigPharmacyGroupAccessor()");
	m_DeleteOrderTypeReservationConfigPharmacyGroupAccessor = accessor;
}

IReservationTypeCollectionPtr ReservationConfigRepository::findReservationTypes()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::findReservationTypes()");

	if (NULL == m_ReservationTypeList.get())
	{
		m_ReservationTypeList = boost::make_shared<IReservationTypeCollection>();
		try
		{
			basar::db::sql::ResultsetRef resultset = m_SelectReservationTypesAccessor->select(ReservationTypeSQLMapper::getSelectSQL());
			while (resultset.next())
			{
				ReservationTypePtr reservationType = boost::make_shared<ReservationType>();
				ReservationTypeSQLMapper mapper(reservationType, resultset);
				mapper.map();
				m_ReservationTypeList->push_back(reservationType);
			}
		}
		catch (basar::Exception &)
		{
			throw;
		}
	}
	return m_ReservationTypeList;
}

IReservationTypePtr ReservationConfigRepository::findReservationType(const basar::Int32& type)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::findReservationType()");

	IReservationTypePtr reservationType;
	IReservationTypeCollectionPtr coll = findReservationTypes();
	IReservationTypeCollection::const_iterator it = coll->begin();
	while (it != coll->end())
	{
		if ((*it)->getReservationType() == type)
		{
			reservationType = (*it);
			break;
		}
		++it;
	}
	return reservationType;
}


IOrderTypeReservationConfigCollectionPtr ReservationConfigRepository::findOrderTypeReservationConfig(
	const basar::VarString& orderType)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::findOrderTypeReservationConfig()");

	if (NULL == m_OrderTypesReservationConfigMap.get())
	{
		readOrderTypeReservationConfig();
	}

	IOrderTypeReservationConfigCollectionPtr coll;
	IOrderTypeReservationConfigCollectionMap::iterator mapIt = m_OrderTypesReservationConfigMap->find(orderType);
	if (mapIt != m_OrderTypesReservationConfigMap->end())
	{
		coll = mapIt->second;
	}
	return coll;
}

IOrderTypeReservationConfigPtr ReservationConfigRepository::findOrderTypeReservationConfigById(const basar::Int32& id)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::findOrderTypeReservationConfigById()");

	OrderTypeReservationConfigPtr config = boost::make_shared<OrderTypeReservationConfig>();
	try
	{
		basar::db::sql::ResultsetRef resultset = m_SelectOrderTypeReservationConfigAccessor->select(
			OrderTypeReservationConfigSQLMapper::getSelectSQLById(id));
		if (resultset.next())
		{
			OrderTypeReservationConfigSQLMapper mapper(config, resultset);
			mapper.map();
			findOrderTypeReservationConfigPharmacyGroup(config);
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}
	return config;
}

IOrderTypeReservationConfigPtr ReservationConfigRepository::getEmptyOrderTypeReservationConfig()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::getEmptyOrderTypeReservationConfig()");

	return boost::make_shared<OrderTypeReservationConfig>();
}

void ReservationConfigRepository::saveOrderTypeReservationConfig(IOrderTypeReservationConfigPtr orderTypeReservationConfig)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::saveOrderTypeReservationConfig()");
	try
	{
		if (orderTypeReservationConfig->isInsertable())
		{
			m_InsertOrderTypeReservationConfigAccessor->execute(OrderTypeReservationConfigSQLMapper::getInsertSQL(orderTypeReservationConfig));
			orderTypeReservationConfig->setId(static_cast<basar::Int32>(m_InsertOrderTypeReservationConfigAccessor->getLastInsertedSerial()));
		}
		else if (orderTypeReservationConfig->isUpdatable())
		{
			m_UpdateOrderTypeReservationConfigAccessor->execute(
				OrderTypeReservationConfigSQLMapper::getUpdateSQL(orderTypeReservationConfig)
			);
		}
		IOrderTypeReservationConfigPharmacyGroupCollection::const_iterator it;
		it = orderTypeReservationConfig->getPharmacyGroups()->begin();
		while (it != orderTypeReservationConfig->getPharmacyGroups()->end())
		{
			if ((*it)->isInsertable())
			{
				saveOrderTypeReservationConfigPharmacyGroup(*it);
			}
			else if ((*it)->isMarkedForDeletion())
			{
				deleteOrderTypeReservationConfigPharmacyGroupById((*it)->getId());
			}
			++it;
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void ReservationConfigRepository::deleteOrderTypeReservationConfig(IOrderTypeReservationConfigPtr orderTypeReservationConfig)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::deleteOrderTypeReservationConfig()");

	try
	{
		m_DeleteOrderTypeReservationConfigAccessor->execute(
			OrderTypeReservationConfigSQLMapper::getDeleteSQL(orderTypeReservationConfig->getId())
		);
		deleteOrderTypeReservationConfigPharmacyGroupByReservationId(orderTypeReservationConfig);
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void ReservationConfigRepository::findOrderTypeReservationConfigPharmacyGroup(OrderTypeReservationConfigPtr reservationConfig)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::findOrderTypeReservationConfigPharmacyGroup()");

	try
	{
		basar::db::sql::ResultsetRef resultset = m_SelectOrderTypeReservationConfigPharmacyGroupAccessor->select(
			OrderTypeReservationConfigPharmacyGroupSQLMapper::getSelectSQLByReservationId(reservationConfig->getId()) );
		while (resultset.next())
		{
			OrderTypeReservationConfigPharmacyGroupPtr config_grp = boost::make_shared<OrderTypeReservationConfigPharmacyGroup>();
			OrderTypeReservationConfigPharmacyGroupSQLMapper mapper(config_grp, resultset);
			mapper.map();
			reservationConfig->m_PharmacyGroups->push_back(config_grp);
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void ReservationConfigRepository::saveOrderTypeReservationConfigPharmacyGroup(IOrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::saveOrderTypeReservationConfigPharmacyGroup()");
	try
	{
		if (orderTypeReservationConfigPharmacyGroup->isInsertable())
		{
			m_InsertOrderTypeReservationConfigPharmacyGroupAccessor->execute(OrderTypeReservationConfigPharmacyGroupSQLMapper::getInsertSQL(orderTypeReservationConfigPharmacyGroup));
			orderTypeReservationConfigPharmacyGroup->setId(static_cast<basar::Int32>(m_InsertOrderTypeReservationConfigPharmacyGroupAccessor->getLastInsertedSerial()));
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void ReservationConfigRepository::deleteOrderTypeReservationConfigPharmacyGroupById(const basar::Int32& id)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::deleteOrderTypeReservationConfigPharmacyGroupById()");
	try
	{
		m_DeleteOrderTypeReservationConfigPharmacyGroupAccessor->execute(
			OrderTypeReservationConfigPharmacyGroupSQLMapper::getDeleteSQLById(id)
		);
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void ReservationConfigRepository::deleteOrderTypeReservationConfigPharmacyGroupByReservationId( IOrderTypeReservationConfigPtr orderTypeReservationConfig )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::deleteOrderTypeReservationConfigPharmacyGroupByReservationId()");
	try
	{
		m_DeleteOrderTypeReservationConfigPharmacyGroupAccessor->execute(
			OrderTypeReservationConfigPharmacyGroupSQLMapper::getDeleteSQLByReservationId(orderTypeReservationConfig->getId())
		);
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void ReservationConfigRepository::readOrderTypeReservationConfig()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationConfigRepository::readOrderTypeReservationConfig()");

	if (NULL == m_OrderTypesReservationConfigMap.get())
	{
		m_OrderTypesReservationConfigMap = boost::make_shared<IOrderTypeReservationConfigCollectionMap>();
	}

	basar::db::sql::ResultsetRef resultset = m_SelectOrderTypeReservationConfigAccessor->select(
		OrderTypeReservationConfigSQLMapper::getSelectSQL()
	);
	while (resultset.next())
	{
		OrderTypeReservationConfigPtr orderTypeReservationConfig = boost::make_shared<OrderTypeReservationConfig>();
		OrderTypeReservationConfigSQLMapper mapper(orderTypeReservationConfig, resultset);
		mapper.map();
		findOrderTypeReservationConfigPharmacyGroup(orderTypeReservationConfig);

		basar::VarString orderType = orderTypeReservationConfig->getOrderType();
		IOrderTypeReservationConfigCollectionMap::iterator mapIt = m_OrderTypesReservationConfigMap->find(orderType);
		if (mapIt != m_OrderTypesReservationConfigMap->end())
		{
			mapIt->second->push_back(orderTypeReservationConfig);
		}
		else
		{
			IOrderTypeReservationConfigCollectionPtr coll = boost::make_shared<IOrderTypeReservationConfigCollection>();
			coll->push_back(orderTypeReservationConfig);
			m_OrderTypesReservationConfigMap->insert(std::make_pair(orderType, coll));
		}
	}
}

} // end namespace stockbooking
} // end namespace libcsc
