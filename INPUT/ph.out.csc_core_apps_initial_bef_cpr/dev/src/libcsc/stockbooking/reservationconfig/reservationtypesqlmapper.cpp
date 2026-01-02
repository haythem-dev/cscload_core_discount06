#include "reservationtypesqlmapper.h"
#include "reservationtype.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

ReservationTypeSQLMapper::ReservationTypeSQLMapper(ReservationTypePtr reservationType , const basar::db::sql::ResultsetRef resultSet) :
	ReservationTypeMapperBase(reservationType),
	m_ResultSet(resultSet)
{
}

ReservationTypeSQLMapper::~ReservationTypeSQLMapper()
{
}


const basar::VarString ReservationTypeSQLMapper::getSelectSQL()
{
	std::stringstream sSql;
	sSql <<
		"SELECT "
			"id, "
			"cscreservationtypename, "
			"cscreservationtype, "
			"withpharmacygroup "
		"FROM cscreservationtypes " ;

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void ReservationTypeSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setId				( m_ResultSet.getInt32("id"));
	setReservationType	( m_ResultSet.getInt32("cscreservationtype"));
	setWithPharmacyGroup( m_ResultSet.getInt16("withpharmacygroup"));
	setReservationName	( m_ResultSet.getString("cscreservationtypename"));
}

}
}
