/*
 * callbackreasonmapper.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKREASONMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKREASONMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackreasonptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackReasonDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackReasonMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackReasonMapper(domMod::ICallbackReasonPtr callbackReason);
    virtual ~CallbackReasonMapper();

    virtual void setBranchNo(basar::Int16 const branchNo);
    virtual void setDivisionNo(basar::Int16 const divisionNo);
    virtual void setReasonNo(basar::Int16 const reasonNo);
    virtual void setReasonName(basar::VarString const reasonName);
    virtual void setMailingList(basar::VarString const mailingList);

private:
    domMod::CallbackReasonDM& m_CallbackReason;

    CallbackReasonMapper& operator=(CallbackReasonMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKREASONMAPPER_H
