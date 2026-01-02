#include <customer/paymentconditions/paymentconditionssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace customer {

    PaymentConditionsSql::PaymentConditionsSql()
    {
    }

    PaymentConditionsSql::~PaymentConditionsSql()
    {
    }

// Create your SQL statement getters here ...
// e.g.:
const basar::VarString PaymentConditionsSql::getPaymentConditionsQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream sql;
    sql << "SELECT k.rebatemethhealthf as nzokdiscountmethod, k.rebatemethfreesale as discountmethod, "
        << "       NVL(t0.paymentarget, 0::smallint) as daysofpayment, NVL(t1.paymentarget, 0::smallint) as nzokdaysofpayment "
        << "FROM kunde k "
        << "LEFT JOIN cstpaymentterms as t0 on t0.branchno=k.filialnr AND t0.customerno=k.idfnr AND t0.preis_typ=0 "
        << "LEFT JOIN cstpaymentterms as t1 on t1.branchno=k.filialnr AND t1.customerno=k.idfnr AND t1.preis_typ=1 "
        << "WHERE k.filialnr=" << branchNo << " AND k.idfnr=" << customerNo;

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc
