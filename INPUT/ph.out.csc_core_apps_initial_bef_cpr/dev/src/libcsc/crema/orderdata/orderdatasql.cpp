#include <crema/orderdata/orderdatasql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

OrderDataSql::OrderDataSql()
{
}

OrderDataSql::~OrderDataSql()
{
}

const basar::VarString OrderDataSql::getOrderDataQuery(const basar::VarString uuid)
{
    std::stringstream sql;
    sql << "Select kdauftragNr, branchno from DebtMailSend where guid = '" << uuid << "';";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
