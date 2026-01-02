#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATASQLMAPPER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATASQLMAPPER_H

#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include "cscorderibtpickingdatamapperbase.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderIBTPickingdataSqlMapper : public CSCOrderIBTPickingdataMapperBase
{
    struct BindedValues
    {
        basar::Int32 cscOrderNo;
        basar::Int32 cscOrderPosNo;
        basar::Int32 deliveryPosNo;
        basar::Int32 quantity;
        basar::VarString batch;
        basar::Int32 expiryDate;
    };

public:
    CSCOrderIBTPickingdataSqlMapper(
        domMod::CSCOrderIBTPickingdataPtr pickingdata, basar::db::sql::ResultsetRef const resultSet);
    virtual ~CSCOrderIBTPickingdataSqlMapper();

    static basar::VarString const getInsertSQL();
    static const basar::VarString getSelectSQL(const basar::Int32 cscorderno, const basar::Int32 cscorderposno);

    static persistence::ISqlParameterBinderPtr const getInsertSqlParameterBinder(
        domMod::ICSCOrderIBTPickingdataPtr pickingdata);

    static void bindInsertSQL(
        basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderIBTPickingdataPtr pickingdata);

protected:
    virtual void doMap();

private:
    const basar::db::sql::ResultsetRef m_ResultSet;

    CSCOrderIBTPickingdataSqlMapper& operator=(CSCOrderIBTPickingdataSqlMapper const&);

    static BindedValues setBindedValues(domMod::ICSCOrderIBTPickingdataPtr pickingdata);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATASQLMAPPER_H
