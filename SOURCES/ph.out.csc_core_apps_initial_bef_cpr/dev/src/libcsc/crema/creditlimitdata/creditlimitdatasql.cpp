#include <crema/creditlimitdata/creditlimitdatasql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

CreditlimitDataSql::CreditlimitDataSql()
{
}

CreditlimitDataSql::~CreditlimitDataSql()
{
}

const basar::VarString CreditlimitDataSql::getCreditlimitDataQuery(const basar::Int16 branchNo, const basar::Int32 orderNo)
{
    // Selects limit type 2 and 1 or chain instead of 1.
    std::stringstream sql;
    sql << "SELECT "
        << "d.limit as creditlimit, "
        << "d.sum_debitside as sumdebitside, "
        << "d.sum_creditside as sumcreditside, "
        << "d.sum_monturnover as summonturnover, "
        << "d.sum_dayturnover as sumdayturnover, "
        << "d.sum_returns as sumreturns, "
        << "d.sum_goodsreceipt as sumgoodsreceipt, "
        << "d.limittype as limittype, "
        << "CASE WHEN d.partnerno = k.maincstno THEN CAST(1 AS SMALLINT) ELSE CAST(0 AS SMALLINT) END as ischain "
        << "from kdauftrag kda "
        << "inner join kunde k on k.idfnr = kda.idfnr "
        << "inner join debtlimit AS d on d.partnerno = k.partnernr or d.partnerno = k.maincstno "
        << "where kda.kdauftragnr = " << orderNo << " and kda.vertriebszentrumnr = " << branchNo
        << " and (d.limittype = 2 or d.partnerno = k.maincstno or k.maincstno = 0);";
        

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
