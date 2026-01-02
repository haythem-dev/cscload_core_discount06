/*
 * irepository.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_IREPOSITORY_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_IREPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace procurementpermission {
namespace repo {

class IRepository
{
public:
    virtual ~IRepository() {}

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor) = 0;

    virtual bool isExportPermitted(basar::VarString const& targetIfaCountryCode, basar::Long32 const articleNo) = 0;
};

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_IREPOSITORY_H
