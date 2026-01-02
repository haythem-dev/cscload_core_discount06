#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAINSERTSQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAINSERTSQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include "icscorderibtpickingdataptr.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderIBTPickingdataInsertSqlParameterBinder : public persistence::ISqlParameterBinder
{
    public:
        CSCOrderIBTPickingdataInsertSqlParameterBinder(domMod::ICSCOrderIBTPickingdataPtr pickingdata);
        virtual ~CSCOrderIBTPickingdataInsertSqlParameterBinder();

        virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

    private:
        domMod::ICSCOrderIBTPickingdataPtr m_Pickingdata;

        CSCOrderIBTPickingdataInsertSqlParameterBinder& operator=(CSCOrderIBTPickingdataInsertSqlParameterBinder const&);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAINSERTSQLPARAMETERBINDER_H
