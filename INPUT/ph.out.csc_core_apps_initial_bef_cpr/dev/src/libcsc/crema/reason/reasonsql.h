#ifndef GUARD_LIBCSC_CREMA_REASONSQL_H
#define GUARD_LIBCSC_CREMA_REASONSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class ReasonSql
{
public:
    ~ReasonSql();

    // Create your SQL statement getters here ...
    // e.g.:
    static const basar::VarString getReasonQuery(
        const basar::Int32 country, const basar::Int32 language, const bool unlock);

private:
    ReasonSql();
    ReasonSql& operator=(const ReasonSql&);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_REASONSQL_H
