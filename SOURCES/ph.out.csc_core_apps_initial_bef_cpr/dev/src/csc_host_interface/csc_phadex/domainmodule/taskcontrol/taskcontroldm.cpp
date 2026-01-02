#include "taskcontroldm.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libbasardbsql_connectionref.h>
#include <libbasardbsql_statementref.h>
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_exceptions.h>
#include <libbasarcmnutil_datetimetools.h>

namespace csc_phadex
{
namespace domMod
{

TaskControlDM::TaskControlDM()
: m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
	METHODNAME_DEF( TaskControlDM, TaskControlDM )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

TaskControlDM::~TaskControlDM()
{
	METHODNAME_DEF( TaskControlDM, ~TaskControlDM )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void TaskControlDM::injectConnection( const basar::db::sql::ConnectionRef connection )
{
	METHODNAME_DEF( TaskControlDM, injectConnection )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_Connection = connection;
}

void TaskControlDM::setConfig( const basar::Int16 branchno, const basar::VarString & applicationName )
{
	m_Branchno = branchno;
	m_ApplicationName = applicationName;

	using namespace basar::db::sql;
	basar::Int32 seconds = 0;
	std::stringstream sql;
	sql << "SELECT wert FROM parameter WHERE (filialnr = " << m_Branchno << ") AND (programmname = '" << m_ApplicationName.c_str() << "') AND (zweck='TASKCONTROL')";
	StatementRef statement = m_Connection.createStatement();
	ResultsetRef resultset = statement.executeQuery( sql.str().c_str() );
	if( resultset.next() )
	{
		seconds = 40 * resultset.getInt32( "wert" ); // see info_zbw
	}

	if( 0 == seconds )
	{
		seconds = 120;
	}

	m_MaxTimeout = seconds * 7 / 10;
}

void TaskControlDM::heartBeat( const basar::Int16 branchno, const basar::VarString & applicationName )
{
	METHODNAME_DEF( TaskControlDM, heartBeat )
	BLOG_TRACE_METHOD( m_Logger, fun );

	setConfig( branchno, applicationName );
	heartBeat();
}

void TaskControlDM::heartBeat()
{
	METHODNAME_DEF( TaskControlDM, heartBeat )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool skipHeartBeat = true;
	static basar::DateTime lastHeartBeat( basar::DateTime::getCurrent() );
	basar::DateTime current( basar::DateTime::getCurrent() );
	if( lastHeartBeat.getDate() != current.getDate() )
	{
		skipHeartBeat = false;
	}
	else
	{
		using namespace basar::cmnutil;
		basar::Int32 elapsed = DateTimeTools::getUnixTimestampFromDateTime( current ) - DateTimeTools::getUnixTimestampFromDateTime( lastHeartBeat );
		if( elapsed > m_MaxTimeout )
		{
			skipHeartBeat = false;
		}
	}

	if( skipHeartBeat )
	{
		return;
	}

	using namespace basar::db::sql;
	if( m_Connection.isInTransaction() )
	{
		static basar::VarString reason( "db connection is in transaction already" );
		throw basar::cmnutil::BasarException( basar::cmnutil::ExceptionInfoStruct( fun, reason, __FILE__, __LINE__ ), "AlreadyInTransactionException" );
	}

	m_Connection.begin();
	StatementRef statement = m_Connection.createStatement();
	std::stringstream sql;
	sql << "UPDATE taskcontrol SET zeitunix = dbinfo('utc_current') "
		   "WHERE (vertriebszentrumnr = " << m_Branchno << ") AND (programmname = '" << m_ApplicationName.c_str() << "')";

	ExecuteReturnInfo ret = statement.execute( sql.str().c_str(), false );
	if( ret.hasError() )
	{
		m_Connection.rollback();
		std::stringstream reason;
		reason << "Error executing sql: <" << ret.getError() << "> on " << sql.str().c_str();
		throw basar::cmnutil::BasarException( basar::cmnutil::ExceptionInfoStruct( fun, reason.str().c_str(), __FILE__, __LINE__ ), "DBException" );
	}

	if(	0 == ret.getAffectedRows() )
	{
		sql.str( "" );
		sql << "INSERT INTO taskcontrol (vertriebszentrumnr, zeitunix, programmname) "
			   "VALUES (" << m_Branchno << ", dbinfo('utc_current'), '" << m_ApplicationName.c_str() << "') ";
		ret = statement.execute( sql.str().c_str(), false );
		if( ret.hasError() )
		{
			m_Connection.rollback();
			std::stringstream reason;
			reason << "Error executing sql: <" << ret.getError() << "> on " << sql.str().c_str();
			throw basar::cmnutil::BasarException( basar::cmnutil::ExceptionInfoStruct( fun, reason.str().c_str(), __FILE__, __LINE__ ), "DBException" );
		}	
	}

	m_Connection.commit();
	lastHeartBeat = basar::DateTime::getCurrent();
}

} // end namespace domMod
} // end namespace csc_phadex
