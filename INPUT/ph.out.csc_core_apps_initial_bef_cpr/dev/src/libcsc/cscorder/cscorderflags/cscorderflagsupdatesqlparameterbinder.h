#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSUPDATESQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSUPDATESQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include <cscorder/cscorderflags/icscorderflagsptr.h>

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderFlagsUpdateSqlParameterBinder : public persistence::ISqlParameterBinder
{
public:
	CSCOrderFlagsUpdateSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags);
    virtual ~CSCOrderFlagsUpdateSqlParameterBinder();

    virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	domMod::ICSCOrderFlagsPtr m_CSCOrderFlags;

    CSCOrderFlagsUpdateSqlParameterBinder& operator=(CSCOrderFlagsUpdateSqlParameterBinder const& binder);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSUPDATESQLPARAMETERBINDER_H
