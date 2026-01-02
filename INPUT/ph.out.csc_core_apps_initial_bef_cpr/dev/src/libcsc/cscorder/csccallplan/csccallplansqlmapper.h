#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSQLMAPPER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSQLMAPPER_H

#include "csccallplanmapperbase.h"
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>


namespace libcsc {
namespace cscorder {
namespace repo {

class CSCCallplanSqlMapper : public CSCCallplanMapperBase
{
    struct BindedValues
    {
        basar::Int16 branchNo;
        basar::Int32 customerNo;
        basar::Int32 date;
        basar::Int32 timeNow;
        basar::Int32 timeFrom;
        basar::Int32 timeTo;
        basar::Int32 callTime;
        basar::Int16 action;
    };

public:
    CSCCallplanSqlMapper(domMod::ICSCCallplanPtr cscCallplan, basar::db::sql::ResultsetRef const resultSet);
    virtual ~CSCCallplanSqlMapper();

    static basar::VarString const getInsertSQL();
    static basar::VarString const getUpdateSQL();
    static const basar::VarString getSelectSQL();

    static persistence::ISqlParameterBinderPtr const getInsertSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);
    static persistence::ISqlParameterBinderPtr const getUpdateSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);
    static persistence::ISqlParameterBinderPtr const getSelectSqlParameterBinder(domMod::ICSCCallplanPtr cscCallplan);

    static void bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan);
    static void bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan);
    static void bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCCallplanPtr cscCallplan);

protected:
    virtual void doMap();

private:
    const basar::db::sql::ResultsetRef m_ResultSet;

    CSCCallplanSqlMapper& operator=(CSCCallplanSqlMapper const&);

    static BindedValues setBindedValues(domMod::ICSCCallplanPtr cscCallplan);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANSQLMAPPER_H
