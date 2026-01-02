/*
 * requestsqlmapper.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_REQUESTSQLMAPPER_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_REQUESTSQLMAPPER_H

#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace procurementpermission {
namespace repo {

class RequestSqlMapper
{
public:
    static const basar::VarString getSelectSQL(basar::VarString const& importIfaCountryCode, const basar::Long32 articleNo);
};

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_REQUESTSQLMAPPER_H
