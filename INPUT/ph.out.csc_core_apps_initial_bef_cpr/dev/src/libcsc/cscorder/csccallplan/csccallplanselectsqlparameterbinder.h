#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSELECTSQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSELECTSQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include <cscorder/csccallplan/icsccallplanptr.h>

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCCallplanSelectSqlParameterBinder : public persistence::ISqlParameterBinder
{
public:
    CSCCallplanSelectSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);
    virtual ~CSCCallplanSelectSqlParameterBinder();

    virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
    domMod::ICSCCallplanPtr m_CSCCallplan;

    CSCCallplanSelectSqlParameterBinder& operator=(CSCCallplanSelectSqlParameterBinder const& binder);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSELECTSQLPARAMETERBINDER_H
