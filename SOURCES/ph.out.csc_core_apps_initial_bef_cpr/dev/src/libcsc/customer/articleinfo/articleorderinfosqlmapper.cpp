#include <customer/articleinfo/articleorderinfosqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace customer {

ArticleOrderInfoSqlMapper::ArticleOrderInfoSqlMapper(ArticleOrderInfoPtr articleOrderInfo, const basar::db::sql::ResultsetRef resultSet) :
    ArticleOrderInfoMapperBase(articleOrderInfo),
    m_ResultSet(resultSet)
{
}

ArticleOrderInfoSqlMapper::~ArticleOrderInfoSqlMapper()
{
}

const basar::VarString ArticleOrderInfoSqlMapper::getSelectSQL(const basar::Int16 branchNo, const basar::Int32 articleNo)
{
    basar::Date today;
    std::stringstream sql;
    sql
        << "SELECT first 1 bk.datum_bestell, bk.datum_we_soll, bk.best_wirksam "
        << "FROM cscbeskopf bk "
        << "INNER JOIN cscbesposi bp ON bk.bestell_nr = bp.bestell_nr and bk.filialnr = bp.filialnr "
        << "WHERE bp.filialnr = " << branchNo << " "
        << "  AND (bk.status_akt = 'A' or (bk.status_akt = 'a' and bk.status_neu = 'Y') or bk.datum_we = " << today.getDate() << ") "
        << "  AND bp.artikel_nr = " << articleNo << " "
        << "ORDER BY bk.datum_we_soll";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

void ArticleOrderInfoSqlMapper::doMap()
{
    const basar::VarString ValueSet = "1";

    if (m_ResultSet.isNull())
    {
        throw;
    }
    setArticleOrderDate(m_ResultSet.getInt32("datum_bestell"));
    setArticleGoodsReceiptTargetDate(m_ResultSet.getInt32("datum_we_soll"));
    setIsArticleOrderEffective(m_ResultSet.getString("best_wirksam") == ValueSet);
}

} // end namespace customer
} // end namespace libcsc
