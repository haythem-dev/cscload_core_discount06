/*
 * inewcallback.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACK_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACK_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace callback {
namespace domMod {

class INewCallback
{
public:
    virtual ~INewCallback() {};

    virtual Int16 const& getBranchNo() const = 0;
    virtual Int32 const& getCustomerNo() const = 0;
    virtual Int16 const& getCstBranchNo() const = 0;
    virtual Int16 const& getDivisionNo() const = 0;
    virtual Int16 const& getReasonNo() const = 0;
    virtual VarString const& getCritText() const = 0;
    virtual Int16 const& getCritLevel() const = 0;
    virtual Int32 const& getCallbackTimeWished() const = 0;
    virtual Int32 const& getCallbackDateWished() const = 0;
    virtual VarString const& getState() const = 0;
    virtual VarString const& getUserName() const = 0;
    virtual VarString const& getContactPerson() const = 0;
    virtual VarString const& getCallbackWantedText() const = 0;
    virtual VarString const& getWebSiteBaseUrl() const = 0;
    virtual VarString const& getWindowsUser() const = 0;
    virtual Int16 const& getSourceApplication() const = 0;
    virtual Int32 const& getUId() const = 0;
    virtual bool const& getSendEmail() const = 0;
    virtual Int16 const& getCallbackStatus() const = 0;
    virtual VarString const& getReference() const = 0;

public:
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setCustomerNo(Int32 const& customerNo) = 0;
    virtual void setCstBranchNo(Int16 const& branchNo) = 0;
    virtual void setDivisionNo(Int16 const& divisionNo) = 0;
    virtual void setReasonNo(Int16 const& reasonNo) = 0;
    virtual void setCritText(VarString const& critText) = 0;
    virtual void setCritLevel(Int16 const& CritLevel) = 0;
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished) = 0;
    virtual void setCallbackDateWished(Int32 const& callbackDateWished) = 0;
    virtual void setState(VarString const& state) = 0;
    virtual void setUserName(VarString const& userName) = 0;
    virtual void setContactPerson(VarString const& contactPerson) = 0;
    virtual void setCallbackWantedText(VarString const& callbackWantedText) = 0;
    virtual void setWebSiteBaseUrl(VarString const& webSiteBaseUrl) = 0;
    virtual void setWindowsUser(VarString const& windowsUser) = 0;
    virtual void setSourceApplication(Int16 const& sourceApplication) = 0;
    virtual void setUId(Int32 const& uid) = 0;
    virtual void setSendEmail(bool const& sendEmail) = 0;
    virtual void setCallbackStatus(Int16 const& callbackStatus) = 0;
    virtual void setReference(VarString const& reference) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACK_H
