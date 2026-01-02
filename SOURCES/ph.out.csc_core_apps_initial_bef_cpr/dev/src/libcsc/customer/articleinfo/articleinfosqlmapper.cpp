#include <customer/articleinfo/articleinfosqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace customer {

ArticleInfoSqlMapper::ArticleInfoSqlMapper(ArticleInfoPtr articleInfo, const basar::db::sql::ResultsetRef resultSet) :
    ArticleInfoMapperBase(articleInfo),
    m_ResultSet(resultSet),
    m_BitNumberNarcoticInEtartklasse1(10),
    m_BitNumberColdchainInEtartschalter1(6)
{
}

ArticleInfoSqlMapper::~ArticleInfoSqlMapper()
{
}

const basar::VarString ArticleInfoSqlMapper::getSelectSQL(const basar::Int16 branchNo, const basar::Int32 articleNo)
{
    std::stringstream sql;
    sql << "SELECT "
                "az.artikel_nr AS articleno, "
                "az.artikel_name AS name, "
                "az.artikel_langname AS alternatename, "
                "az.positivliste AS positivelist, "
                "az.artikel_gesperrt AS blockedflag, "
                "az.datum_anlage AS creationdate, "
                "az.datum_aender AS changedate, "
                "al.filialnr AS branchno, "
                "al.artikelaktiv AS activeflag, "
                "ac.article_code AS ean, "
                "ma.name AS manufacturername, "
                "tr.salestaxrate AS vatpercentage, "
                "ap.preisekapo AS baseprice, "
                "CAST(nvl(az.etartschalter1,0) + nvl(al.etartschalter1,0) AS INTEGER) AS coldchainarticle, "
                "az.etartklasse1 AS etartklasse1, "
                "az.datum_lieferbar_ab AS availablefrom, "
                "az.kontingent_ppe AS quotappe "
            "FROM artikelzentral az "
                "JOIN artikellokal al ON az.artikel_nr = al.artikel_nr "
                "LEFT OUTER JOIN articlecodes ac ON al.artikel_nr = ac.articleno AND ac.code_type = 13 "
                "LEFT OUTER JOIN manufacturer ma ON az.hersteller_nr = ma.hersteller_nr "
                "LEFT OUTER JOIN taxrates tr ON tr.taxlevel = az.taxlevel "
                "LEFT OUTER JOIN artikelpreis ap ON ap.artikel_nr = al.artikel_nr "
            "WHERE al.filialnr = " << branchNo << " ";
    if (articleNo > 0)
    {
        sql <<  "AND az.artikel_nr = " << articleNo << " ";
    }
    sql << "ORDER BY az.artikel_nr";
    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

void ArticleInfoSqlMapper::doMap()
{
    if( m_ResultSet.isNull() )
    {
        throw;
    }

    setBranchNo                 (m_ResultSet.getInt16("branchno"));
    setArticleNo                (m_ResultSet.getInt32("articleno"));
    setEAN                      (m_ResultSet.getString("ean"));
    setName                     (m_ResultSet.getString("name"));
    setAlternateName            (m_ResultSet.getString("alternatename"));
    setManufacturerName         (m_ResultSet.getString("manufacturername"));
    setBasePrice                (m_ResultSet.getDecimal("baseprice"));
    setVatPercentage            (m_ResultSet.getDecimal("vatpercentage"));
    setPositiveList             (m_ResultSet.getString("positivelist") == basar::VarString("1"));
    setActiveFlag               (m_ResultSet.getString("activeflag") == basar::VarString("1"));
    setBlockedFlag              (m_ResultSet.getString("blockedflag") == basar::VarString("1"));
    setCreationDate             (basar::Date(m_ResultSet.getInt32("creationdate")));
    setChangeDate               (basar::Date(m_ResultSet.getInt32("changedate")));
    setAvailableFrom            (basar::Date(m_ResultSet.getInt32("availablefrom")));
    //Check if 6th bit in etartschalter1 is set, in case it is set it is a coldchainarticle
    setColdChainFlag            ( (m_ResultSet.getInt32("coldchainarticle")) & (1 << (m_BitNumberColdchainInEtartschalter1 - 1)) );
    //Check if 10th bit in etartklasse1 is set, in case it is set it is a narcotic
    setNarcoticFlag             ( (m_ResultSet.getInt32("etartklasse1")) & (1 << (m_BitNumberNarcoticInEtartklasse1-1)) );
    setQuotaPPE                 (m_ResultSet.getString("quotappe") == basar::VarString("1"));
}


const basar::VarString ArticleInfoSqlMapper::getSelectArtInfoTextSQL(const basar::Int32 articleNo)
{
    std::stringstream sql;
    sql << "SELECT "
                "ARTICLENO, "
                "ARTINFOTYPE, "
                "SEQUENCENO, "
                "INFOTEXT "
            "FROM "
                "ARTINFOTEXT "
            "WHERE "
                "ARTICLENO = " << articleNo << " "
            "ORDER BY "
                "SEQUENCENO";
    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}


void ArticleInfoSqlMapper::doMapArtInfoText()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }
    appendArtInfoText(m_ResultSet.getString("infotext"));
}

const basar::VarString ArticleInfoSqlMapper::getSelectArticleNosByPeriodSQL(const basar::Int16 branchNo, basar::Int32 positionsPerPage,
    const basar::Int32 articleNoFrom, const basar::Int32 dateFrom, const basar::Int32 dateTo, ArticleInquiryPeriodDateTypeEnum dateType)
{
    // +1 to also get the beginning element of the next page
    ++positionsPerPage;

    std::stringstream azCondition;
    switch (dateType)
    {
    case Creation:
        azCondition << "az.datum_anlage BETWEEN " << dateFrom << " AND " << dateTo;
        break;
    case Change:
        azCondition << "az.datum_aender BETWEEN " << dateFrom << " AND " << dateTo;
        break;
    case AllDates:
        azCondition << "(   (az.datum_anlage BETWEEN " << dateFrom << " AND " << dateTo << ") "
                       " OR (az.datum_aender BETWEEN " << dateFrom << " AND " << dateTo << ") )";
        break;
    default:
        return "";
    }

    std::stringstream sql;
    sql
        << "SELECT FIRST " << positionsPerPage << " al.artikel_nr "
           "FROM artikellokal al "
           "WHERE al.filialnr = " << branchNo << " AND al.artikel_nr >= " << articleNoFrom << " AND "
           "EXISTS (SELECT 'x' FROM artikelzentral az WHERE az.artikel_nr = al.artikel_nr AND " << azCondition.str() << ") "
           "ORDER BY al.artikel_nr";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());
    return sql.str();
}

} // end namespace customer
} // end namespace libcsc

