#ifndef GUARD_DOMMOD_BULK_INSERTER_H
#define GUARD_DOMMOD_BULK_INSERTER_H

#include "ibulkinserter.h"
#include <libbasar_definitions.h>
#include <libbasardbsql_connectionref.h>
#include <log4cplus/logger.h>

namespace domMod 
{		
namespace util
{
class BulkInserter : public IBulkInserter
{
public:
	static const basar::Int32 DEFAULT_COUNT_BUFFER = 100;
	static const basar::Int32 MAX_COUNT_BYTES = 30000;

	BulkInserter( 
		const basar::db::sql::ConnectionRef connection,
		log4cplus::Logger & logger,
		const basar::Int32 maxCountBufferStatements = DEFAULT_COUNT_BUFFER,
		const basar::Int32 maxCountBytes = MAX_COUNT_BYTES
			); 
	virtual ~BulkInserter(); 

	virtual void init();
	virtual void insert(
		const basar::VarString & sql
			);
	virtual void finish();

private:
	BulkInserter( const BulkInserter & );
	BulkInserter & operator=( const BulkInserter & );																				

	void cleanUp();
	void execute(
		const basar::VarString & sql 
			);
	void logSQL(
		const basar::VarString & sql 
			);
	void logExecuteResult(
		const basar::db::sql::ExecuteReturnInfo & executeResult
			);

	basar::db::sql::ConnectionRef	m_Connection;
	log4cplus::Logger &				m_Logger;
	const basar::Int32				m_MaxCountBufferStatements;
	const basar::Int32				m_MaxCountBytes;
	basar::Int32					m_CountBufferStatements;
	basar::VarString				m_BulkSQL;
}; 

} // namespace util
} // namespace domMod

#endif // GUARD_DOMMOD_BULK_INSERTER_H

