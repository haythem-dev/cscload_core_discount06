#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSSQLMAPPER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSSQLMAPPER_H

#include "cscorderflagsmapperbase.h"
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>


namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderFlagsSqlMapper : public CSCOrderFlagsMapperBase
{
    struct BindedValues
    {
        basar::Int32 cscOrderNo;
        basar::Int16 noDelayedDelivery;
        basar::Int16 waitForIbtPicking;
    };

public:    
    CSCOrderFlagsSqlMapper(domMod::CSCOrderFlagsPtr cscOrderFlags, basar::db::sql::ResultsetRef const resultSet);
    virtual ~CSCOrderFlagsSqlMapper();

    static bool isInsertable(domMod::ICSCOrderFlagsPtr cscOrderFlags);
    static bool isUpdatable(domMod::ICSCOrderFlagsPtr cscOrderFlags);

    static basar::VarString const getInsertSQL();
    static basar::VarString const getUpdateSQL();
    static basar::VarString const getDeleteSQL(const basar::Int32 cscorderno);
    static const basar::VarString getSelectSQL(const basar::Int32 cscorderno);

    static persistence::ISqlParameterBinderPtr const getInsertSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags);
    static persistence::ISqlParameterBinderPtr const getUpdateSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags);

    static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderFlagsPtr cscOrderFlags);
    static void bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderFlagsPtr cscOrderFlags);

protected:
    virtual void doMap();

private:
    const basar::db::sql::ResultsetRef m_ResultSet;

    CSCOrderFlagsSqlMapper& operator=(CSCOrderFlagsSqlMapper const&);

    static BindedValues setBindedValues(domMod::ICSCOrderFlagsPtr cscOrderFlags);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSSQLMAPPER_H
