#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANINSERTSQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANINSERTSQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include <cscorder/csccallplan/icsccallplanptr.h>

namespace libcsc {
namespace cscorder {
namespace domMod {
    class ICSCCallplan;
}
namespace repo {

class CSCCallplanInsertSqlParameterBinder : public persistence::ISqlParameterBinder
{
public:
    CSCCallplanInsertSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);
    virtual ~CSCCallplanInsertSqlParameterBinder();

    virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
    domMod::ICSCCallplanPtr m_CSCCallplan;

    CSCCallplanInsertSqlParameterBinder& operator=(CSCCallplanInsertSqlParameterBinder const& binder);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANINSERTSQLPARAMETERBINDER_H
