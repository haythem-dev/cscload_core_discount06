#include "articlereservationsqlmapper.h"
#include "articlereservation.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace stockbooking {

ArticleReservationSQLMapper::ArticleReservationSQLMapper(ArticleReservationPtr articleReservation , const basar::db::sql::ResultsetRef resultSet) :
	ArticleReservationMapperBase(articleReservation),
	m_ResultSet(resultSet)
{
}

ArticleReservationSQLMapper::~ArticleReservationSQLMapper()
{
}

const basar::VarString ArticleReservationSQLMapper::getSelectSQL(const basar::Int16& branchNo, const basar::Int32& articleNo )
{
	std::stringstream sSql;

	sSql << "SELECT "
		"branchno, "
		"pharmacygroupid, "
		"articleno, "
		"reservtype ,"
		"maxqty ,"
		"reservedqty ,"
		"reservepct "
		"FROM "
		"articlereservation "
		"WHERE branchno = " << branchNo << " and articleno = " << articleNo ;

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString ArticleReservationSQLMapper::getUpdateSQL(const IArticleReservationPtr articleReservation )
{
	std::stringstream sSql;

	sSql << "UPDATE "
		"articlereservation SET "
		"reservedqty = " << articleReservation->getReservedQty() << ", "
		"maxqty = " << articleReservation->getMaxQty() << ", "
		"reservepct = " << articleReservation->getReservePct() <<
		" WHERE branchno = " << articleReservation->getBranchNo() <<
		" AND articleno = " << articleReservation->getArticleNo() <<
		" AND reservtype = " << articleReservation->getReservType();

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString ArticleReservationSQLMapper::getInsertSQL(const IArticleReservationPtr articleReservation )
{
	std::stringstream sSql;
	
	sSql << "INSERT INTO articlereservation "
		" ( branchno, pharmacygroupid, articleno, reservtype, maxqty, reservedqty, reservepct ) "
		" VALUES ( " << articleReservation->getBranchNo() << ", '" << articleReservation->getPharmacyGroupId() << "' ," 
		<< articleReservation->getArticleNo() << "," << articleReservation->getReservType() << ", " << articleReservation->getMaxQty() << ", " 
		<< articleReservation->getReservedQty() << ", " << articleReservation->getReservePct() << " )";

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

const basar::VarString ArticleReservationSQLMapper::getDeleteSQL( const IArticleReservationPtr articleReservation )
{
	std::stringstream sSql;
	
	sSql << "DELETE FROM articlereservation "
	" WHERE branchno = " << articleReservation->getBranchNo() <<
	" AND articleno = " << articleReservation->getArticleNo() <<
	" AND reservtype = " << articleReservation->getReservType();

	BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sSql.str());
	return sSql.str();

}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void ArticleReservationSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setPharmacyGroupId(m_ResultSet.getString("pharmacygroupid") );
	setArticleNo( m_ResultSet.getInt32("articleno") );
	setReservType( m_ResultSet.getInt16("reservtype") );
	setMaxQty(m_ResultSet.getInt32("maxqty"));
	setReservedQty(m_ResultSet.getInt32("reservedqty"));
	setReservePct(m_ResultSet.getInt16("reservepct"));

}

}
}