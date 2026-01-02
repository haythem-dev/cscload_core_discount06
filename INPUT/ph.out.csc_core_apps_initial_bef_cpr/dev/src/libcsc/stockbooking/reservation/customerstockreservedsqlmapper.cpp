#include "customerstockreservedsqlmapper.h"
#include "customerstockreserved.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

CustomerStockReservedSQLMapper::CustomerStockReservedSQLMapper(CustomerStockReservedPtr customerStockReserved , const basar::db::sql::ResultsetRef resultSet) :
	CustomerStockReservedMapperBase(customerStockReserved),
	m_ResultSet(resultSet)
{
}

CustomerStockReservedSQLMapper::~CustomerStockReservedSQLMapper()
{
}

const basar::VarString CustomerStockReservedSQLMapper::getSelectSQL(const basar::VarString & dbName ,const basar::Int16& branchNo, const basar::Int32& articleNo )
{
	std::stringstream sSql;

	sSql << "SELECT "
		"branchno, "
		"customerno, "
		"articleno, "
		"reservedqty, "
		"datefrom, "
		"timefrom, "
		"dateto , "
		"timeto, "
		"kdauftragnr, "
		"reservtype "
		"FROM " << dbName << ":cststockreserved "
		"WHERE branchno = " << branchNo << " and articleno = " << articleNo ;

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();
}

const basar::VarString CustomerStockReservedSQLMapper::getUpdateSQL(const basar::VarString & dbName ,const ICustomerStockReservedPtr customerStockReserved )
{
	std::stringstream sSql;

	sSql << "UPDATE " << dbName << 
		":cststockreserved SET "
		"reservedqty = " << customerStockReserved->getReservedQty() << ", "
		"dateto = " << customerStockReserved->getDateTo() << ", "
		"timeto = " << customerStockReserved->getTimeTo() <<
		" WHERE branchno = " << customerStockReserved->getBranchNo() <<
		" AND customerno = " << customerStockReserved->getCustomerNo() <<
		" AND articleno = " << customerStockReserved->getArticleNo() <<
		" AND reservtype = " << customerStockReserved->getReservType() <<
		" AND kdauftragnr = " << customerStockReserved->getKdAuftragNr() <<
		" AND datefrom = " << customerStockReserved->getDateFrom();

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString CustomerStockReservedSQLMapper::getDeleteSQL(const basar::VarString & dbName , const ICustomerStockReservedPtr customerStockReserved )
{
	std::stringstream sSql;
	
	sSql << "DELETE FROM " << dbName << ":cststockreserved "
	" WHERE branchno = " << customerStockReserved->getBranchNo() <<
	" AND customerno = " << customerStockReserved->getCustomerNo() <<
	" AND articleno = " << customerStockReserved->getArticleNo() <<
	" AND reservtype = " << customerStockReserved->getReservType() <<
	" AND kdauftragnr = " << customerStockReserved->getKdAuftragNr() <<
	" AND datefrom = " << customerStockReserved->getDateFrom();

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void CustomerStockReservedSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setCustomerNo(m_ResultSet.getInt32("customerno"));
	setArticleNo(m_ResultSet.getInt32("articleno") );
	setReservedQty(m_ResultSet.getInt32("reservedqty") );
	setDateFrom(m_ResultSet.getInt32("datefrom"));
	setTimeFrom(m_ResultSet.getInt32("timefrom"));
	setDateTo(m_ResultSet.getInt32("dateto") );
	setTimeTo(m_ResultSet.getInt32("timeto"));
	setKdAuftragNr(m_ResultSet.getInt32("kdauftragnr"));
	setReservType(m_ResultSet.getInt16("reservtype"));

}

}
}