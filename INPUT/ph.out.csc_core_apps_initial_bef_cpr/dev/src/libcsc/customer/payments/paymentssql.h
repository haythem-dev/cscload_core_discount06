#ifndef GUARD_LIBCSC_CUSTOMER_PAYMENTSSQL_H
#define GUARD_LIBCSC_CUSTOMER_PAYMENTSSQL_H

#include <libbasar_definitions.h>
#include "types/paymentsfilterenum.inc"

namespace libcsc {
namespace customer {

class PaymentsSql
{
public:
    ~PaymentsSql();

    // Create your SQL statement getters here ...
    // e.g.:
    static const basar::VarString getPaymentsQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, PaymentsFilterEnum filter);

private:
    PaymentsSql();
    PaymentsSql& operator=(const PaymentsSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PAYMENTSSQL_H
