#include "bulkinserter.h"
#include <libbasardbsql_statementref.h>
#include <sstream>
//#include <libbasardbsql_insertsetref.h>

namespace domMod 
{		
namespace util
{
BulkInserter::BulkInserter( 
	const basar::db::sql::ConnectionRef connection,
	log4cplus::Logger & logger,
	const basar::Int32 maxCountBufferStatements,	// = DEFAULT_COUNT_BUFFER
	const basar::Int32 maxCountBytes				// = MAX_COUNT_BYTES
		)
: m_Connection( connection ),
  m_Logger( logger ),
  m_MaxCountBufferStatements( maxCountBufferStatements ),
  m_MaxCountBytes( maxCountBytes ),
  m_CountBufferStatements( 0 )
{
}

BulkInserter::~BulkInserter()
{
	//! \todo throw if there are INSERTs left?
}

void BulkInserter::init()
{
	cleanUp();
}

void BulkInserter::insert(
	const basar::VarString & sql
		)
{
	++m_CountBufferStatements;
	std::stringstream ss;
	ss << m_BulkSQL.c_str() << ( 0 == m_BulkSQL.length() ? "" : "\n" ) << sql.c_str();
	basar::VarString tempSQL( ss.str().c_str() );
	if( m_MaxCountBytes <= static_cast< basar::Int32>( tempSQL.length() ) )
	{
		// sql is getting too long, execute now
		execute( m_BulkSQL );
		m_CountBufferStatements = 1;
		m_BulkSQL = sql;
		return;
	}

	if( m_MaxCountBufferStatements == m_CountBufferStatements )
	{
		// max count of insert statements reached, execute now
		execute( tempSQL );
		cleanUp();
		return;
	}

	m_BulkSQL = tempSQL;
}

void BulkInserter::finish()
{
	if( 0 < m_BulkSQL.length() )
	{
		execute( m_BulkSQL );
	}

	cleanUp();
}

void BulkInserter::cleanUp()
{
	m_BulkSQL = "";
	m_CountBufferStatements = 0;
}

void BulkInserter::execute(
	const basar::VarString & sql 
		)
{
	logSQL( sql );
	using namespace basar::db::sql;
	StatementRef statement = m_Connection.createStatement();
	ExecuteReturnInfo ret = statement.execute( sql );
	logExecuteResult( ret ); 

	// not sure if execute() will do the job, alternative:
	//InsertsetRef insert = statement.executeInsert( sql );
	//basar::UInt32 rows = insert.flushRows();
}

void BulkInserter::logSQL(
	const basar::VarString & sql 
		)
{
    if( m_Logger.isEnabledFor( log4cplus::DEBUG_LOG_LEVEL ) )
	{
        std::stringstream ss;
        ss << "Collected " << m_CountBufferStatements << " INSERT statements, bulk SQL:" << std::endl << sql;
        m_Logger.forcedLog( log4cplus::DEBUG_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }
}

void BulkInserter::logExecuteResult(
	const basar::db::sql::ExecuteReturnInfo & executeResult
		)
{
    if( m_Logger.isEnabledFor( log4cplus::DEBUG_LOG_LEVEL ) )
	{
        std::stringstream ss;
		ss << "Execute result: ";
		if( executeResult.hasError() )
		{
			ss << "ERROR<" << executeResult.getError();
		}
		else
		{
			ss << "SUCCESS, " << static_cast<basar::Int32>( executeResult.getAffectedRows() ) << " rows inserted";
		}

		m_Logger.forcedLog( log4cplus::DEBUG_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }
}

} // namespace util
} // namespace domMod