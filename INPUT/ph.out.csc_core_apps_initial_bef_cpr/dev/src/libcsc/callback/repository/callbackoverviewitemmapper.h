/*
 * callbackoverviewitemmapper.h
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKOVERVIEWITEMMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKOVERVIEWITEMMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackoverviewitemptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackOverviewItemDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackOverviewItemMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackOverviewItemMapper(domMod::ICallbackOverviewItemPtr callback);
    virtual ~CallbackOverviewItemMapper();

    virtual void setCallbackNo(basar::Int32 const callbackNo);
    virtual void setBranchNo(basar::Int16 const& branchNo);
    virtual void setCallbackDate(basar::Int32 const& callbackDate);
    virtual void setCallbackTime(basar::Int32 const& callbacktime);
    virtual void setReasonName(basar::VarString const& reasonName);
    virtual void setPharmacyName(basar::VarString const& pharmacyName);
    virtual void setCity(basar::VarString const& city);
    virtual void setCritLevel(basar::Int16 const& critLevel);
    virtual void setCallbackStatus(basar::VarString const& callbackStatus);
    virtual void setDivisionName(basar::VarString const& divisionName);
    virtual void setReference(basar::VarString const& reference);

private:
    domMod::CallbackOverviewItemDM& m_Callback;

    CallbackOverviewItemMapper& operator=(CallbackOverviewItemMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKOVERVIEWITEMMAPPER_H
