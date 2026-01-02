#include <crema/cremaorder/cremaordersql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

CremaOrderSql::CremaOrderSql()
{
}

CremaOrderSql::~CremaOrderSql()
{
}

const basar::VarString CremaOrderSql::getOpenCremaOrdersQuery(
    const basar::Int16 userLevel, const std::vector<basar::Int16>& relevantBranchNos)
{
    std::stringstream sql;
    sql << "SELECT dms.kdauftragnr, dms.guid, dms.branchNo, dms.senddate, kda.idfnr, kda.wertlieferung as ordervalue, sug.url, k.postleitzahl, k.nameapo, k.ort, k.maincstno"
        << " from ( select min(id) as id from debtmailsend group by kdauftragnr ) as dmsa "
        << " inner join debtmailsend dms on dms.id = dmsa.id "
        << " inner join kdauftrag kda on kda.kdauftragnr = dms.kdauftragnr and kda.vertriebszentrumnr = dms.branchNo "
        << " inner join kunde k on k.idfnr = kda.idfnr and k.filialnr = kda.vertriebszentrumnr"
        << " inner join smtpusergroups sug on sug.id = dms.smtpusergroupid "
        << " inner join crematype ct on ct.id = dms.crematypeid "
        << " inner join debtlevelformail dlfm on dlfm.id = ct.typeid "
        << " where ct.type = 0 "
        // 3 = UserLevel.MANAGER, 2 = UserLevel.USER
        << " and dlfm.leveltype in ( 2" << (userLevel == 2 ? "" : ", 3") << " )";

    std::string branchnos = joinRelevantBranchNos(relevantBranchNos);
    if (!branchnos.empty())
    {
        sql << " and dms.branchno in ( " << branchnos << " )";
    }
    sql << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString CremaOrderSql::joinRelevantBranchNos(const std::vector<basar::Int16>& relevantBranchNos)
{
    std::vector<basar::Int16>::const_iterator iter = relevantBranchNos.begin();
    std::stringstream branchnos;
    if (iter != relevantBranchNos.end())
    {
        branchnos << *iter;
        ++iter;
    }
    for (; iter != relevantBranchNos.end(); ++iter)
    {
        branchnos << "," << *iter;
    }
    return branchnos.str();
}

const basar::VarString CremaOrderSql::getFinishedTodayCremaOrdersQuery(const std::vector<basar::Int16>& relevantBranchNos)
{
    std::stringstream sql;
    sql << "SELECT kdad.kdauftragnr, kda.vertriebszentrumnr as branchNo, kda.idfnr, kdad.ordervalue, kdad.reluser, kdad.relreason, kdad.relcomment, k.postleitzahl, k.nameapo, k.ort, k.maincstno"
        << " from kdauftragdebtrel kdad "
        << " inner join kdauftrag kda on kda.kdauftragnr = kdad.kdauftragnr"
        << " inner join kunde k on k.idfnr = kda.idfnr and k.filialnr = kda.vertriebszentrumnr"
        << " where isreleased = 1";

    std::string branchnos = joinRelevantBranchNos(relevantBranchNos);
    if (!branchnos.empty())
    {
        sql << " and kda.vertriebszentrumnr in ( " << branchnos << " )";
    }
    sql << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
