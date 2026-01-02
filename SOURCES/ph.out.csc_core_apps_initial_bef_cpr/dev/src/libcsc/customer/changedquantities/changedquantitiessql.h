#ifndef GUARD_LIBCSC_CUSTOMER_CHANGEDQUANTITIESSQL_H
#define GUARD_LIBCSC_CUSTOMER_CHANGEDQUANTITIESSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ChangedQuantitiesSql
{
public:
    ~ChangedQuantitiesSql();

    static const basar::VarString GetChangedQuantitiesQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo);

private:
    ChangedQuantitiesSql();
    ChangedQuantitiesSql& operator=(const ChangedQuantitiesSql&);

    static const basar::VarString GetQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, bool archive);

    static const basar::VarString GetWhere(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 orderNo, const basar::Int32 dateFrom, const basar::Int32 dateTo, bool archive);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CHANGEDQUANTITIESSQL_H
