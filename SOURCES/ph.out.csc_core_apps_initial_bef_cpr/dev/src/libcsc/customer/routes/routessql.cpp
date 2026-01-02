#include <customer/routes/routessql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

RoutesSql::RoutesSql()
{
}

RoutesSql::~RoutesSql()
{
}

const basar::VarString RoutesSql::GetRoutesQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int16 weekday, const basar::Int32 today)
{
    std::stringstream sql;
    sql << "SELECT t.weekday AS Weekday, t.tourid as TourId, a.fahrtzeit as Duration "
        << "FROM tourplantagwoche t "
        << "INNER JOIN tourplantag a ON a.tourid=t.tourid AND a.vertriebszentrumnr=t.vertriebszentrumnr AND a.kundennr=t.kundennr "
        << "WHERE t.vertriebszentrumnr=" << branchNo << " AND t.kundennr=" << customerNo
        << "  AND a.datumkommi=" << today << " AND t.tourid != 475900 "
        << "  AND EXISTS (SELECT 'x' FROM tourplanwoche w WHERE w.weekday=t.weekday AND w.tourid=t.tourid AND w.filialnr=t.vertriebszentrumnr)";
    if (weekday > -1)
    {
        sql << " AND t.weekday=" << weekday;
    }
    sql << " ORDER BY t.weekday, t.tourid";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
