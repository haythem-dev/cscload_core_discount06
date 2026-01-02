#ifndef GUARD_LIBCSC_CUSTOMER_TOURSSQL_H
#define GUARD_LIBCSC_CUSTOMER_TOURSSQL_H

#include <string>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ToursSql
{
public:
    ~ToursSql();

    // Create your SQL statement getters here ...
    // e.g.:
    static const basar::VarString getToursQuery(
        const basar::Int32 branchNo, const basar::Int32 tourDate);

    static const basar::VarString getCustomerToursInfoQuery(
        const basar::Int16 branchNo,
        const basar::Int32 tourDate,
        const std::vector<std::string>& tourIds,
        const basar::VarString& dbNameWarehouse);

private:
    ToursSql();
    ToursSql& operator=(const ToursSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TOURSSQL_H
