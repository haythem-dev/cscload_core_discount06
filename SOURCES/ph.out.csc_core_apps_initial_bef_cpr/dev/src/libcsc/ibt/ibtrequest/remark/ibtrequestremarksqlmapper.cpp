#include "ibtrequestremarksqlmapper.h"
#include "ibtrequestremark.h"
#include "logger/loggerpool.h"

namespace libcsc
{
namespace ibt
{
IbtRequestRemarkSqlMapper::IbtRequestRemarkSqlMapper( IbtRequestRemarkPtr ibtRequestRemark, const basar::db::sql::ResultsetRef resultSet )
: IbtRequestRemarkMapperBase( ibtRequestRemark ), m_ResultSet( resultSet )
{
}

IbtRequestRemarkSqlMapper::~IbtRequestRemarkSqlMapper()
{
}

void IbtRequestRemarkSqlMapper::doMap()
{
    // TODO: check ResultSet
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setIbtRequestId( m_ResultSet.getInt32( "ibtrequestid" ) );
    setRemarkLevel( static_cast<IbtRequestRemarkLevelEnum>( m_ResultSet.getInt16( "remarklevel" ) ) );
    setRemark( m_ResultSet.getString( "remark" ) );
    setRemarkType( static_cast<OrderRemarkTypeEnum>( m_ResultSet.getInt16( "remarktype" ) ) );
}

bool IbtRequestRemarkSqlMapper::isInsertable( const IbtRequestRemarkPtr ibtRequestRemark )
{
	return ibtRequestRemark->getIbtRequestId().isDirty();
}

bool IbtRequestRemarkSqlMapper::isUpdatable( const IbtRequestRemarkPtr ibtRequestRemark )
{
    return (    ibtRequestRemark->getIbtRequestId().isClean()
			 && ibtRequestRemark->getRemarkLevel().isClean()
			 && ibtRequestRemark->getRemarkType().isClean()
			 && ibtRequestRemark->containsDirty() );
}

bool IbtRequestRemarkSqlMapper::isDeletable( const IbtRequestRemarkPtr ibtRequestRemark )
{
    return (    ibtRequestRemark->getIbtRequestId().isClean()
			 && ibtRequestRemark->getRemarkLevel().isClean()
			 && ibtRequestRemark->getRemarkType().isClean()
			 && 0 < ibtRequestRemark->getIbtRequestId() );
}

const basar::VarString IbtRequestRemarkSqlMapper::getSelectSQL( const basar::Int32 ibtRequestId )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRemarkSqlMapper::getSelectSQL()" );

    std::stringstream ss;
    ss << "SELECT "
		"ibtrequestid, "
		"remarklevel, "
		"remark, "
		"remarktype "
		"FROM ibtremarkrequest "
		"WHERE "
		"ibtrequestid = " << ibtRequestId << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestRemarkSqlMapper::getInsertSQL( const IbtRequestRemarkPtr ibtRequestRemark )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRemarkSqlMapper::getInsertSQL()" );

	std::stringstream ss;
	ss << "INSERT INTO ibtremarkrequest "
		"( "
		"ibtrequestid, "
		"remarklevel, "
		"remark, "
		"remarktype "
		") VALUES ( "
		<< ibtRequestRemark->getIbtRequestId().get() << ", "
		<< ibtRequestRemark->getRemarkLevel().get() << ", "
		<< "'" << ibtRequestRemark->getRemark().c_str() << "', "
		<< ibtRequestRemark->getRemarkType().get() << " "
		") ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString IbtRequestRemarkSqlMapper::getUpdateSQL( const IbtRequestRemarkPtr ibtRequestRemark )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRemarkSqlMapper::getUpdateSQL()" );
	
	std::stringstream ss;
	ss << "UPDATE ibtremarkrequest "
		"SET "
		"remark = " << "'" << ibtRequestRemark->getRemark().c_str() << "' "
		"WHERE "
		"ibtrequestid = " << ibtRequestRemark->getIbtRequestId().get() <<
		" AND "
		"remarklevel = " << ibtRequestRemark->getRemarkLevel().get() <<
		" AND "
		"remarktype = " << ibtRequestRemark->getRemarkType().get() << " "; 

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str();
}

const basar::VarString IbtRequestRemarkSqlMapper::getDeleteSQL( const IbtRequestRemarkPtr ibtRequestRemark )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRemarkSqlMapper::getDeleteSQL()" );

	std::stringstream ss;
	ss << "DELETE FROM ibtremarkrequest "
		"WHERE "
		"ibtrequestid = " << ibtRequestRemark->getIbtRequestId().get() <<
		" AND "
		"remarklevel = " << ibtRequestRemark->getRemarkLevel().get() << 
		" AND "
		"remarktype = " << ibtRequestRemark->getRemarkType().get() << " "; 

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

} // end namespace ibt
} // end namespace libcsc
