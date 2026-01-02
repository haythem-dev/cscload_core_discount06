#ifndef GUARD_DOMMOD_EXPORTARTICLE_EXPORTARTICLEDM_H
#define GUARD_DOMMOD_EXPORTARTICLE_EXPORTARTICLEDM_H

//-----------------------------------------------------------------------------------------

#include "iexportarticledm.h"
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

namespace exportarticlecalculator {
namespace domMod {
namespace exportarticle {

//-----------------------------------------------------------------------------------------

class ExportArticleDM : public IExportArticleDM
{
public:
	ExportArticleDM(const log4cplus::Logger& logger);
	~ExportArticleDM();

	virtual void												injectDbConnection	( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );
	
	virtual void                                                find				( );
	virtual bool												next				( );
	virtual void												save				( const basar::Int32 articleNo, const bool isExportExcluded );
	virtual void                                                markChangedArticles	( );
	
	virtual void												setCountry			( const basar::VarString & country );
	virtual void												setBranchNo			( const basar::Int16 branchNo );
	virtual void												setDateFrom			( const basar::Int32 dateFrom );

	virtual const basar::db::sql::ResultsetRef					getArticleData		( );
	virtual basar::Int32										getCounterUpdate	( );
	virtual basar::Int32										getCounterInsert	( );
	virtual basar::Int32										getCounterUnchanged	( );


private:
	ExportArticleDM( const ExportArticleDM & );
	ExportArticleDM & operator = ( const ExportArticleDM & );

	const log4cplus::Logger&									getLogger() const;

	void														createPreparedStmtUpd	( );
	void														createPreparedStmtIns	( );
	
	basar::Int16												getExportPermissionFlag	( );
	basar::Int16												calcExportPermissionFlag( const bool isExportExcluded );
		
	const log4cplus::Logger&									m_Logger;
	basar::db::sql::ConnectionRef								m_Connection;

	basar::VarString											m_SqlSelectArticleData;
	basar::VarString											m_SqlPrepUpdateExportArticle;
	basar::VarString											m_SqlPrepInsertExportArticle;

	basar::db::sql::StatementRef								m_StmtSelect;
	basar::db::sql::PreparedStatementRef						m_PrepStmtUpdate;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsert;
	
	basar::VarString											m_Country;
	basar::Int16												m_BranchNo;
	basar::Int32												m_DateFrom;

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

#endif // GUARD_DOMMOD_EXPORTARTICLE_EXPORTARTICLEDM_H

//-----------------------------------------------------------------------------------------

