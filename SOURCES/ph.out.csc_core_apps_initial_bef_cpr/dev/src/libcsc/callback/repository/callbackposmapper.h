/*
 * callbackposmapper.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKPOSMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKPOSMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackposptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackPosDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackPosMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackPosMapper(domMod::ICallbackPosPtr callbackPos);
    virtual ~CallbackPosMapper();

    virtual void setText(basar::VarString const& text);
    virtual void setCreationDate(basar::Int32 const& creationDate);
    virtual void setCreationTime(basar::Int32 const& creationTime);
    virtual void setUserName(basar::VarString const& userName);
    virtual void setCallbackNo(basar::Int32 const callbackNo);
    virtual void setCallbackPosNo(basar::Int32 const callbackPosNo);
    virtual void setCallbackPosNoDone(basar::Int32 const callbackPosNoDone);
    virtual void setCallbackTimeWished(basar::Int32 const& callbackTimeWished);
    virtual void setCallbackDateWished(basar::Int32 const& callbackDateWished);
    virtual void setDivisionName(basar::VarString const& divisionName);

private:
    domMod::CallbackPosDM& m_CallbackPos;

    CallbackPosMapper& operator=(CallbackPosMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKPOSMAPPER_H
