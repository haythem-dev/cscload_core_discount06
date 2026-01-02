/*
 * callbackitemdm.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDM_H

#include "icallbackitemptr.h"
#include "icallbackitem.h"

namespace libcsc {
namespace callback {

namespace repo {
class CallbackItemMapper;
}

namespace domMod {

class CallbackItemDM : public ICallbackItem
{
    // because of OR mapping
    friend class repo::CallbackItemMapper;

public:
    virtual ~CallbackItemDM();

    static ICallbackItemPtr create();

    virtual Int32 const& getCallbackNo() const;
    virtual Int32 const& getCallbackPartNo() const;
    virtual Int16 const& getDivisionNo() const;
    virtual Int32 const& getCritNo() const;
    virtual VarString const& getPosTypeTag() const;
    virtual Int32 const& getPosNo() const;
    virtual Int32 const& getPosNoDone() const;
    virtual Int32 const& getCallbackTimeWished() const;
    virtual Int32 const& getCallbackDateWished() const;
    virtual Int16 const& getCallbackTime() const;
    virtual VarString const& getState() const;
    virtual VarString const& getLockTag() const;
    virtual Int16 const& getShiftCount() const;
    virtual Int16 const& getReasonNo() const;
    virtual Int16 const& getCallbackStatus() const;
    virtual VarString const& getReference() const;

public:
    virtual void setCallbackNo(Int32 const& callbackNo);
    virtual void setCallbackPartNo(Int32 const& callbackPartNo);
    virtual void setDivisionNo(Int16 const& callbackPartNo);
    virtual void setCritNo(Int32 const& critNo);
    virtual void setPosTypeTag(VarString const& posTypeTag);
    virtual void setPosNo(Int32 const& posNo);
    virtual void setPosNoDone(Int32 const& posNoDone);
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished);
    virtual void setCallbackDateWished(Int32 const& callbackDateWished);
    virtual void setCallbackTime(Int16 const& callbackTime);
    virtual void setState(VarString const& state);
    virtual void setLockTag(VarString const& lockTag);
    virtual void setShiftCount(Int16 const& shiftCount);
    virtual void setReasonNo(Int16 const& reasonNo);
    virtual void setCallbackStatus(Int16 const& callbackStatus);
    virtual void setReference(VarString const& reference);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CallbackItemDM();

private:
    Int32 m_CallbackNo;
    Int32 m_CallbackPartNo;
    Int16 m_DivisionNo;
    Int32 m_CritNo;
    VarString m_PosTypeTag;
    Int32 m_PosNo;
    Int32 m_PosNoDone;
    Int32 m_CallbackTimeWished;
    Int32 m_CallbackDateWished;
    Int16 m_CallbackTime;
    VarString m_State;
    VarString m_LockTag;
    Int16 m_ShiftCount;
    Int16 m_ReasonNo;
    Int16 m_CallbackStatus;
    VarString m_Reference;

    CallbackItemDM(const CallbackItemDM&);
    CallbackItemDM& operator=(const CallbackItemDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKITEMDM_H
