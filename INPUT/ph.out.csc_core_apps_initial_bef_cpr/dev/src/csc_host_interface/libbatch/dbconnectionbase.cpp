//--------------------------------------------------------------------------------------------------//
/*! \file connectionbase.cpp
 *  \brief default definition of abstract connection base class
 *  \author Dirk Kapusta
 *  \date 27.01.2009
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasardbaspect.h>
#include "dbconnectionbase.h"
#include "loggerpool.h"
#include "classinfo_macros.h"


//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
using basar::db::aspect::ConnectionRef;
        
//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libBatch
{
namespace dbConnection
{

DBConnectionBase::DBConnectionBase( const basar::db::sql::DatabaseInfo& databaseInfo )
: m_Logger( LoggerPool::LoggerDBConnection ), m_DatabaseInfo( databaseInfo )
{
	METHODNAME_DEF( DBConnectionBase, DBConnectionBase )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

DBConnectionBase::~DBConnectionBase()
{
	METHODNAME_DEF( DBConnectionBase, ~DBConnectionBase )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

//bool DBConnectionBase::establishConnection()
//{
//	METHODNAME_DEF( DBConnectionBase, establishConnection )
//	BLOG_TRACE_METHOD( m_Logger, fun );	
//
//	bool retval = false;
//
//	connect();
//	if( getCurrentConnection().isOpen() )
//	{
//		retval = true;
//	}
//
//	return retval;
//}

bool DBConnectionBase::isOpen() const
{
    if( m_ActiveConn.isNull() )
    {
        return false;
    }
    return m_ActiveConn.isOpen();
}

bool DBConnectionBase::isValid() const
{
    if( m_ActiveConn.isNull() )
    {
        return false;
    }
    if (!m_ActiveConn.isOpen())
    {
        return false;
    }

    basar::db::sql::ConnectionRef dbConnRef = m_ActiveConn.getSqlConnection();

    return dbConnRef.isValid();
}

void DBConnectionBase::connect()
{
    METHODNAME_DEF( DBConnectionBase, connect )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_DatabaseInfo.eConnectType = getConnectionType();
    m_ActiveConn = basar::db::aspect::Manager::getInstance().createConnect( m_DatabaseInfo );

    doConnect();

    logConnect();
}

void DBConnectionBase::logConnect() const
{
    METHODNAME_DEF( DBConnectionBase, logConnect )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( m_Logger.isEnabledFor( log4cplus::INFO_LOG_LEVEL ) ){
        std::stringstream ss;
        ss  << "Successfully connected to db:" << std::endl << m_ActiveConn.getDbInfo();
        m_Logger.forcedLog( log4cplus::INFO_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }
}

void DBConnectionBase::logDisconnect() const
{
    METHODNAME_DEF( DBConnectionBase, logDisconnect )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( m_Logger.isEnabledFor( log4cplus::INFO_LOG_LEVEL ) ){
        std::stringstream ss;
        ss  << "Successfully disconnected from db:" << std::endl << m_ActiveConn.getDbInfo();
        m_Logger.forcedLog( log4cplus::INFO_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }
}

void DBConnectionBase::disconnect()
{
    METHODNAME_DEF( DBConnectionBase, disconnect )
    BLOG_TRACE_METHOD( m_Logger, fun );

    if( m_ActiveConn.isNull() )
    {
        return;
    }
    m_ActiveConn.close();

    logDisconnect();
}

/*! \return Reference to current connection; used to create an instance of an accessor definition \n \throw no-throw */
const ConnectionRef DBConnectionBase::getCurrentConnection() const
{
    METHODNAME_DEF( DBConnectionBase, getCurrentConnection )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_ActiveConn;
}

const basar::db::sql::DatabaseInfo& DBConnectionBase::getDBInfo() const
{
    return m_DatabaseInfo;
}

/*! \throw no-throw */
void DBConnectionBase::setIsolationLevel( basar::IsolationLevelEnum eLevel )
{
    METHODNAME_DEF( DBConnectionBase, setIsolationLevel )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_ActiveConn.setIsolationLevel( eLevel );
}

/*! \throw no-throw */
void DBConnectionBase::setLockModeWait( basar::LockModeEnum eMode , basar::UInt32 secs )
{
    METHODNAME_DEF( DBConnectionBase, setLockModeWait )
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_ActiveConn.setLockModeWait( eMode, secs );
}

} // end namespace dbConnection
} // end namespace libBatch
