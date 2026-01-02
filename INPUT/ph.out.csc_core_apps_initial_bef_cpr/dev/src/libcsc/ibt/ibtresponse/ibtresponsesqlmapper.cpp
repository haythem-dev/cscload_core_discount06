#include "ibtresponsesqlmapper.h"
#include "ibtresponse.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtResponseSqlMapper::IbtResponseSqlMapper( IbtResponsePtr ibtResponse, const basar::db::sql::ResultsetRef resultSet )
: IbtResponseMapperBase( ibtResponse ), m_ResultSet( resultSet )
{
}

IbtResponseSqlMapper::~IbtResponseSqlMapper()
{
}

void IbtResponseSqlMapper::doMap()
{
    // TODO: check ResultSet
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setIbtRequestId( m_ResultSet.getInt32( "ibtrequestid" ) );
	setIbtResponseId( m_ResultSet.getInt32( "ibtresponseid" ) );
    setIbtOrderNo( m_ResultSet.getInt32( "ibtorderno" ) );
    setIbtOrderPosNo( m_ResultSet.getInt32( "ibtorderposno" ) );
    setIbtConfirmedQuantity( m_ResultSet.getInt32( "ibtconfirmedqty" ) );
	setCreationDateTime( m_ResultSet.getDateTime( "creationdatetime" ) );    
}

bool IbtResponseSqlMapper::isInsertable( const IbtResponsePtr ibtResponse )
{
    return ibtResponse->getIbtResponseId().isUnset();
}

bool IbtResponseSqlMapper::isUpdateable( const IbtResponsePtr ibtResponse )
{
    return ibtResponse->getIbtResponseId().isClean();
}

const basar::VarString IbtResponseSqlMapper::getInsertSQL( const IbtResponsePtr ibtResponse )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtResponseSqlMapper::getInsertSQL()" );

	std::stringstream ss;
	ss << "INSERT INTO ibtresponse "
		"( "
		"ibtrequestid, "
		"creationdatetime, "
		"ibtorderno, "
		"ibtorderposno, "
		"ibtconfirmedqty "
		") VALUES ( "
		<< ibtResponse->getIbtRequestId() << ", "
		"CURRENT, "
		<< ibtResponse->getIbtOrderNo() << ", "
		<< ibtResponse->getIbtOrderPosNo() << ", "
		<< ibtResponse->getIbtConfirmedQuantity() << " "
		") ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString IbtResponseSqlMapper::getUpdateSQL(const IbtResponsePtr ibtResponse)
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerIbtRequest(), "IbtResponseSqlMapper::getUpdateSQL()");

	std::stringstream ss;
	ss <<
		"UPDATE ibtresponse SET "
			"ibtorderno = " << ibtResponse->getIbtOrderNo() << ", "
			"ibtorderposno = " << ibtResponse->getIbtOrderPosNo() << ", "
			"ibtconfirmedqty = " << ibtResponse->getIbtConfirmedQuantity() << " "
		"WHERE "
			"ibtresponseid = " << ibtResponse->getIbtResponseId().get();

	BLOG_TRACE(LoggerPool::getLoggerIbtRequest(), ss.str().c_str());

	return ss.str().c_str();
}

const basar::VarString IbtResponseSqlMapper::getSelectSQL( const basar::Int32 ibtOrderNo, const basar::Int32 ibtPosNo )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtResponseSqlMapper::getSelectSQL()" );

	std::stringstream ss;
	ss << "SELECT FIRST 1 "
		"ibtrequestid, "
		"ibtresponseid, "
		"ibtorderno, "
		"ibtorderposno, "
		"ibtconfirmedqty, "
		"creationdatetime "
		"FROM ibtresponse "
		"WHERE ibtorderno=" << ibtOrderNo << "AND ibtorderposno=" << ibtPosNo << " " <<
		"ORDER BY creationdatetime desc";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str().c_str();
}


} // end namespace ibt
} // end namespace libcsc
