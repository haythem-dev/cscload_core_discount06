/*
 * icallbackitem.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKITEM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKITEM_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackItem : public base::IDomainModule
{
public:
    virtual ~ICallbackItem() {};

    virtual Int32 const& getCallbackNo() const = 0;
    virtual Int32 const& getCallbackPartNo() const = 0;
    virtual Int16 const& getDivisionNo() const = 0;
    virtual Int32 const& getCritNo() const = 0;
    virtual VarString const& getPosTypeTag() const = 0;
    virtual Int32 const& getPosNo() const = 0;
    virtual Int32 const& getPosNoDone() const = 0;
    virtual Int32 const& getCallbackTimeWished() const = 0;
    virtual Int32 const& getCallbackDateWished() const = 0;
    virtual Int16 const& getCallbackTime() const = 0;
    virtual VarString const& getState() const = 0;
    virtual VarString const& getLockTag() const = 0;
    virtual Int16 const& getShiftCount() const = 0;
    virtual Int16 const& getReasonNo() const = 0;
    virtual Int16 const& getCallbackStatus() const = 0;
    virtual VarString const& getReference() const = 0;

public:
    virtual void setCallbackNo(Int32 const& callbackNo) = 0;
    virtual void setCallbackPartNo(Int32 const& callbackPartNo) = 0;
    virtual void setDivisionNo(Int16 const& callbackdivisionNo) = 0;
    virtual void setCritNo(Int32 const& critNo) = 0;
    virtual void setPosTypeTag(VarString const& posTypeTag) = 0;
    virtual void setPosNo(Int32 const& posNo) = 0;
    virtual void setPosNoDone(Int32 const& posNoDone) = 0;
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished) = 0;
    virtual void setCallbackDateWished(Int32 const& callbackDateWished) = 0;
    virtual void setCallbackTime(Int16 const& callbackTime) = 0;
    virtual void setState(VarString const& state) = 0;
    virtual void setLockTag(VarString const& lockTag) = 0;
    virtual void setShiftCount(Int16 const& shiftCount) = 0;
    virtual void setReasonNo(Int16 const& reasonNo) = 0;
    virtual void setCallbackStatus(Int16 const& callbackStatus) = 0;
    virtual void setReference(VarString const& reference) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKITEM_H
