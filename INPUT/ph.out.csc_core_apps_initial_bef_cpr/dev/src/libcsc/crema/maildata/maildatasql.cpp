#include <crema/maildata/maildatasql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

MailDataSql::MailDataSql()
{
}

MailDataSql::~MailDataSql()
{
}

const basar::VarString MailDataSql::getMailDataQuery(
    const basar::VarString uuid)
{
    std::stringstream sql;
    sql << " select sug.sentfromaddress, adr.senttoaddress, sem.emailtype from debtmailsend dms "
           " inner join smtpusergroups sug on sug.id=dms.smtpusergroupid "
           " inner join smtpemailtype sem on sem.smtpusergroupid = sug.id "
           " inner join smtpsendtoemailaddresses adr on sem.id = adr.smtpemailtypeid "
           " where guid = '" << uuid << "' group by adr.senttoaddress, sug.sentfromaddress, sem.emailtype;";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
