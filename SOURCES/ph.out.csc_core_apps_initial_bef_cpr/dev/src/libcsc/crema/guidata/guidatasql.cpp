#include <crema/guidata/guidatasql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

GuiDataSql::GuiDataSql()
{
}

GuiDataSql::~GuiDataSql()
{
}

const basar::VarString GuiDataSql::getGuiDataQuery(const basar::Int16 branchNo, const basar::Int32 orderNo)
{
    std::stringstream sql;
    sql << "SELECT "
        << "kda.kdauftragnr, kda.vertriebszentrumnr, kda.wertlieferung, "
        << "k.filialnr, k.idfnr, k.nameinhaber, k.postleitzahl, k.nameapo, k.ort, "
        << "d.limit, d.sum_debitside, d.sum_creditside, d.sum_monturnover, d.sum_dayturnover, d.sum_returns, d.sum_goodsreceipt, "
        << "k.maincstno "
        << "from kdauftrag kda "
        << "inner join kunde k on k.idfnr = kda.idfnr "
        << "inner join debtlimit AS d on d.partnerno = k.partnernr "
        << "where kda.kdauftragnr = " << orderNo << " and kda.vertriebszentrumnr = " << branchNo << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
