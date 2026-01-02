#include "fmdrelevantdm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/fmdrelevantcalculator_loggerpool.h>
#include "domainmodule/fmdrelevantcalculator_property_definitions.h"
#include "domainmodule/fmdrelevantdm_definitions.h"

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmdarticle {

//-----------------------------------------------------------------------------------------
	
FmdRelevantDM::FmdRelevantDM(const log4cplus::Logger& logger) :
	m_ProviderAvailable(NONE),
	m_Logger(logger), m_SqlSelectArticleData (""),
	m_SqlPrepUpdateFmdRelevant (""), m_SqlPrepInsertFmdRelevant (""), m_BranchNo (0),
	m_CounterUpdate(0), m_CounterUnchanged(0)
{

}

FmdRelevantDM::~FmdRelevantDM()
{
	if( false == m_ArticleResultSet.isNull() )
	{
		if( m_ArticleResultSet.isOpen() )
			m_ArticleResultSet.close();
		
		m_ArticleResultSet.reset();
	}

	if( false == m_StmtSelect.isNull() )
	{
		if( m_StmtSelect.isOpen() )
			m_StmtSelect.close();
		
		m_StmtSelect.reset();
	}

	if( false == m_PrepStmtUpdate.isNull() )
	{
		if( m_PrepStmtUpdate.isOpen() )
			m_PrepStmtUpdate.close();
		
		m_PrepStmtUpdate.reset();
	}

	if( false == m_PrepStmtInsert.isNull() )
	{
		if( m_PrepStmtInsert.isOpen() )
			m_PrepStmtInsert.close();
		
		m_PrepStmtInsert.reset();
	}
}

void FmdRelevantDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
{
	m_Connection = conn->getCurrentConnection().getSqlConnection();
}

bool FmdRelevantDM::existsIfaTable()
{
	return m_ProviderAvailable == IFA || m_ProviderAvailable == IFA_AND_DC;
}

bool FmdRelevantDM::existsDcTable()
{
	return m_ProviderAvailable == DATACARE || m_ProviderAvailable == IFA_AND_DC;
}

void FmdRelevantDM::createPreparedStmtUpd	( )
{
	if( m_PrepStmtUpdate.isNull() || false == m_PrepStmtUpdate.isOpen() )
	{
		m_SqlPrepUpdateFmdRelevant = "UPDATE zartikel SET fmd_relevant = ?, datum_aender = TO_CHAR(CURRENT,'%Y%m%d')::INTEGER, bearbeiter = 'fmdrelca', chargenartikel = ? "
									 "WHERE artikel_nr = ? ";

		m_PrepStmtUpdate = m_Connection.createPreparedStatement(m_SqlPrepUpdateFmdRelevant);

		std::stringstream ss;
		ss << "prepared UPDATE stmt <" << m_SqlPrepUpdateFmdRelevant.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

void FmdRelevantDM::createPreparedStmtIns	( )
{
	if( m_PrepStmtInsert.isNull() || false == m_PrepStmtInsert.isOpen() )
	{
		m_SqlPrepInsertFmdRelevant = "INSERT INTO zapflege (artikel_nr, datum) VALUES ( ?, TO_CHAR(CURRENT,'%Y%m%d')::INTEGER) ";
		
		m_PrepStmtInsert = m_Connection.createPreparedStatement(m_SqlPrepInsertFmdRelevant);

		std::stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertFmdRelevant.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

bool  FmdRelevantDM::next(  )
{
	if (true == m_ArticleResultSet.isNull() || false == m_ArticleResultSet.isOpen() )
		return false;
	
	return m_ArticleResultSet.next();
}


void FmdRelevantDM::find(  )
{
	basar::VarString sqlSelectExistance;
	basar::db::sql::StatementRef stmtIfaExists = m_Connection.createStatement();
	basar::db::sql::ResultsetRef existsIfaResultSet 
		//= stmtIfaExists.executeQuery("Select tabname from systables s where s.tabname = 'zifaoart'");
		= stmtIfaExists.executeQuery("Select colname from syscolumns where tabid = (select tabid from systables s where s.tabname = 'zifaoart') and colname = 'a11verihoc'");

	if (existsIfaResultSet.next())
	{
		m_ProviderAvailable = IFA;
	}

	basar::db::sql::StatementRef stmtDcExists = m_Connection.createStatement();
	basar::db::sql::ResultsetRef existsDcResultSet
		//= stmtIfaExists.executeQuery("Select tabname from systables s where s.tabname = 'zdcoart'");
		= stmtIfaExists.executeQuery("Select colname from syscolumns where tabid = (select tabid from systables s where s.tabname = 'zdcoart') and colname = 'dc_faelschsicher'");

	if (existsDcResultSet.next())
	{
		if (existsIfaTable())
			m_ProviderAvailable = IFA_AND_DC;
		else
			m_ProviderAvailable = DATACARE;
	}

	stmtDcExists.close();
	stmtDcExists.reset();
	
	existsDcResultSet.close();
	existsDcResultSet.reset();
	
	stmtIfaExists.close();
	stmtIfaExists.reset();

	existsIfaResultSet.close();
	existsIfaResultSet.reset();

	findArticleMasterData();
}

void FmdRelevantDM::findArticleMasterData()
{
	m_SqlSelectArticleData.format(
		"SELECT "
		"z.artikel_nr AS %s, "
		"z.arzneimittel AS %s, "
		"z.rezeptpfl AS %s, "
		"z.tierarznei AS %s, "
		"z.HOMOEOPATHIKUM AS %s, "
		"z.MEDIZINISCHE_GASE AS %s, "
		"z.fmd_relevant AS %s, "
		"z.chargenartikel AS %s, "
		"CAST(NVL(excep.exceptiontype, -1) as smallint) AS %s, "
		"NVL(ac.article_code, '') AS %s, ",
		properties::ARTICLE_NO.getName().c_str(),
		properties::ARZNEIMITTEL.getName().c_str(),
		properties::REZEPTPFL.getName().c_str(),
		properties::TIERARZNEI.getName().c_str(),
		properties::HOMOEOPATHIKUM.getName().c_str(),
		properties::MEDIZINISCHE_GASE.getName().c_str(),
		properties::FMD_RELEVANT.getName().c_str(),
		properties::BATCH_ARTICLE.getName().c_str(),
		properties::EXCEPTION_TYPE.getName().c_str(),
		properties::ATC_CODE.getName().c_str());

	basar::VarString sql = "";

	if (existsIfaTable())
	{
		sql.format( "CAST(NVL(ifa.a11verihoc, -1) as integer) AS %s, ",
					properties::IFA_FMD_VAL.getName().c_str());
	}
	else
	{
		sql.format( "CAST('-1' as integer) AS %s, ",
					properties::IFA_FMD_VAL.getName().c_str());
	}

	m_SqlSelectArticleData.append(sql);

	if (existsDcTable())
	{
		sql.format( "CAST(NVL(dc.dc_faelschsicher, -1) as smallint) AS %s ",
					properties::DC_FMD_VAL.getName().c_str());
	}
	else
	{
		sql.format( "CAST('-1' as smallint) AS %s ", 
					properties::DC_FMD_VAL.getName().c_str());
	}

	m_SqlSelectArticleData.append(sql);

	m_SqlSelectArticleData.append(
		"FROM zartikel z "
		"left outer join fmdexceptionarticles excep on z.artikel_nr = excep.articleno "
		"left outer join carticlecodes ac on z.artikel_nr = ac.articleno and ac.code_type = 2 ");

	if (existsIfaTable())
	{
		m_SqlSelectArticleData.append("left outer join Zifaoart ifa on z.artikel_nr = ifa.a00pzn ");
	}
	
	if (existsDcTable())
	{
		m_SqlSelectArticleData.append("left outer join zdcoart dc on z.artikel_nr = dc.dc_artikel_nr ");
	}

	m_SqlSelectArticleData.append(	
#ifndef NDEBUG
		"where z.artikel_nr >= 1 and z.artikel_nr <= 5049 "
#endif
		"ORDER BY z.artikel_nr ");

	m_StmtSelect = m_Connection.createStatement();
	m_ArticleResultSet = m_StmtSelect.executeQuery(m_SqlSelectArticleData);
	BLOG_DEBUG(m_Logger, m_SqlSelectArticleData.c_str());
}

void FmdRelevantDM::save(const basar::Int32 articleNo, const basar::Int16 isFmdRelevant)
{
	METHODNAME_DEF(FmdArticleDM, saveIfNew)
	BLOG_TRACE_METHOD(getLogger(), fun);

	std::stringstream ss;
	ss << " for ARTICLENO <" << articleNo << "> ";
	
	if (getArticleData().getInt16(properties::FMD_RELEVANT) != isFmdRelevant)
	{
		basar::VarString batchFlag = getArticleData().getString(properties::BATCH_ARTICLE);

		// activated with start of FMD
		if (isFmdRelevant > 0 && batchFlag == "0")
		{
			batchFlag = "1";
			ss << "chargenartikel updated to <" << batchFlag.c_str() << ">, ";
		}
		
		createPreparedStmtUpd();

		m_PrepStmtUpdate.setInt16(0, isFmdRelevant);
		m_PrepStmtUpdate.setString(1, batchFlag.c_str()); 
		m_PrepStmtUpdate.setInt32(2, articleNo);
		
		m_PrepStmtUpdate.execute();
		
		ss << "fmd_relevant updated to <" << isFmdRelevant << ">";
		++m_CounterUpdate;
		BLOG_DEBUG(m_Logger, ss.str());

		saveZapflege(articleNo);
	}
	else
	{
		ss << "fmd_relevant unchanged <" << isFmdRelevant << ">";;
		BLOG_DEBUG(m_Logger, ss.str());
		++m_CounterUnchanged;
	}
}

void FmdRelevantDM::saveZapflege(const basar::Int32 articleNo)
{
	createPreparedStmtIns();

	m_PrepStmtInsert.setInt32(0, articleNo);
				
	m_PrepStmtInsert.execute(false); // no exception due to -239

/*	no logging for zapflege necessary:
	std::stringstream ss;
	ss << " for ARTICLENO <" << articleNo;
	ss << "> new zapflege record inserted";
	BLOG_DEBUG(m_Logger, ss.str());
*/
}

void FmdRelevantDM::setBranchNo(const basar::Int16 branchNo)
{
	m_BranchNo = branchNo;

	std::stringstream ss;
	ss << " branchno set to <" << m_BranchNo << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

basar::Int16 FmdRelevantDM::getBranchNo( )
{
	return m_BranchNo;
}

const basar::db::sql::ResultsetRef FmdRelevantDM::getArticleData	()
{
	return m_ArticleResultSet;
}

const log4cplus::Logger& FmdRelevantDM::getLogger() const
{
	return m_Logger;
}

basar::Int32	FmdRelevantDM::getCounterUpdate	( )
{
	return m_CounterUpdate;
}

basar::Int32	FmdRelevantDM::getCounterUnchanged	( )
{
	return m_CounterUnchanged;
}
	
//-----------------------------------------------------------------------------------------
} 
} 
} 
