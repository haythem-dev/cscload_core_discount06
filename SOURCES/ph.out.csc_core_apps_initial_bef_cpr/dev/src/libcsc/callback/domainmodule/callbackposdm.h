/*
 * callbackposdm.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDM_H

#include "icallbackposptr.h"
#include "icallbackpos.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {

namespace repo {
class CallbackPosMapper;
}

namespace domMod {

class CallbackPosDM : public ICallbackPos
{
    // because of OR mapping
    friend class repo::CallbackPosMapper;

public:
    virtual ~CallbackPosDM();

    static ICallbackPosPtr create();

    virtual VarString const& getText() const;
    virtual Int32 const& getCreationDate() const;
    virtual Int32 const& getCreationTime() const;
    virtual VarString const& getUserName() const;
    virtual Int32 const& getCallbackNo() const;
    virtual Int32 const& getCallbackPosNo() const;
    virtual Int32 const& getCallbackPosNoDone() const;
    virtual Int32 const& getCallbackTimeWished() const;
    virtual Int32 const& getCallbackDateWished() const;
    virtual VarString const& getDivisionName() const;

public:
    virtual void setText(VarString const& text);
    virtual void setCreationDate(Int32 const& creationDate);
    virtual void setCreationTime(Int32 const& creationTime);
    virtual void setUserName(VarString const& userName);
    virtual void setCallbackNo(Int32 const& callbackNo);
    virtual void setCallbackPosNo(Int32 const& callbackPosNo);
    virtual void setCallbackPosNoDone(Int32 const& callbackPosNoDone);
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished);
    virtual void setCallbackDateWished(Int32 const& callbackDateWished);
    virtual void setDivisionName(VarString const& divisionName);

protected:
    CallbackPosDM();

private:
    VarString m_Text;
    Int32 m_CreationDate;
    Int32 m_CreationTime;
    VarString m_UserName;
    Int32 m_CallbackNo;
    Int32 m_CallbackPosNo;
    Int32 m_CallbackPosNoDone;
    Int32 m_CallbackDateWished;
    Int32 m_CallbackTimeWished;
    VarString m_DivisionName;

    CallbackPosDM(const CallbackPosDM&);
    CallbackPosDM& operator=(const CallbackPosDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKPOSDM_H
