#ifndef GUARD_DOMMOD_LOADCONTRACTSHR_LOADCONTRACTSHRDM_H
#define GUARD_DOMMOD_LOADCONTRACTSHR_LOADCONTRACTSHRDM_H

//-----------------------------------------------------------------------------------------

#include "iloadcontractshrdm.h"
#include <libutil/dbconnection.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_statementref.h>
#include <libbasardbsql_resultsetref.h>
#include <libbasardbsql_connectionref.h>

using namespace std;
//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace loadcontractshr {
namespace domMod {
namespace loadcontractshrdm {

//-----------------------------------------------------------------------------------------

class LoadContractsHrDM : public ILoadContractsHrDM
{
public:
	LoadContractsHrDM(const log4cplus::Logger& logger);
	~LoadContractsHrDM();

	virtual void												injectDbConnection	( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );

	virtual bool												next				( );
	virtual void                                                run					( );

	virtual void												setMode(const basar::VarString path);
	virtual basar::VarString									getMode();

	virtual void												setPath			( const basar::VarString path );
	virtual basar::VarString									getPath();

	virtual basar::Int32										getCounterRebatesUpdated();
	virtual basar::Int32										getCounterRebatesAdded	( );
	virtual basar::Int32										getCounterContractsAdded ( );
	virtual basar::Int32										getCounterRebatesUnchanged	( );
	virtual basar::Int32										getCounterRebatesUnchangedOutOfDate ( );
	virtual basar::Int32										getCounterRebatesUnchangedSimilar();
	virtual basar::Int32										getCounter();
	virtual basar::Int32										getCounterBadFormat();
	virtual  std::stringstream*									getResult(ResultGrp grp);

private:
	LoadContractsHrDM( const LoadContractsHrDM & );
	LoadContractsHrDM & operator = ( const LoadContractsHrDM & );

	const log4cplus::Logger&									getLogger() const;

	void														createPreparedStmtUpdRebate	( );
	void														createPreparedStmtInsContract  ( );
	void														createPreparedStmtInsZgrppflege( );
	void														createPreparedStmtInsRebate  ( );

	bool														rebateExists(const string& pzn, const string& pharmacyGrpId, const string& dateTo);
	bool														matchExists(const string& pzn, const string& pharmacyGrpId, const string& dateTo);
	bool														checkBadContractNo(const string& contractNo, std::vector<int>& pos);
	int															getNoFromDb(const string& contractNo);
	const string												ConvertDate(const string& date);
	int															getContractId(list< pair<string, int> >& contracts, const string& contractNo);
	int															getNoFromContractsList(list< pair<string, int> >& contracts, const string& contractNo);
	int															createNewContract(const string& contractNo);
	int															getDbInitialVars(int* currentDate);
	void														addRebate(const string& pzn, int contId, const string& dateFrom, const string& dateTo, const string& purchaseGrp, const string& price);
	void														updateRebate(const string& pzn, const string& pharmacyGrpId, const string& dateTo, int contId);
	void														addToGrp(ResultGrp grp, const string& line);
		
	const log4cplus::Logger&									m_Logger;
	basar::db::sql::ConnectionRef								m_Connection;

	basar::VarString											m_SqlSelectArticleData;
	basar::VarString											m_SqlPrepUpdateLoadContractsHr;
	basar::VarString											m_SqlPrepInsertLoadContractsHr;
	basar::VarString											m_SqlPrepUpdateRebates;
	basar::VarString											m_SqlPrepInsertGrpPfl;

	basar::db::sql::StatementRef								m_StmtSelect;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsertContract;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsertGrpPfl;
	basar::db::sql::PreparedStatementRef						m_PrepStmtInsertRebate;
	basar::db::sql::PreparedStatementRef						m_PrepStmtUpdateRebate;

	
	basar::VarString											m_Path;
	basar::VarString											m_Mode;
	string														m_CurrentContractNo;
	string														m_CurrentPzn; 
	string														m_CurrentPharmacyGrpId; 
	string														m_CurrentDateFrom; 
	string														m_CurrentDateTo; 
	string														m_CurrentPrice; 
	string														m_CurrentPromo;

	basar::Int32												m_CounterContractsAdded;
	basar::Int32												m_CounterRebatesUpdated;
	basar::Int32												m_CounterRebatesAdded;
	basar::Int32												m_CounterRebatesUnchanged; 
	basar::Int32												m_CounterRebatesUnchangedSimilar;
	basar::Int32												m_CounterRebatesUnchangedOutOfDate;
	basar::Int32												m_Counter;
	basar::Int32												m_CounterBadFormat;
	basar::Int32												m_NewId;

	std::stringstream m_ssBADFORMAT;
	std::stringstream m_ssOUTOFDATE;
	std::stringstream m_ssDOES_NOT_EXIST;
	std::stringstream m_ssMATCHING_EXISTS;
	std::stringstream m_ssSIMILAR_EXISTS;
	std::stringstream m_ssUPDATED;
	std::stringstream m_ssNO_MATCHING_FOUND;
	std::stringstream m_ssINSERTED;

	basar::db::sql::ResultsetRef								m_ArticleResultSet;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_LOADCONTRACTSHR_LOADCONTRACTSHRDM_H

//-----------------------------------------------------------------------------------------

