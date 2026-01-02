#include <customer/pricesanddiscounts/pricesanddiscountssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

PricesAndDiscountsSql::PricesAndDiscountsSql()
{
}

PricesAndDiscountsSql::~PricesAndDiscountsSql()
{
}

// Create your SQL statement getters here ...
// e.g.:
const basar::VarString PricesAndDiscountsSql::getPricesAndDiscountsQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const bool nzok)
{
    std::stringstream sql;
    sql << "SELECT DISTINCT cb.articleno, cb.sellingmode, "
        << "                cb.discountpercent AS discountpercentage, cb.grossprofitpct AS grossprofitpercentage, "
        << "                cb.preisfaktur AS salesprice, cb.pharmacysellprice, "
        << (nzok ? "az.healthfundcode" : "' '") << " AS nzokcode "
        << "FROM cucosbulgaria_" << branchNo << " cb "
        << "LEFT OUTER JOIN artikelpreis ap ON ap.artikel_nr=cb.articleno AND ap.preis_typ IN (" << (nzok ? "0, 1" : "0") << ") ";

    if (nzok)
    {
        sql << "LEFT OUTER JOIN artikelzentral az ON az.artikel_nr=ap.artikel_nr ";
    }

    sql << "WHERE cb.customerno=" << customerNo << " AND cb.sellingmode IN(" << (nzok ? "8, 9" : "8") << ") "
        << "  AND EXISTS (SELECT 'x' FROM artikellokal al WHERE al.artikel_nr=cb.articleno AND al.artikelaktiv=1 AND al.filialnr=" << branchNo << ") "
        << "  AND (cb.articleno > 0 OR ap.preisekapo > 0 OR cb.discountpercent > 0 OR cb.preisfaktur > 0 OR cb.grossprofitpct > 0)";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString PricesAndDiscountsSql::getPdAvailableForBranchQuery(
    const basar::Int16 branchno)
{
    std::stringstream sql;
    sql << "SELECT COUNT('x') "
        << "FROM parameter "
        << "WHERE programmname='cucosbulgaria' AND parametername='available' AND wert=1 AND filialnr=" << branchno;

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString PricesAndDiscountsSql::getCustomerNzokNoQuery(
    const basar::Int16 branchno, const basar::Int32 customerno)
{
    std::stringstream sql;
    sql << "SELECT krankenkassennr "
        << "FROM kunde "
        << "WHERE filialnr=" << branchno << " AND idfnr=" << customerno;

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
