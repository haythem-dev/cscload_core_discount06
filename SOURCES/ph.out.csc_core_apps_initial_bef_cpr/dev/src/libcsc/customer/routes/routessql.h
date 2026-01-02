#ifndef GUARD_LIBCSC_CUSTOMER_ROUTESSQL_H
#define GUARD_LIBCSC_CUSTOMER_ROUTESSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class RoutesSql
{
public:
    ~RoutesSql();

    static const basar::VarString GetRoutesQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int16 weekday, const basar::Int32 today);

private:
    RoutesSql();
    RoutesSql& operator=(const RoutesSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ROUTESSQL_H
