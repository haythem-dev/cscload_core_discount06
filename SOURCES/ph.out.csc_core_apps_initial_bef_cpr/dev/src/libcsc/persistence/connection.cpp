#include "connection.h"
#include <libbasardbsql_databaseinfo.h>
#include <libbasardbsql_manager.h>
#include <libbasardbsql_statementref.h>
#include "exceptions/persistenceexception.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace persistence
{
Connection::Connection()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerSession(), "Connection::Connection()" );
}

Connection::Connection( basar::db::sql::ConnectionRef connection )
    : m_Connection( connection )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerSession(), "Connection::Connection( basar::db::sql::ConnectionRef )" );
}

Connection::~Connection()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerSession(), "Connection::~Connection()" );
}
	
void Connection::open( const basar::VarString & dbserver, const basar::VarString & database )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerSession(), "Connection::open()" );

	if( m_Connection.isNull() )
	{
		basar::db::sql::DatabaseInfo dbinfo;
		dbinfo.setInfxConcurrent( dbserver, database );
		m_Connection = basar::db::sql::Manager::getInstance().createConnect( dbinfo );
		m_Connection.setLockModeWait( basar::WAITSECS, 25 );
		return;
	}

	checkNotNullOrThrow( "Connection::open()", __LINE__ );
	m_Connection.open();
}

void Connection::close()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerSession(), "Connection::close()" );

	checkNotNullOrThrow( "Connection::close()", __LINE__ );
	checkOpenOrThrow( "Connection::close()", __LINE__ );
	m_Connection.close();
}

void Connection::beginTransaction()
{
	checkNotNullOrThrow( "Connection::beginTransaction()", __LINE__ );
	checkOpenOrThrow( "Connection::beginTransaction()", __LINE__ );
	m_Connection.begin();
}

void Connection::commitTransaction()
{
	checkNotNullOrThrow( "Connection::commitTransaction()", __LINE__ );
	checkOpenOrThrow( "Connection::commitTransaction()", __LINE__ );
	m_Connection.commit();
}

void Connection::rollbackTransaction()
{
	checkNotNullOrThrow( "Connection::rollbackTransaction()", __LINE__ );
	checkOpenOrThrow( "Connection::rollbackTransaction()", __LINE__ );
	m_Connection.rollback();
}

bool Connection::inTransaction() const
{
	checkNotNullOrThrow( "Connection::inTransaction()", __LINE__ );
	checkOpenOrThrow( "Connection::inTransaction()", __LINE__ );
	return m_Connection.isInTransaction();
}

void Connection::setExplainOn()
{
	checkNotNullOrThrow( "Connection::setExplainOn()", __LINE__ );
	checkOpenOrThrow( "Connection::setExplainOn()", __LINE__ );
	m_Connection.createStatement().execute("SET EXPLAIN ON");
}

void Connection::setExplainOff()
{
	checkNotNullOrThrow( "Connection::setExplainOff()", __LINE__ );
	checkOpenOrThrow( "Connection::setExplainOff()", __LINE__ );
	m_Connection.createStatement().execute("SET EXPLAIN OFF");
}

//----------------------------------------------------------------------------
//! \throw  no-throw
//!
void Connection::setIsolationLevel(const basar::IsolationLevelEnum eLevel,
								   const bool					  retainLocks /* = false */)
{
    checkNotNullOrThrow("Connection::setExplainOff()", __LINE__);
    checkOpenOrThrow("Connection::setExplainOff()", __LINE__);
    m_Connection.setIsolationLevel(eLevel, retainLocks);
}

basar::db::sql::ConnectionRef Connection::getDbSqlConnection() const
{
	return m_Connection;
}

void Connection::checkNotNullOrThrow( const char * context, const basar::Int32 line ) const
{
	if( m_Connection.isNull() )
	{
		throw exceptions::PersistenceException( basar::ExceptInfo( context, "Connection is NULL!", __FILE__, line ) );
	}
}

void Connection::checkOpenOrThrow( const char * context, const basar::Int32 line ) const
{
	if( !m_Connection.isOpen() )
	{
		throw exceptions::PersistenceException( basar::ExceptInfo( context, "Connection isn't open!", __FILE__, line ) );
	}
}

} // end namespace persistence
} // end namespace libcsc


