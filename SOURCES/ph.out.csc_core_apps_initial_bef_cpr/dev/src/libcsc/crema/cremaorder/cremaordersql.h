#ifndef GUARD_LIBCSC_CREMA_CREMAORDERSQL_H
#define GUARD_LIBCSC_CREMA_CREMAORDERSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class CremaOrderSql
{
public:
    ~CremaOrderSql();

    static const basar::VarString getOpenCremaOrdersQuery(
        const basar::Int16 userLevel, const std::vector<basar::Int16>& relevantBranchNos);

    static const basar::VarString getFinishedTodayCremaOrdersQuery(const std::vector<basar::Int16>& relevantBranchNos);

private:
    CremaOrderSql();
    CremaOrderSql& operator=(const CremaOrderSql&);

    static const basar::VarString joinRelevantBranchNos(const std::vector<basar::Int16>& relevantBranchNos);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_CREMAORDERSQL_H
