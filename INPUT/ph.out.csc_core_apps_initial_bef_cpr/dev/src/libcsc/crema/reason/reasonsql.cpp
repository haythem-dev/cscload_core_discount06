#include <crema/reason/reasonsql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

ReasonSql::ReasonSql()
{
}

ReasonSql::~ReasonSql()
{
}

const basar::VarString ReasonSql::getReasonQuery(
    const basar::Int32 country, const basar::Int32 language, const bool unlock)
{
    std::stringstream sql;
    sql << "Select crt.CremaReasonText as reason, crt.Id as id from CremaReasonTexts crt "
           "inner join CremaCountryTextConfig cctc on cctc.reasonid = crt.id "
           "where ReasonForUnlock = '" << (unlock ? 1 : 0) << "' and countryid = " << country << " and languagecode = " << language << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
