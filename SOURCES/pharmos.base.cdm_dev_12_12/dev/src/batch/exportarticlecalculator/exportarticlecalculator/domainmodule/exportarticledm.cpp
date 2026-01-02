#include "exportarticledm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/exportarticlecalculator_loggerpool.h>
#include "domainmodule/exportarticlecalculator_property_definitions.h"
#include "domainmodule/exportarticledm_definitions.h"

//-----------------------------------------------------------------------------------------

namespace exportarticlecalculator {
namespace domMod {
namespace exportarticle {

//-----------------------------------------------------------------------------------------
	
ExportArticleDM::ExportArticleDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_SqlSelectArticleData (""),
	m_SqlPrepUpdateExportArticle (""), m_SqlPrepInsertExportArticle (""), m_Country (""), m_BranchNo (0), m_DateFrom (0),
	m_CounterUpdate(0), m_CounterInsert(0), m_CounterUnchanged(0)
{

}

ExportArticleDM::~ExportArticleDM()
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

void ExportArticleDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
{
	m_Connection = conn->getCurrentConnection().getSqlConnection();
}

void ExportArticleDM::createPreparedStmtUpd	( )
{
	if( m_PrepStmtUpdate.isNull() || false == m_PrepStmtUpdate.isOpen() )
	{
		m_SqlPrepUpdateExportArticle.format(" UPDATE cexportarticle SET exportpermissionflag = ?, lastpermissionchange = CURRENT "
														"WHERE country_ifacode = '%s' AND articleno = ? ",
														m_Country.c_str());

		m_PrepStmtUpdate = m_Connection.createPreparedStatement(m_SqlPrepUpdateExportArticle);

		std::stringstream ss;
		ss << "prepared UPDATE stmt <" << m_SqlPrepUpdateExportArticle.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

void ExportArticleDM::createPreparedStmtIns	( )
{
	if( m_PrepStmtInsert.isNull() || false == m_PrepStmtInsert.isOpen() )
	{
		m_SqlPrepInsertExportArticle.format(" INSERT INTO cexportarticle (country_ifacode, articleno, exportpermissionflag, lastpermissionchange) VALUES "
														"( '%s', ?, ?, CURRENT) ",
														m_Country.c_str());

		m_PrepStmtInsert = m_Connection.createPreparedStatement(m_SqlPrepInsertExportArticle);

		std::stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertExportArticle.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}


bool  ExportArticleDM::next(  )
{
	if (true == m_ArticleResultSet.isNull() || false == m_ArticleResultSet.isOpen() )
		return false;
	
	return m_ArticleResultSet.next();
}


void ExportArticleDM::find(  )
{

	m_SqlSelectArticleData.format( 
		"SELECT z.artikel_nr AS %s, "
				"f.filialnr AS %s, "
				"z.btm AS %s, "
				"z.g_un_nr AS %s, "
				"z.meldepfl AS %s, "
				"z.kuehlartikel AS %s, "
				"z.explosivgrundstoff AS %s, "
				"z.psychotrop AS %s, "
				"z.tierarznei AS %s, "
				"z.artikel_gesperrt AS %s, "
				"z.arzneimittel AS %s, "
				"z.datum_ah AS %s, "
				"z.datum_av AS %s, "
				"z.vertrbind AS %s, "
				"z.vertrbind_ifa AS %s, "
				"z.prismaewoche AS %s, "
				"z.biozid_verord AS %s, "
				"z.homoeopathikum AS %s, "
				"z.anthroposophikum AS %s, "
				"f.artikelaktiv AS %s, "
				"f.lagerfachnr AS %s, "
				"NVL(c.article_code, '') AS %s, "
				"cast(NVL(b.imex_mode, 0) as smallint) AS %s, " 
				"cast(NVL((select narcotic_substance_flag from catccode a where a.code_atc = c.article_code), 0) as smallint) AS %s, "
				"cast((z.gs_explosion + z.gs_hochentz + z.gs_umwelt + z.gs_reizend + z.gs_aetzend + z.gs_sehrgiftig + z.gs_leichtentz + z.gs_giftig + z.gs_gesundhsch + z.gs_brand) as smallint) AS %s, "
				"cast(NVL(s.pictogram01_flag, 0) + NVL(s.pictogram02_flag, 0) + NVL(s.pictogram03_flag, 0) + NVL(s.pictogram04_flag, 0) + NVL(s.pictogram05_flag, 0) + "
					 "NVL(s.pictogram06_flag, 0) + NVL(s.pictogram07_flag, 0) + NVL(s.pictogram08_flag, 0) + NVL(s.pictogram09_flag, 0) as smallint) AS %s, "
				"cast(NVL(e.exportpermissionflag, -1) as smallint) AS %s "
		"FROM zartikel z, artikelf f, OUTER carticlecodes c, OUTER cexportarticle e, OUTER cimexblock b, OUTER csafetydatasheet s "
		"WHERE f.filialnr = %d " // exportierende Filiale
			"and z.artikel_nr = f.artikel_nr "
			"and z.artikel_nr = c.articleno and c.code_type = 2 " // ATC
			"and z.artikel_nr = e.articleno and e.country_ifacode = '%s' " // importierendes Land
			"and z.artikel_nr = b.articleno and b.country_ifacode = '%s' " // importierendes Land
			"and z.artikel_nr = s.articleno "
			//"and z.artikel_nr in (428117, 447646, 2387) "
			"ORDER BY z.artikel_nr"
			,

			properties::ARTICLE_NO.getName().c_str(),
			properties::BRANCH_NO.getName().c_str(),
			properties::NARCOTIC_FLAG.getName().c_str(),
			properties::UN_NO.getName().c_str(),
			properties::NOTIFIABLE_FLAG.getName().c_str(),
			properties::COOL_ARTICLE_MODE.getName().c_str(),
			properties::EXPLOSION_FLAG.getName().c_str(),
			properties::PSYCHOTROPIC_FLAG.getName().c_str(),
			properties::ANIMAL_MEDICINE_FLAG.getName().c_str(),
			properties::ARTICLE_LOCKED_FLAG.getName().c_str(),
			properties::MEDICINE_FLAG.getName().c_str(),
			properties::OUTSALE_DATE.getName().c_str(),
			properties::EXPIRY_DATE.getName().c_str(),
			properties::DISTRIBUTION_BINDING_MODE.getName().c_str(),
			properties::DISTRIBUTION_BINDING_IFA.getName().c_str(),
			properties::PRISMAE_NO.getName().c_str(),
			properties::BIOZID_FLAG.getName().c_str(),	
			properties::HOMEOPATHY_FLAG.getName().c_str(),	
			properties::ANTHROPOSOPHIC_FLAG.getName().c_str(),	
			properties::ACTIVE_ARTICLE_FLAG.getName().c_str(),
			properties::STORAGE_LOCATION.getName().c_str(),
			properties::ATC_CODE.getName().c_str(),
			properties::EXPORT_BLOCK_FLAG.getName().c_str(),
			properties::NARCOTIC_SUBSTANCE_FLAG.getName().c_str(),
			properties::HAZARDOUS_SUBSTANCE_OLD.getName().c_str(),
			properties::HAZARDOUS_SUBSTANCE_NEW.getName().c_str(),
			properties::EXPORTPERMISSION_FLAG.getName().c_str(),
			m_BranchNo,
			m_Country.c_str(),
			m_Country.c_str());

	m_StmtSelect = m_Connection.createStatement();

	m_ArticleResultSet = m_StmtSelect.executeQuery(m_SqlSelectArticleData);

	BLOG_DEBUG( m_Logger, m_SqlSelectArticleData.c_str() );
}

void ExportArticleDM::save(const basar::Int32 articleNo, const bool isExportExcluded)
{
	METHODNAME_DEF( ExportArticleDM, save )
	BLOG_TRACE_METHOD( getLogger(), fun );

	std::stringstream ss;
	ss << " for ARTICLENO <" << articleNo;

	
	if ( getExportPermissionFlag() < domMod::exportarticle::FLAG_OFF && isExportExcluded == false) // no former entry = only INSERT, if export is permitted!
	{
		createPreparedStmtIns();

		m_PrepStmtInsert.setInt32(0, articleNo);
		m_PrepStmtInsert.setInt16(1, calcExportPermissionFlag(isExportExcluded));
				
		m_PrepStmtInsert.execute();

		ss << "> new export permisson entry inserted.";
		++m_CounterInsert;
	}
	else if ( getExportPermissionFlag() >= domMod::exportarticle::FLAG_OFF &&
			  calcExportPermissionFlag(isExportExcluded) != getExportPermissionFlag()) // UPDATE only if flag- value is changing
	{
		createPreparedStmtUpd();

		m_PrepStmtUpdate.setInt16(0, calcExportPermissionFlag(isExportExcluded));
		m_PrepStmtUpdate.setInt32(1, articleNo);
		
		m_PrepStmtUpdate.execute();

		ss << "> export permission updated to <" << !isExportExcluded << ">";
		++m_CounterUpdate;
	}
	else
	{
		// unchanged
		ss << "> export permission remaining unchanged <" << !isExportExcluded << ">";
		++m_CounterUnchanged;
	}

	BLOG_DEBUG( m_Logger, ss.str() );
}

void ExportArticleDM::markChangedArticles	( )
{
	basar::VarString sqlUpdateChangedArticles;
	
	sqlUpdateChangedArticles.format(	"UPDATE cexportarticle SET lastarticlechange = CURRENT WHERE country_ifacode = '%s' and exportpermissionflag = 1 and (articleno IN "
										"(SELECT artikel_nr from zapflege where datum >= %ld) OR articleno IN (SELECT artikel_nr from zpznpflege where datum >= %ld))",
										m_Country.c_str(), m_DateFrom, m_DateFrom );

	basar::db::sql::StatementRef stmtUpdate = m_Connection.createStatement();

	basar::db::sql::ExecuteReturnInfo ret = stmtUpdate.execute(sqlUpdateChangedArticles);

	std::stringstream ss;
	ss << ret.getAffectedRows() << " article changes marked for export permissons by <" << sqlUpdateChangedArticles.c_str() << ">";
	BLOG_INFO( m_Logger, ss.str() );

	stmtUpdate.close();
	stmtUpdate.reset();
}

void ExportArticleDM::setCountry(const basar::VarString & country)
{
	m_Country = country;

	std::stringstream ss;
	ss << " country set to <" << m_Country.c_str() << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

void ExportArticleDM::setBranchNo(const basar::Int16 branchNo)
{
	m_BranchNo = branchNo;

	std::stringstream ss;
	ss << " branchno set to <" << m_BranchNo << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

void ExportArticleDM::setDateFrom(const basar::Int32 dateFrom)
{
	m_DateFrom = dateFrom;

	std::stringstream ss;
	ss << " datefrom set to <" << m_DateFrom << ">";
	BLOG_INFO( m_Logger, ss.str() );
}


basar::Int16	ExportArticleDM::calcExportPermissionFlag	( const bool isExportExcluded )
{
	if (isExportExcluded)
		return domMod::exportarticle::FLAG_OFF;
	else 
		return domMod::exportarticle::FLAG_ON;
}

basar::Int16	ExportArticleDM::getExportPermissionFlag()
{
	return m_ArticleResultSet.getInt16(properties::EXPORTPERMISSION_FLAG);
}

const basar::db::sql::ResultsetRef ExportArticleDM::getArticleData	()
{
	return m_ArticleResultSet;
}

const log4cplus::Logger& ExportArticleDM::getLogger() const
{
	return m_Logger;
}

basar::Int32	ExportArticleDM::getCounterUpdate	( )
{
	return m_CounterUpdate;
}

basar::Int32	ExportArticleDM::getCounterInsert	( )
{
	return m_CounterInsert;
}

basar::Int32	ExportArticleDM::getCounterUnchanged	( )
{
	return m_CounterUnchanged;
}
	
//-----------------------------------------------------------------------------------------
} 
} 
} 
