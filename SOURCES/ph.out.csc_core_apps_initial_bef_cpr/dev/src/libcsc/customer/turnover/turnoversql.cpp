#include <customer/turnover/turnoversql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

TurnoverSql::TurnoverSql()
{
}

TurnoverSql::~TurnoverSql()
{
}

const basar::VarString TurnoverSql::GetTurnoverQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo)
{
    std::stringstream sql;
    sql << "SELECT SUM(invoicevolume) AS total, SUM(volume1) AS xmlvalue, (SUM(invoicevolume)-SUM(volume1)) AS value "
        << "FROM dealervolume "
        << "WHERE branchno = " << branchNo
        << "  AND customerno = " << customerNo
        << "  AND (dateinvoice >= " << dateFrom << " AND dateinvoice <= " << dateTo << ")";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
