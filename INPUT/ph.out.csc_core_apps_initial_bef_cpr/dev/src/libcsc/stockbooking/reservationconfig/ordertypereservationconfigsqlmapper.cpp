#include "ordertypereservationconfigsqlmapper.h"
#include "ordertypereservationconfig.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

OrderTypeReservationConfigSQLMapper::OrderTypeReservationConfigSQLMapper(OrderTypeReservationConfigPtr orderTypeReservationConfig , const basar::db::sql::ResultsetRef resultSet) :
	OrderTypeReservationConfigMapperBase(orderTypeReservationConfig),
	m_ResultSet(resultSet)
{
}

OrderTypeReservationConfigSQLMapper::~OrderTypeReservationConfigSQLMapper()
{
}

const basar::VarString OrderTypeReservationConfigSQLMapper::getSelectSQL()
{
	std::stringstream sSql;

	sSql << "SELECT "
		"otrc.id, "
		"csc.cscreservationtype, "
		"csc.withpharmacygroup, "
		"csc.cscreservationtypename, "
		"otrc.cscordertype, "
		"otrc.ordertypereservationconfigname, "
		"otrc.priority, "
		"otrc.reservedstockonly, "
		"otrc.freestockhaspriority "
		"FROM "
		"ordertypereservationconfig AS otrc "
		"INNER JOIN cscreservationtypes csc ON csc.cscreservationtype = otrc.cscreservationtype "
		"ORDER BY otrc.cscordertype, otrc.priority ";

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

const basar::VarString OrderTypeReservationConfigSQLMapper::getSelectSQLById(const basar::Int32& id)
{
	std::stringstream sSql;

	sSql << "SELECT "
		"otrc.id, "
		"csc.cscreservationtype, "
		"csc.withpharmacygroup, "
		"csc.cscreservationtypename, "
		"otrc.cscordertype, "
		"otrc.ordertypereservationconfigname, "
		"otrc.priority, "
		"otrc.reservedstockonly, "
		"otrc.freestockhaspriority "
		"FROM "
		"ordertypereservationconfig AS otrc "
		"INNER JOIN cscreservationtypes csc ON csc.cscreservationtype = otrc.cscreservationtype "
		"WHERE otrc.id = " << id;

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}


const basar::VarString OrderTypeReservationConfigSQLMapper::getSelectSQLByOrderType( const basar::VarString& orderType )
{
	std::stringstream sSql;

	sSql << "SELECT "
		"otrc.id, "
		"csc.cscreservationtype, "
		"csc.withpharmacygroup, "
		"csc.cscreservationtypename, "
		"otrc.cscordertype, "
		"otrc.ordertypereservationconfigname, "
		"otrc.priority, "
		"otrc.reservedstockonly, "
		"otrc.freestockhaspriority "
		"FROM "
		"ordertypereservationconfig AS otrc "
		"INNER JOIN cscreservationtypes csc ON csc.cscreservationtype = otrc.cscreservationtype "
		"WHERE otrc.cscordertype ='" << orderType << "' "
		"ORDER BY otrc.priority ASC";

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

const basar::VarString OrderTypeReservationConfigSQLMapper::getUpdateSQL(const IOrderTypeReservationConfigPtr orderTypeReservationConfig )
{
	std::stringstream sSql;

	sSql << "UPDATE "
		"ordertypereservationconfig SET "
		"priority = " << orderTypeReservationConfig->getPriority() << ", "
		"cscordertype = '" << orderTypeReservationConfig->getOrderType() << "', " <<
		"ordertypereservationconfigname = '" << orderTypeReservationConfig->getOrderTypeReservationConfigName() << "', " <<
		"cscreservationtype = " << orderTypeReservationConfig->getReservationType() << ", " <<
		"reservedstockonly = " << orderTypeReservationConfig->getReservedStockOnly() << ", " <<
		"freestockhaspriority = " << orderTypeReservationConfig->getFreeStockHasPriority() <<
		" WHERE id = " << orderTypeReservationConfig->getId();
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

const basar::VarString OrderTypeReservationConfigSQLMapper::getInsertSQL( const IOrderTypeReservationConfigPtr orderTypeReservationConfig )
{
	std::stringstream sSql;
	
	sSql << "INSERT INTO ordertypereservationconfig "
		" (priority, cscordertype, ordertypereservationconfigname, cscreservationtype, reservedstockonly, freestockhaspriority ) "
		" VALUES ( " 
		<< orderTypeReservationConfig->getPriority() << 
		", '" << orderTypeReservationConfig->getOrderType() << "' , '" << orderTypeReservationConfig->getOrderTypeReservationConfigName() <<"' ," 
		<< orderTypeReservationConfig->getReservationType() << "," 
		<< orderTypeReservationConfig->getReservedStockOnly() << "," 
		<< orderTypeReservationConfig->getFreeStockHasPriority() << ")";
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

const basar::VarString OrderTypeReservationConfigSQLMapper::getDeleteSQL( const basar::Int32& id )
{
	std::stringstream sSql;
	sSql << "DELETE FROM ordertypereservationconfig WHERE id = " << id ;
	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}
//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void OrderTypeReservationConfigSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setId				( m_ResultSet.getInt32("id"));

	setReservationType	( m_ResultSet.getInt32("cscreservationtype"));
	setWithPharmacyGroup( m_ResultSet.getInt16("withpharmacygroup"));
	setReservationName	( m_ResultSet.getString("cscreservationtypename"));

	setOrderType(m_ResultSet.getString("cscordertype"));
	setOrderTypeReservationConfigName(m_ResultSet.getString("ordertypereservationconfigname"));
	setPriority(m_ResultSet.getInt16("priority"));
	setReservedStockOnly(m_ResultSet.getInt16("reservedstockonly"));
	setFreeStockHasPriority(m_ResultSet.getInt16("freestockhaspriority"));

}

}
}