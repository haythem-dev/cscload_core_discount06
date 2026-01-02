/*
 * repository.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_H

#include "procurementpermission/repository/irepository.h"
#include "procurementpermission/repository/irepositoryptr.h"
#include <libbasarcmnutil_bstring.h>
#include "logger/loggerpool.h"

namespace libcsc {
namespace procurementpermission {
namespace repo {

class Repository : public IRepository
{
public:
    virtual ~Repository();

    static IRepositoryPtr create(log4cplus::Logger const& logger);

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);

    virtual bool isExportPermitted(basar::VarString const& targetIfaCountryCode, basar::Long32 const articleNo);

protected:
    Repository(log4cplus::Logger const& logger);

private:
    Repository& operator=(const Repository&);

    persistence::IAccessorPtr m_FindAccessor;
    log4cplus::Logger const m_Logger;
};

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_REPOSITORY_H
