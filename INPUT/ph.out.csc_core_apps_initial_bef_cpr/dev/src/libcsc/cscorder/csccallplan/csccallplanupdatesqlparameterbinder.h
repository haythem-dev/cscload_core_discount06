#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANUPDATESQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANUPDATESQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include <cscorder/csccallplan/icsccallplanptr.h>

namespace libcsc {
namespace cscorder {
namespace domMod {
    class ICSCCallplan;
}
namespace repo {

class CSCCallplanUpdateSqlParameterBinder : public persistence::ISqlParameterBinder
{
public:
    CSCCallplanUpdateSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);
    virtual ~CSCCallplanUpdateSqlParameterBinder();

    virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
    domMod::ICSCCallplanPtr m_CSCCallplan;

    CSCCallplanUpdateSqlParameterBinder& operator=(CSCCallplanUpdateSqlParameterBinder const& binder);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANUPDATESQLPARAMETERBINDER_H
