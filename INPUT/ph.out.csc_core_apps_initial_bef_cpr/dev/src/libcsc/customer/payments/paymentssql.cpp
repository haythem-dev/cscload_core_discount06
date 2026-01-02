#include <customer/payments/paymentssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

PaymentsSql::PaymentsSql()
{
}

PaymentsSql::~PaymentsSql()
{
}

// Create your SQL statement getters here ...
// e.g.:
const basar::VarString PaymentsSql::getPaymentsQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, PaymentsFilterEnum filter)
{
    std::stringstream sql;
    sql << "SELECT invoicenumber as invoiceno, invoicedate, doctype, pricetype as kindofinvoice, kindoforder, daysofpayment as duedays, "
        << "       paymentdate as duedate, totalinvoiceamount as invoicevalue, paidinvoiceamount as paidvalue, paymentspec "
        << "FROM cstpaymentlist "
        << "WHERE branchno=" << branchNo << " AND customerno=" << customerNo << " "
        << "  AND sequenceno=0 AND invoicestate in (0, 1, 2, 6) "
        << "  AND invoicedate >= " << dateFrom << " AND invoicedate <= " << dateTo;

    if (filter != AllDocuments)
    {
        sql << " AND openinvoiceamount <> 0";
    }

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
