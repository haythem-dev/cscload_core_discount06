#ifndef GUARD_LIBCSC_CUSTOMER_TURNOVERSQL_H
#define GUARD_LIBCSC_CUSTOMER_TURNOVERSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class TurnoverSql
{
public:
    ~TurnoverSql();

    static const basar::VarString GetTurnoverQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 dateFrom, const basar::Int32 dateTo);

private:
    TurnoverSql();
    TurnoverSql& operator=(const TurnoverSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TURNOVERSQL_H
