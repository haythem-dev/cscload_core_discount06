#include <customer/discountaccount/discountaccountsql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

DiscountAccountSql::DiscountAccountSql()
{
}

DiscountAccountSql::~DiscountAccountSql()
{
}

// Create your SQL statement getters here ...
// e.g.:
const basar::VarString DiscountAccountSql::getDiscountAccountQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, const bool accNatRebateGroup)
{
    std::stringstream sql;
    sql << "SELECT NVL(SUM(CASE WHEN vouchertyp='GU' THEN -1*balance ELSE balance END), 0) as value "
        << "FROM cstdiscacc "
        << "WHERE branchno=" << branchNo << " AND date >= " << dateFrom << " AND date <= " << dateTo << " "
        << "  AND (   (vouchertyp='RE' AND kdauftragnr=0) "
        << "       OR (vouchertyp='GU') ) "
        << "  AND " << (accNatRebateGroup ? "maincstno" : "customerno") << "=" << customerNo;

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString DiscountAccountSql::getDaGroupNoQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream sql;
    sql << "SELECT maincstno "
        << "FROM kunde "
        << "WHERE filialnr=" << branchNo << " AND idfnr=" << customerNo;

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
