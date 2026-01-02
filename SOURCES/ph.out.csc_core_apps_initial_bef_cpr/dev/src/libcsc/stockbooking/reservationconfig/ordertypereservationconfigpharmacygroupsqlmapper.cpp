#include "ordertypereservationconfigpharmacygroupsqlmapper.h"
#include "ordertypereservationconfigpharmacygroup.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

OrderTypeReservationConfigPharmacyGroupSQLMapper::OrderTypeReservationConfigPharmacyGroupSQLMapper(OrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup , const basar::db::sql::ResultsetRef resultSet) :
	OrderTypeReservationConfigPharmacyGroupMapperBase(orderTypeReservationConfigPharmacyGroup),
	m_ResultSet(resultSet)
{
}

OrderTypeReservationConfigPharmacyGroupSQLMapper::~OrderTypeReservationConfigPharmacyGroupSQLMapper()
{
}

const basar::VarString OrderTypeReservationConfigPharmacyGroupSQLMapper::getSelectSQLByReservationId(const basar::Int32 reservationId)
{
	std::stringstream sSql;

	sSql << "SELECT "
		"id, "
		"pharmacygroupid, "
		"ordertypereservationconfig_id "
		"FROM "
		"ordertypereservationconfigcpg "
		"WHERE ordertypereservationconfig_id = " << reservationId;

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString OrderTypeReservationConfigPharmacyGroupSQLMapper::getInsertSQL(const IOrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup )
{
	std::stringstream sSql;
	
	sSql << "INSERT INTO ordertypereservationconfigcpg "
		" (pharmacygroupid, ordertypereservationconfig_id ) "
		" VALUES ( '" << orderTypeReservationConfigPharmacyGroup->getPharmacyGroupId() << "', " 
		<< orderTypeReservationConfigPharmacyGroup->getOrderTypeReservationConfigId() << ")";
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString OrderTypeReservationConfigPharmacyGroupSQLMapper::getDeleteSQLById( const basar::Int32 id )
{
	std::stringstream sSql;
	sSql << "DELETE FROM ordertypereservationconfigcpg WHERE id = " << id ;
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString OrderTypeReservationConfigPharmacyGroupSQLMapper::getDeleteSQLByReservationId( const basar::Int32 reservationId )
{
	std::stringstream sSql;
	sSql << "DELETE FROM ordertypereservationconfigcpg WHERE ordertypereservationconfig_id = " << reservationId ;
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}


void OrderTypeReservationConfigPharmacyGroupSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setId				( m_ResultSet.getInt32("id"));
	setPharmcyGroupId(m_ResultSet.getString("pharmacygroupid"));
	setOrderTypeReservationConfigId(m_ResultSet.getInt32("ordertypereservationconfig_id"));
}


}
}