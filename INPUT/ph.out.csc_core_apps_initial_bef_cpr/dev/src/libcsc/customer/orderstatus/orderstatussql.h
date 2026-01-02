#ifndef GUARD_LIBCSC_CUSTOMER_ORDERSTATUSSQL_H
#define GUARD_LIBCSC_CUSTOMER_ORDERSTATUSSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class OrderStatusSql
{
public:
    ~OrderStatusSql();

    static const basar::VarString GetOrderStatusStatusFlagsQuery(const basar::Int16 branchNo,
        const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 orderDate);

private:
    OrderStatusSql();
    OrderStatusSql& operator=(const OrderStatusSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ORDERSTATUSSQL_H
