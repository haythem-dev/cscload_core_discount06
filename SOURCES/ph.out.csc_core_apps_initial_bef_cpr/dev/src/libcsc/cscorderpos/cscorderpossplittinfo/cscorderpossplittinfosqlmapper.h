#ifndef GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOSQLMAPPER_H
#define GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOSQLMAPPER_H

#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include "cscorderpossplittinfomapperbase.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

class CSCOrderposSplittinfoSqlMapper : public CSCOrderposSplittinfoMapperBase
{
    struct BindedValues
    {
        basar::Int32 cscOrderNo;
        basar::Int32 cscOrderPosNo;
        basar::Int16 splittType;
        basar::Int16 original;
        basar::Int32 orderNo;
        basar::Int32 orderPosNo;
    };

public:
    CSCOrderposSplittinfoSqlMapper(
        domMod::CSCOrderposSplittinfoPtr splittinfo, basar::db::sql::ResultsetRef const resultSet);
    virtual ~CSCOrderposSplittinfoSqlMapper();

    static basar::VarString const getInsertSQL();
    static const basar::VarString getSelectSQL(const basar::Int32 cscorderno, const basar::Int32 cscorderposno,
        const basar::Int16 splitttype);
    static const basar::VarString getSelectArchiveSQL(const basar::Int32 cscorderno, const basar::Int32 cscorderposno,
        const basar::Int16 splitttype, const basar::Int32 date);

    static persistence::ISqlParameterBinderPtr const getInsertSqlParameterBinder(
        domMod::ICSCOrderposSplittinfoPtr splittinfo);

    static void bindInsertSQL(
        basar::db::sql::PreparedStatementRef prepStmt, domMod::ICSCOrderposSplittinfoPtr splittinfo);

protected:
    virtual void doMap();

private:
    const basar::db::sql::ResultsetRef m_ResultSet;

    CSCOrderposSplittinfoSqlMapper& operator=(CSCOrderposSplittinfoSqlMapper const&);

    static BindedValues setBindedValues(domMod::ICSCOrderposSplittinfoPtr splittinfo);
};

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOSQLMAPPER_H
