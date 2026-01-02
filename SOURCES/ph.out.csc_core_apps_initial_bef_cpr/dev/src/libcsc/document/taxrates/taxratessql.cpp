#include <document/taxrates/taxratessql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace document {

TaxratesSql::TaxratesSql()
{
}

TaxratesSql::~TaxratesSql()
{
}

const basar::VarString TaxratesSql::getTaxratesQuery()
{
    std::stringstream sql;
    sql << "SELECT taxlevel, salestaxrate "
        << "FROM taxrates";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace document
} // end namespace libcsc
