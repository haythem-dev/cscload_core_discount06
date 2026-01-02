#ifndef GUARD_LIBCSC_CUSTOMER_DISCOUNTACCOUNTSQL_H
#define GUARD_LIBCSC_CUSTOMER_DISCOUNTACCOUNTSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class DiscountAccountSql
{
public:
    ~DiscountAccountSql();

    // Create your SQL statement getters here ...
    // e.g.:
    static const basar::VarString getDiscountAccountQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, const bool accNatRebateGroup);

    static const basar::VarString getDaGroupNoQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo);

private:
    DiscountAccountSql();
    DiscountAccountSql& operator=(const DiscountAccountSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_DISCOUNTACCOUNTSQL_H
