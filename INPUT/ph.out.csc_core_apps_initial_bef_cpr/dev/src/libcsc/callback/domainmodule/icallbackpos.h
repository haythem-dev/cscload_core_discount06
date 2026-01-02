/*
 * icallbackpos.h
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOS_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOS_H

#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackPos
{
public:
    virtual ~ICallbackPos() {};

    virtual VarString const& getText() const = 0;
    virtual Int32 const& getCreationDate() const = 0;
    virtual Int32 const& getCreationTime() const = 0;
    virtual VarString const& getUserName() const = 0;
    virtual Int32 const& getCallbackNo() const = 0;
    virtual Int32 const& getCallbackPosNo() const = 0;
    virtual Int32 const& getCallbackPosNoDone() const = 0;
    virtual Int32 const& getCallbackTimeWished() const = 0;
    virtual Int32 const& getCallbackDateWished() const = 0;
    virtual VarString const& getDivisionName() const = 0;

public:
    virtual void setText(VarString const& text) = 0;
    virtual void setCreationDate(Int32 const& creationDate) = 0;
    virtual void setCreationTime(Int32 const& creationTime) = 0;
    virtual void setUserName(VarString const& userName) = 0;
    virtual void setCallbackNo(Int32 const& callbackNo) = 0;
    virtual void setCallbackPosNo(Int32 const& callbackPosNo) = 0;
    virtual void setCallbackPosNoDone(Int32 const& callbackPosNoDone) = 0;
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished) = 0;
    virtual void setCallbackDateWished(Int32 const& callbackDateWished) = 0;
    virtual void setDivisionName(VarString const& divisionName) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKPOS_H
