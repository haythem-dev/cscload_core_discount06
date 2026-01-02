#include "bulkrangeselector.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace stockbooking
{
BulkRangeSelector::BulkRangeSelector()
{
}

BulkRangeSelector::~BulkRangeSelector()
{
	m_SelectAccessor.reset();
}

void BulkRangeSelector::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

void BulkRangeSelector::bulkRangeAvailability(
	const basar::Int16 localBranchNo,
	const basar::VarString& articleCodeFrom,
	const basar::VarString& articleCodeTo,
	std::vector<std::string>& returnArticles
	) const
{
	try
	{
		std::stringstream sql;

		sql << 	
			"SELECT "
				"MAX(CASE al_fil.artikelaktiv WHEN '1' THEN al_fil.bestand ELSE 0 END) + "	// Bestand im eigenen VZ
				"SUM(NVL(al_ibt.bestand,0)), "												// Verbundbestand
				"ac.article_code "
			"FROM ibtbranches i "
				"join artikellokal al_fil on al_fil.filialnr = i.branchno "					// Join für eigene Filiale
				"join articlecodes ac on ac.articleno = al_fil.artikel_nr and ac.preferred_flag = 1 "
				"left join ibtbrancharticleconfig c on c.branchno = i.branchno and c.ibttypeid = i.nlevelibttypeid and "
					"c.ibtassortmenttypeid = i.nlevelibtassortmenttypeid and c.articleno = ac.articleno "
				"left join artikellokal al_ibt on al_ibt.artikel_nr = c.articleno and al_ibt.filialnr = i.ibtbranchno "	// Join für Verbundfilialen
			"WHERE i.branchno=" << localBranchNo << " and i.active_flag = 1 and ac.article_code >= " << articleCodeFrom <<" and ac.article_code <= " << articleCodeTo << " "
			"GROUP BY ac.article_code "
			"HAVING MAX(CASE al_fil.artikelaktiv WHEN '1' THEN al_fil.bestand ELSE 0 END) + SUM(NVL(al_ibt.bestand,0)) > 0 ";

		BLOG_TRACE(LoggerPool::getLoggerStockBooking(), sql.str());

		basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select(sql.str());
		while (true == resultset.next())
		{
			returnArticles.push_back(resultset.getString("article_code"));
		}
	}
	catch(...)
	{
	}
}

void BulkRangeSelector::bulkRangeStock(
	const basar::Int16 localBranchNo,
	const basar::VarString& articleCodeFrom,
	const basar::VarString& articleCodeTo,
	std::vector<ReturnArticles>& returnArticles,
	bool getExpiryDate
) const
{
	try
	{
		std::stringstream sql;
		sql <<
			"SELECT "
			"al.artikel_nr, "
			"al.bestand, "
			"ac.article_code ";
		if (true == getExpiryDate)
		{
			sql <<
				", NVL(ao.datumverfall, 0)::INTEGER AS datumverfall ";
		}
		sql <<
			"FROM artikellokal al "
			"JOIN articlecodes ac ON ac.articleno = al.artikel_nr AND ac.preferred_flag = 1 ";
		if (true == getExpiryDate)
		{
			sql <<
				"LEFT OUTER JOIN artikellagerort ao ON ao.artikel_nr = al.artikel_nr "
				"AND ao.filialnr = al.filialnr ";
		}
		sql <<
			"WHERE "
			"al.filialnr = " << localBranchNo << " AND "
			"ac.article_code >= " << articleCodeFrom << " AND "
			"ac.article_code <= " << articleCodeTo << " ";

		basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select(sql.str());
		while (true == resultset.next())
		{
			ReturnArticles r;
			r.ArticleCode_ = resultset.getString("article_code");
			r.Quantity_ = resultset.getInt32("bestand");
			if (true == getExpiryDate)
			{
				r.ExpiryDate_ = resultset.getInt32("datumverfall");
			}
			returnArticles.push_back(r);
		}
	}
	catch (...)
	{
	}
}

// Bulk range stock from ArticleCharge table
// Serbia only!
void BulkRangeSelector::bulkRangeStockAC(
	const basar::Int16 localBranchNo,
	const basar::VarString& articleCodeFrom,
	const basar::VarString& articleCodeTo,
	std::vector<ReturnArticles>& returnArticles,
	bool getExpiryDate
) const
{
	try
	{
		std::stringstream sql;

		sql <<
			"SELECT DISTINCT articleno, stock, chargennr, article_code ";
			if (true == getExpiryDate)
			{
				sql <<
					", expirydate ";
			}
			sql << " FROM("
				"SELECT al.artikel_nr as articleno, al.bestand as stock, ac.article_code, ";
				if (true == getExpiryDate)
				{
					sql <<
						"NVL(artc.expirydate, 0)::INTEGER AS expirydate, ";
				}
			sql << "artc.chargennr as chargennr, "
					"RANK() OVER(PARTITION BY al.artikel_nr ORDER BY artc.expirydate ASC, artc.chargennr ASC) as rank "
					"FROM artikellokal al "
					"JOIN articlecodes ac ON ac.articleno = al.artikel_nr AND ac.preferred_flag = 1 "
					"LEFT OUTER JOIN articlecharge artc ON artc.articleno = al.artikel_nr "
					"AND artc.branchno = al.filialnr "
					"WHERE al.filialnr = " << localBranchNo << " AND "
					"ac.article_code >= " << articleCodeFrom << " AND "
					"ac.article_code <= " << articleCodeTo << ") as result "
					"where rank = 1";

		basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select(sql.str());
		while (true == resultset.next())
		{
			ReturnArticles r;
			r.ArticleCode_ = resultset.getString("article_code");
			r.Quantity_ = resultset.getInt32("stock");
			r.Batch_ = resultset.getString("chargennr");
			if (true == getExpiryDate)
			{
				r.ExpiryDate_ = resultset.getInt32("expirydate");
			}
			returnArticles.push_back(r);
		}
	}
	catch (...)
	{
	}
}

} // end namespace stockbooking
} // end namespace libcsc
