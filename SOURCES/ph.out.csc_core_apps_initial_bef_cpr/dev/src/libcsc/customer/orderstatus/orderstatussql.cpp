#include <customer/orderstatus/orderstatussql.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

OrderStatusSql::OrderStatusSql()
{
}

OrderStatusSql::~OrderStatusSql()
{
}

const basar::VarString OrderStatusSql::GetOrderStatusStatusFlagsQuery(const basar::Int16 branchNo,
    const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 orderDate)
{
    bool archive = (orderDate > 0);

    std::stringstream sql;
    sql << "SELECT FIRST 1 a.kdauftragstat[2] as inprocess, a.kdauftragstat[4] as onhold, a.kdauftragstat[5] as ordercreated, a.kdauftragstat[8] as readyforinvoicing, "
        << "a.kdauftragstat[9] as invoicecreated, a.kdauftragstat[10] as ordercanceled, a.kdauftragstat[13] as onhold2, "
        << "CAST(NVL(c.driverid, 0) AS INTEGER) AS driverid, CAST(NVL(a.rechnungnr, 0) AS INTEGER) AS invoiceno, "
        << "CAST(NVL(a.kdauftragnrfiliale, 0) AS INTEGER) AS pharmosorderno "
        << "FROM " << (archive ? "a" : "") << "kdauftrag a "
        << "LEFT JOIN cstpaymentlist c "
        << "ON c.branchno=a.filialnr "
        << "AND c.customerno=a.idfnr "
        << "AND c.sequenceno=0 "
        << "AND c.invoicenumber=a.invoicenumber ";
    if (archive)
    {
        sql << "AND c.invoicedate=a.datum ";
    }
    sql << "WHERE a.filialnr=" << branchNo << " AND a.idfnr=" << customerNo << " AND a.kdauftragnr=" << orderNo;
    if (archive)
    {
        sql << " AND a.datum=" << orderDate;
    }

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
