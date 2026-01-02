#ifndef GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H
#define GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class  PricesAndDiscountsSql
{
public:
    ~PricesAndDiscountsSql();

// Create your SQL statement getters here ...
// e.g.:
static const basar::VarString getPricesAndDiscountsQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const bool nzok);

static const basar::VarString getPdAvailableForBranchQuery(
    const basar::Int16 branchno);

static const basar::VarString getCustomerNzokNoQuery(
    const basar::Int16 branchno, const basar::Int32 customerno);

private:
    PricesAndDiscountsSql();
    PricesAndDiscountsSql& operator=(const  PricesAndDiscountsSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PRICESANDDISCOUNTSSQL_H
