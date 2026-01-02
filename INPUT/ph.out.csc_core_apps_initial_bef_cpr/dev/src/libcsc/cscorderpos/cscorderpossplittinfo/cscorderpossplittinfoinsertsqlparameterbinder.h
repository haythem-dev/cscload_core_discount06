#ifndef GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOINSERTSQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOINSERTSQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include "icscorderpossplittinfoptr.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

class CSCOrderposSplittinfoInsertSqlParameterBinder : public persistence::ISqlParameterBinder
{
    public:
        CSCOrderposSplittinfoInsertSqlParameterBinder(domMod::ICSCOrderposSplittinfoPtr splittinfo);
        virtual ~CSCOrderposSplittinfoInsertSqlParameterBinder();

        virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

    private:
        domMod::ICSCOrderposSplittinfoPtr m_Splittinfo;

        CSCOrderposSplittinfoInsertSqlParameterBinder& operator=(CSCOrderposSplittinfoInsertSqlParameterBinder const&);
};

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOINSERTSQLPARAMETERBINDER_H
