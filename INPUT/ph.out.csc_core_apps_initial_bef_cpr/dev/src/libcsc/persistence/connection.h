#ifndef GUARD_LIBCSC_PERSISTENCE_CONNECTION_H
#define GUARD_LIBCSC_PERSISTENCE_CONNECTION_H

#include <libbasardbsql_connectionref.h>

namespace libcsc
{
namespace persistence
{
class Connection
{
public:
	Connection();
    explicit Connection( basar::db::sql::ConnectionRef );
	~Connection();
	
	void open( const basar::VarString & dbserver, const basar::VarString & database );
	void close();

	void beginTransaction();
	void commitTransaction();
	void rollbackTransaction();

	void setExplainOn();
	void setExplainOff();
	void setIsolationLevel(const basar::IsolationLevelEnum eLevel,				//!< transaction isolation level
						   const bool					   retainLocks = false	//!< only for Informix:\n true : RETAIN UPDATE LOCKS for SELECT ... FOR UPDATE \n false: no retain
						  );

	bool inTransaction() const;
	basar::db::sql::ConnectionRef getDbSqlConnection() const;

private:
	void checkNotNullOrThrow( const char * context, const basar::Int32 line ) const;
	void checkOpenOrThrow( const char * context, const basar::Int32 line ) const;

	basar::db::sql::ConnectionRef	m_Connection;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_CONNECTION_H
