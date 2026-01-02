/*
 * callbackitemmapper.h
 *
 *  Created on: 13.05.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKITEMMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKITEMMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackitemptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackItemDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackItemMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackItemMapper(domMod::ICallbackItemPtr callbackItem);
    virtual ~CallbackItemMapper();

    virtual void setCallbackNo(basar::Int32 const callbackNo);
    virtual void setCritNo(basar::Int32 const critNo);
    virtual void setPosTypeTag(basar::VarString const posTypeTag);
    virtual void setPosNoDone(basar::Int32 const posNoDone);
    virtual void setLockTag(basar::VarString const lockTag);
    virtual void setCallbackStatus(basar::Int16 const callbackStatus);

private:
    domMod::CallbackItemDM& m_CallbackItem;

    CallbackItemMapper& operator=(CallbackItemMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKITEMMAPPER_H
