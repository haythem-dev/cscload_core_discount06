#ifndef GUARD_LIBCSC_CREMA_MAILDATASQL_H
#define GUARD_LIBCSC_CREMA_MAILDATASQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class MailDataSql
{
public:
    ~MailDataSql();

    // Create your SQL statement getters here ...
    // e.g.:
    static const basar::VarString getMailDataQuery(
        const basar::VarString uuid);

private:
    MailDataSql();
    MailDataSql& operator=(const MailDataSql&);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_MAILDATASQL_H
