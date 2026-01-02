#ifndef GUARD_LIBCSC_CREMA_CREDITLIMITDATASQL_H
#define GUARD_LIBCSC_CREMA_CREDITLIMITDATASQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class CreditlimitDataSql
{
public:
    ~CreditlimitDataSql();

    static const basar::VarString getCreditlimitDataQuery(const basar::Int16 branchNo, const basar::Int32 orderNo);

private:
    CreditlimitDataSql();
    CreditlimitDataSql& operator=(const CreditlimitDataSql&);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_CREDITLIMITDATASQL_H
