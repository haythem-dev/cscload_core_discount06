#ifndef GUARD_DOMMOD_IBTARTICLE_IBTARTICLEDM_H
#define GUARD_DOMMOD_IBTARTICLE_IBTARTICLEDM_H

//-----------------------------------------------------------------------------------------

#include "iibtarticledm.h"
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

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtArticle {

//-----------------------------------------------------------------------------------------

class IbtArticleDM : public IIbtArticleDM
{
public:
	IbtArticleDM(const log4cplus::Logger& logger);
	~IbtArticleDM();

	virtual void												injectDbConnection	( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );
	
	virtual void                                                find				( );
	virtual basar::Int32										findDemand			( const basar::Int32 articleNo, basar::Int32 weeksToConsider );
	virtual bool												next				( );
	virtual void												saveRelevanceFlag(const basar::Int32 articleNo, const basar::Int32 assortmentType, basar::Int16 relvanceflag);
	virtual void												save				( const basar::Int32 articleNo, const bool isIbtRelevant, const basar::Int32 assortmentType );
	virtual void                                                deleteUnknownConfig	( );

	virtual void												setChangeUser		( const basar::VarString & changeUser );
	virtual void												setBranchNo			( const basar::Int16 branchNo );

	virtual const basar::db::sql::ResultsetRef					getArticleData		( );
	virtual basar::Int32										getCounterUpdate	( );
	virtual basar::Int32										getCounterInsert	( );
	virtual basar::Int32										getCounterUnchanged	( );


private:
	IbtArticleDM( const IbtArticleDM & );
	IbtArticleDM & operator = ( const IbtArticleDM & );

	const log4cplus::Logger&									getLogger() const;

	void														createPreparedStmtUpd	( );
	void														createPreparedStmtIns	( );
	void														createPreparedStmtSelDemand ( basar::Int32 weeksToConsider );

	basar::Int32												getAssortmentType	( );
	basar::Int16												getIbtRelevantFlag	( );
	basar::Int16												calcIbtRelevantFlag	( const bool isIbtRelevant );
	const basar::I18nString										sumStringDemand		( basar::Int32 weeksToConsider );
		
	const log4cplus::Logger&									m_Logger;
	basar::db::sql::ConnectionRef								m_Connection;

	basar::VarString											m_SqlSelectArticleData;
	basar::VarString											m_SqlPrepSelectDemand;
	basar::VarString											m_SqlPrepUpdateIbtBranchArticleConfig;
	basar::VarString											m_SqlPrepInsertIbtBranchArticleConfig;

	basar::db::sql::StatementRef								m_StmtSelect;
	basar::db::sql::PreparedStatementRef						m_PrepStmtUpdate;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsert;
	basar::db::sql::PreparedStatementRef						m_PrepStmtSelDemand;	

	basar::VarString											m_ChangeUser;
	basar::Int16												m_BranchNo;

	basar::Int32												m_CounterUpdate;
	basar::Int32												m_CounterInsert;
	basar::Int32												m_CounterUnchanged;

	basar::db::sql::ResultsetRef								m_ArticleResultSet;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_IBTARTICLE_IBTARTICLEDM_H

//-----------------------------------------------------------------------------------------

