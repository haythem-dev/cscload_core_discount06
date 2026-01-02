#include "ibtarticledm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/ibtrelevantcalculator_loggerpool.h>
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"
#include "domainmodule/ibtarticledm_definitions.h"

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtArticle {

//-----------------------------------------------------------------------------------------
	
IbtArticleDM::IbtArticleDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_SqlSelectArticleData (""), m_SqlPrepSelectDemand (""), 
	m_SqlPrepUpdateIbtBranchArticleConfig (""), m_SqlPrepInsertIbtBranchArticleConfig (""), m_ChangeUser (""), m_BranchNo (0),
	m_CounterUpdate(0), m_CounterInsert(0), m_CounterUnchanged(0)
{

}

IbtArticleDM::~IbtArticleDM()
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

	if( false == m_PrepStmtSelDemand.isNull() )
	{
		if( m_PrepStmtSelDemand.isOpen() )
			m_PrepStmtSelDemand.close();
		
		m_PrepStmtSelDemand.reset();
	}
}

void IbtArticleDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
{
	m_Connection = conn->getCurrentConnection().getSqlConnection();
}

void IbtArticleDM::createPreparedStmtUpd	( )
{
	if( m_PrepStmtUpdate.isNull() || false == m_PrepStmtUpdate.isOpen() )
	{
		m_SqlPrepUpdateIbtBranchArticleConfig.format(" UPDATE puibtbrancharticleconfig SET relevanceflag = ?, assortmenttypeid = ?, lastchangedate = CURRENT, userlastchange = '%s' "
														"WHERE branchno = %d AND articleno = ? ",
														m_ChangeUser.c_str(), m_BranchNo);

		m_PrepStmtUpdate = m_Connection.createPreparedStatement(m_SqlPrepUpdateIbtBranchArticleConfig);

		std::stringstream ss;
		ss << "prepared UPDATE stmt <" << m_SqlPrepUpdateIbtBranchArticleConfig.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

void IbtArticleDM::createPreparedStmtIns	( )
{
	if( m_PrepStmtInsert.isNull() || false == m_PrepStmtInsert.isOpen() )
	{
		m_SqlPrepInsertIbtBranchArticleConfig.format(" INSERT INTO puibtbrancharticleconfig (branchno, articleno, relevanceflag, assortmenttypeid, lastchangedate, userlastchange) VALUES "
														"( %d, ?, ?, ?, CURRENT, '%s') ",
														m_BranchNo, m_ChangeUser.c_str());

		m_PrepStmtInsert = m_Connection.createPreparedStatement(m_SqlPrepInsertIbtBranchArticleConfig);

		std::stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertIbtBranchArticleConfig.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

const basar::I18nString IbtArticleDM::sumStringDemand(basar::Int32 weeksToConsider)
{
	basar::I18nString result;
	basar::I18nString yearType("uj_");
  	basar::I18nString formatWeek;

//------
	basar::Int16 currentWeek = basar::cmnutil::Date::getCurrent().getWeekOfYear();
	basar::Int16 currentYear = basar::cmnutil::Date::getCurrent().getYear();
		
	if ( currentWeek									== 1		&& 
		 basar::cmnutil::Date::getCurrent().getMonth()	== 12		)
		++currentYear;

	if ( basar::cmnutil::Date::getCurrent().getMonth()	== 1		&& 
		 currentWeek	>= 52)
		--currentYear;
//------

	if (!(currentYear %2)) 
		yearType.format("gj_");
	
	result.format("(%s%02d", yearType.c_str(), currentWeek);
  
	for (; weeksToConsider > 1; --weeksToConsider)
	{
		--currentWeek;
		if ( 0 == currentWeek) 
		{
			currentWeek = 53;
			if ( "uj_" == yearType)
				yearType = "gj_";
			else
				yearType = "uj_";
		}
		
		formatWeek.format("%02d", currentWeek);
		result +=  " + " + yearType + formatWeek; 
	}

	result += ")";

	return result;
}

/* TH prepared stmt for selecting "Artikeltourismus"- Daten
SELECT 
besposi.artikel_nr, 
zartikel.apothekenpfl, -- otc
zartikel.rezeptpfl, -- rx
besposi.preis_aktuell, Sum(besposi.menge_bestell), Sum(besposi.menge_zaehl), 
Sum(besposi.menge_bestell*besposi.preis_aktuell), Sum(besposi.menge_zaehl*besposi.preis_aktuell), Sum(besposi.menge_bestell-besposi.menge_zaehl), 
Sum(besposi.menge_bestell*besposi.preis_aktuell-besposi.menge_zaehl*besposi.preis_aktuell)
FROM informix.beskopf beskopf, informix.besposi besposi, 
--informix.bliefer bliefer, join wg original-hersteller 
informix.zartikel zartikel
WHERE besposi.bestell_nr = beskopf.bestell_nr AND besposi.filialnr = beskopf.filialnr AND zartikel.artikel_nr = besposi.artikel_nr 
AND ((besposi.datum_we>=20170101 And besposi.datum_we<=20170125) AND (besposi.best_wirksam=1) AND (beskopf.status_akt='D'))
And besposi.artikel_nr = 1126111
GROUP BY besposi.artikel_nr, zartikel.apothekenpfl, zartikel.rezeptpfl,  besposi.preis_aktuell, beskopf.status_akt
HAVING (Sum(besposi.menge_bestell-besposi.menge_zaehl)>=100) or (Sum(besposi.menge_bestell*besposi.preis_aktuell-besposi.menge_zaehl*besposi.preis_aktuell)>=500)
*/


void IbtArticleDM::createPreparedStmtSelDemand	( basar::Int32 weeksToConsider )
{
	if( m_PrepStmtSelDemand.isNull() || false == m_PrepStmtSelDemand.isOpen() )
	{
		m_SqlPrepSelectDemand = "SELECT FIRST 1 NVL((SELECT (";
		
		basar::I18nString whereCond;
		whereCond.format("WHERE artikel_nr = ? AND filialnr = %d", m_BranchNo);
		
		m_SqlPrepSelectDemand.append(sumStringDemand(weeksToConsider).c_str());
		m_SqlPrepSelectDemand.append(") FROM nachfw ");
		m_SqlPrepSelectDemand.append(whereCond.c_str());

		m_SqlPrepSelectDemand.append("), 0) + NVL((SELECT (");
		m_SqlPrepSelectDemand.append(sumStringDemand(weeksToConsider).c_str());
		m_SqlPrepSelectDemand.append(") FROM defektw ");
		m_SqlPrepSelectDemand.append(whereCond.c_str());

		m_SqlPrepSelectDemand.append(") ,0) AS " + properties::NUM_OF_DEMAND.getName() + " FROM nachfw");
		
		m_PrepStmtSelDemand = m_Connection.createPreparedStatement(m_SqlPrepSelectDemand);

		std::stringstream ss;
		ss << "prepared DEMAND stmt <" << m_SqlPrepSelectDemand.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

bool  IbtArticleDM::next(  )
{
	if (true == m_ArticleResultSet.isNull() || false == m_ArticleResultSet.isOpen() )
		return false;
	
	return m_ArticleResultSet.next();
}

basar::Int32	IbtArticleDM::findDemand			( const basar::Int32 articleNo, const basar::Int32 weeksToConsider )
{
	createPreparedStmtSelDemand(weeksToConsider);

	m_PrepStmtSelDemand.setInt32(0, articleNo);
	m_PrepStmtSelDemand.setInt32(1, articleNo);
		
	basar::db::sql::ResultsetRef res = m_PrepStmtSelDemand.executeSingleQuery();

	if (!res.next())
		return 0;

	return res.getDecimal(properties::NUM_OF_DEMAND.getName()).toInt32();
}

void IbtArticleDM::deleteUnknownConfig	( )
{
	basar::VarString sqlDeleteUnknownConfig;
	
	sqlDeleteUnknownConfig.format(	"DELETE FROM puibtbrancharticleconfig c WHERE branchno = %d and articleno NOT IN "
										"(SELECT artikel_nr from artikelf where filialnr = c.branchno)",
										m_BranchNo );

	basar::db::sql::StatementRef stmtDelete = m_Connection.createStatement();

	basar::db::sql::ExecuteReturnInfo ret = stmtDelete.execute(sqlDeleteUnknownConfig);

	std::stringstream ss;
	ss << ret.getAffectedRows() << " config-rows deleted by <" << sqlDeleteUnknownConfig.c_str() << ">";
	BLOG_INFO( m_Logger, ss.str() );

	stmtDelete.close();
	stmtDelete.reset();
}


void IbtArticleDM::find(  )
{
	m_SqlSelectArticleData.format( 
		"SELECT z.artikel_nr AS %s, "
				"cast(NVL(ibt.isfixedregional, 2) as smallint) AS %s, "
				"f.filialnr AS %s, "
				"z.btm AS %s, "
				"z.g_un_nr AS %s, "
				"z.konsig_partner_nr AS %s, "
				"NVL(w1.warengruppe, '') AS %s, "
				"NVL(w2.warengruppe, '') AS %s, "
				"NVL(w3.warengruppe, '') AS %s, "
				"NVL(w4.warengruppe, '') AS %s, "
				"f.lagerfachnr AS %s, "
				"NVL(p.aep, 0.0) AS %s, "
				"z.kuehlartikel AS %s, "
				"z.verbundsperre AS %s, "
				"z.chargenartikel AS %s, "
				"z.privatsortiment AS %s, "
				"z.artikel_gesperrt AS %s, "
				"z.zentr_eksperre AS %s, "
				"z.datum_ah AS %s, "
				"f.abc_artikel AS %s, "
				"cast((z.gs_explosion + z.gs_hochentz + z.gs_umwelt + z.gs_reizend + z.gs_aetzend + z.gs_sehrgiftig + z.gs_leichtentz + z.gs_giftig + z.gs_gesundhsch + z.gs_brand) as smallint) AS %s, "
				"cast(NVL(s.pictogram01_flag, 0) + NVL(s.pictogram02_flag, 0) + NVL(s.pictogram03_flag, 0) + NVL(s.pictogram04_flag, 0) + NVL(s.pictogram05_flag, 0) + "
					 "NVL(s.pictogram06_flag, 0) + NVL(s.pictogram07_flag, 0) + NVL(s.pictogram08_flag, 0) + NVL(s.pictogram09_flag, 0) as smallint) AS %s, "
				"cast(NVL(c.assortmenttypeid, 0) as integer) AS %s, "
				"cast(NVL(c.relevanceflag, -1) as smallint) AS %s "
		"FROM zartikel z, artikelf f, OUTER zartwg w1, OUTER zartwg w2, OUTER zartwg w3, OUTER zartwg w4, OUTER zartpreis p, OUTER puibtbrancharticleconfig c, OUTER csafetydatasheet s, OUTER cibt ibt "
		"WHERE f.filialnr = %d "
			"and z.artikel_nr = f.artikel_nr "
			"and z.artikel_nr = s.articleno "
			"and w1.artikel_nr = z.artikel_nr and w1.art = '5' "
			"and w2.artikel_nr = z.artikel_nr and w2.art = 'A' "
			"and w3.artikel_nr = z.artikel_nr and w3.art = 'G' "
			"and w4.artikel_nr = z.artikel_nr and w4.art = 'D' "
			"and c.branchno = f.filialnr and f.artikel_nr = c.articleno "
			"and p.artikel_nr = z.artikel_nr and z.artikel_nr = ibt.articleno and p.datumgueltigab = "
			"(select max(datumgueltigab) from zartpreis p2 where p2.artikel_nr = p.artikel_nr "
			"and datumgueltigab <= cast(to_char(current, '%%Y%%m%%d') as integer)) "
			// "and z.artikel_nr in (78597, 112, 78605, 106, 432478) "
			,

			properties::ARTICLE_NO.getName().c_str(),
			properties::FIXREGIONAL.getName().c_str(),
			properties::BRANCH_NO.getName().c_str(),
			properties::NARCOTIC_FLAG.getName().c_str(),
			properties::UN_NO.getName().c_str(),
			properties::CONSIGNMENT_PARTNER_NO.getName().c_str(),
			properties::SEASON_GROUP_1.getName().c_str(),
			properties::SEASON_GROUP_2.getName().c_str(),
			properties::SEASON_GROUP_3.getName().c_str(),
			properties::SPECIAL_ARTICLE_TYPE.getName().c_str(),
			properties::STORAGE_LOCATION.getName().c_str(),
			properties::PURCHASING_PRICE.getName().c_str(),
			properties::COOL_ARTICLE_MODE.getName().c_str(),
			properties::IBT_EXCLUDE_FLAG.getName().c_str(),
			properties::BATCH_FLAG.getName().c_str(),			
			properties::PRIVATE_GOODS_TYPE.getName().c_str(),
			properties::ARTICLE_LOCKED_FLAG.getName().c_str(),
			properties::CENTR_PU_ART_LOCKED_FLAG.getName().c_str(),
			properties::OUTSALE_DATE.getName().c_str(),
			properties::ABC_CATEGORY.getName().c_str(),
			properties::HAZARDOUS_SUBSTANCE_OLD.getName().c_str(),
			properties::HAZARDOUS_SUBSTANCE_NEW.getName().c_str(),
			properties::ASSORTMENT_TYPE.getName().c_str(),
			properties::RELEVANCE_FLAG.getName().c_str(),
			m_BranchNo );

	m_StmtSelect = m_Connection.createStatement();

	m_ArticleResultSet = m_StmtSelect.executeQuery(m_SqlSelectArticleData);

	BLOG_DEBUG( m_Logger, m_SqlSelectArticleData.c_str() );
}

void IbtArticleDM::saveRelevanceFlag(const basar::Int32 articleNo, const basar::Int32 assortmentType, basar::Int16 relvanceflag)
{
	METHODNAME_DEF( IbtArticleDM, saveRelevanceFlag )
	BLOG_TRACE_METHOD( getLogger(), fun );

	std::stringstream ss;
	ss << " saveRelevanceFlag for ARTICLENO <" << articleNo;

	if ( getIbtRelevantFlag() < domMod::ibtarticledm::FLAG_OFF ) // no former entry = INSERT
	{
		createPreparedStmtIns();

		m_PrepStmtInsert.setInt32(0, articleNo);
		m_PrepStmtInsert.setInt16(1, 1);
		m_PrepStmtInsert.setInt32(2, assortmentType);
		
		m_PrepStmtInsert.execute();

		ss << "> inserting new ibt relevant entry <1> and assortmenttype <" << assortmentType << "> inserted.";
		++m_CounterInsert;
	}
	else
	{
		createPreparedStmtUpd();

		m_PrepStmtUpdate.setInt16(0, relvanceflag);
		m_PrepStmtUpdate.setInt32(1, assortmentType);
		m_PrepStmtUpdate.setInt32(2, articleNo);
		
		m_PrepStmtUpdate.execute();

		ss << "> Updating the ibt relevance flag = < " << relvanceflag << " > and assortmenttype updated to < " << assortmentType << ">";
		++m_CounterUpdate;
	}
	
	BLOG_DEBUG( m_Logger, ss.str() );
}

void IbtArticleDM::save(const basar::Int32 articleNo, const bool isIbtRelevant, const basar::Int32 assortmentType)
{
	METHODNAME_DEF( IbtArticleDM, save )
	BLOG_TRACE_METHOD( getLogger(), fun );

	std::stringstream ss;
	ss << " Save for ARTICLENO <" << articleNo;

	if ( getIbtRelevantFlag() < domMod::ibtarticledm::FLAG_OFF ) // no former entry = INSERT
	{
		createPreparedStmtIns();

		m_PrepStmtInsert.setInt32(0, articleNo);
		m_PrepStmtInsert.setInt16(1, calcIbtRelevantFlag(isIbtRelevant));
		m_PrepStmtInsert.setInt32(2, assortmentType);
		
		m_PrepStmtInsert.execute();

		ss << "> new ibt relevant entry <" << isIbtRelevant << ">, assortmenttype <" << assortmentType << "> inserted.";
		++m_CounterInsert;
	}
	else if ( calcIbtRelevantFlag(isIbtRelevant) != getIbtRelevantFlag() ||
			  assortmentType					 != getAssortmentType()	) // UPDATE only if flag- values are changing
	{
		createPreparedStmtUpd();

		m_PrepStmtUpdate.setInt16(0, calcIbtRelevantFlag(isIbtRelevant));
		m_PrepStmtUpdate.setInt32(1, assortmentType);
		m_PrepStmtUpdate.setInt32(2, articleNo);
		
		m_PrepStmtUpdate.execute();

		ss << "> ibt relevance flag / assortmenttype updated to <" << isIbtRelevant << "> / <" << assortmentType << ">";
		++m_CounterUpdate;
	}
	else
	{
		// unchanged
		ss << "> ibt relevance flag / assortmenttype remaining unchanged <" << isIbtRelevant << "> / <" << assortmentType << ">";
		++m_CounterUnchanged;
	}

	BLOG_DEBUG( m_Logger, ss.str() );
}

void IbtArticleDM::setChangeUser(const basar::VarString & changeUser)
{
	m_ChangeUser = changeUser;

	std::stringstream ss;
	ss << " username set to <" << m_ChangeUser.c_str() << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

void IbtArticleDM::setBranchNo(const basar::Int16 branchNo)
{
	m_BranchNo = branchNo;

	std::stringstream ss;
	ss << " branchno set to <" << m_BranchNo << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

basar::Int16	IbtArticleDM::calcIbtRelevantFlag	( const bool isIbtRelevant )
{
	if (isIbtRelevant)
		return domMod::ibtarticledm::FLAG_ON;
	else 
		return domMod::ibtarticledm::FLAG_OFF;
}

basar::Int32	IbtArticleDM::getAssortmentType	( )
{
	return m_ArticleResultSet.getInt32(properties::ASSORTMENT_TYPE);
}

basar::Int16	IbtArticleDM::getIbtRelevantFlag()
{
	return m_ArticleResultSet.getInt16(properties::RELEVANCE_FLAG);
}

const basar::db::sql::ResultsetRef IbtArticleDM::getArticleData	()
{
	return m_ArticleResultSet;
}

const log4cplus::Logger& IbtArticleDM::getLogger() const
{
	return m_Logger;
}

basar::Int32	IbtArticleDM::getCounterUpdate	( )
{
	return m_CounterUpdate;
}

basar::Int32	IbtArticleDM::getCounterInsert	( )
{
	return m_CounterInsert;
}

basar::Int32	IbtArticleDM::getCounterUnchanged	( )
{
	return m_CounterUnchanged;
}
	
//-----------------------------------------------------------------------------------------
} 
} 
} 
