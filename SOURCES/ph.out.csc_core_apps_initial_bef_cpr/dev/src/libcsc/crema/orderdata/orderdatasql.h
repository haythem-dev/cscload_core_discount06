#ifndef GUARD_LIBCSC_CREMA_ORDERDATASQL_H
#define GUARD_LIBCSC_CREMA_ORDERDATASQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class OrderDataSql
{
public:
    ~OrderDataSql();

    static const basar::VarString getOrderDataQuery(const basar::VarString uuid);

private:
    OrderDataSql();
    OrderDataSql& operator=(const OrderDataSql&);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_ORDERDATASQL_H
