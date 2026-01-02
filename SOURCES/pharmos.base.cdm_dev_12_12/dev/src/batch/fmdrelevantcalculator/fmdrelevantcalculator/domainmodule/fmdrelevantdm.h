#ifndef GUARD_DOMMOD_FMDRELEVANT_FMDRELEVANTDM_H
#define GUARD_DOMMOD_FMDRELEVANT_FMDRELEVANTDM_H

//-----------------------------------------------------------------------------------------

#include "ifmdrelevantdm.h"
#include <libutil/dbconnection.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_statementref.h>
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_connectionref.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmdarticle {

//-----------------------------------------------------------------------------------------

class FmdRelevantDM : public IFmdRelevantDM
{
public:
	FmdRelevantDM(const log4cplus::Logger& logger);
	~FmdRelevantDM();

	virtual void												injectDbConnection	( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );
	
	virtual void                                                find				( );
	virtual bool												next				( );
	virtual void												save			( const basar::Int32 articleNo, const basar::Int16 isFmdRelevant );
	
	virtual void												setBranchNo			( const basar::Int16 branchNo );
	virtual basar::Int16										getBranchNo();

	virtual const basar::db::sql::ResultsetRef					getArticleData		( );
	virtual basar::Int32										getCounterUpdate	( );
	virtual basar::Int32										getCounterUnchanged	( );



private:
	FmdRelevantDM( const FmdRelevantDM & );
	FmdRelevantDM & operator = ( const FmdRelevantDM & );

	const log4cplus::Logger&									getLogger() const;

	void														saveZapflege(const basar::Int32 articleNo);

	void														createPreparedStmtUpd	( );
	void														createPreparedStmtIns	( );

	void														findArticleMasterData();
	bool														existsIfaTable();
	bool														existsDcTable();

	enum ProviderAvailable
	{
		NONE = -1,
		IFA = 0,
		DATACARE = 1,
		IFA_AND_DC = 2
	};
	ProviderAvailable m_ProviderAvailable;
		
	const log4cplus::Logger&									m_Logger;
	basar::db::sql::ConnectionRef								m_Connection;

	basar::VarString											m_SqlSelectArticleData;
	basar::VarString											m_SqlPrepUpdateFmdRelevant;
	basar::VarString											m_SqlPrepInsertFmdRelevant;

	basar::db::sql::StatementRef								m_StmtSelect;
	basar::db::sql::PreparedStatementRef						m_PrepStmtUpdate;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsert;
	
	basar::Int16												m_BranchNo;

	basar::Int32												m_CounterUpdate;
	basar::Int32												m_CounterUnchanged;

	basar::db::sql::ResultsetRef								m_ArticleResultSet;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_FMDRELEVANT_FMDRELEVANTDM_H

//-----------------------------------------------------------------------------------------

