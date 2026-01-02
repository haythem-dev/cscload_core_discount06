/*
 * newcallbackdm.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDM_H

#include "inewcallbackptr.h"
#include "inewcallback.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {

namespace repo {
class CallbackMapper;
}

namespace domMod {

class NewCallbackDM : public INewCallback
{
    // because of OR mapping
    friend class repo::CallbackMapper;

public:
    virtual ~NewCallbackDM();

    static INewCallbackPtr create();

    virtual Int16 const& getBranchNo() const;
    virtual Int32 const& getCustomerNo() const;
    virtual Int16 const& getCstBranchNo() const;
    virtual Int16 const& getDivisionNo() const;
    virtual Int16 const& getReasonNo() const;
    virtual VarString const& getCritText() const;
    virtual Int16 const& getCritLevel() const;
    virtual Int32 const& getCallbackTimeWished() const;
    virtual Int32 const& getCallbackDateWished() const;
    virtual VarString const& getState() const;
    virtual VarString const& getUserName() const;
    virtual VarString const& getContactPerson() const;
    virtual VarString const& getCallbackWantedText() const;
    virtual VarString const& getWebSiteBaseUrl() const;
    virtual VarString const& getWindowsUser() const;
    virtual Int16 const& getSourceApplication() const;
    virtual Int32 const& getUId() const;
    virtual bool const& getSendEmail() const;
    virtual Int16 const& getCallbackStatus() const;
    virtual VarString const& getReference() const;

public:
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setCustomerNo(Int32 const& customerNo);
    virtual void setCstBranchNo(Int16 const& cstBranchNo);
    virtual void setDivisionNo(Int16 const& divisionNo);
    virtual void setReasonNo(Int16 const& reasonNo);
    virtual void setCritText(VarString const& critText);
    virtual void setCritLevel(Int16 const& CritLevel);
    virtual void setCallbackTimeWished(Int32 const& callbackTimeWished);
    virtual void setCallbackDateWished(Int32 const& callbackDateWished);
    virtual void setState(VarString const& state);
    virtual void setUserName(VarString const& userName);
    virtual void setContactPerson(VarString const& contactPerson);
    virtual void setCallbackWantedText(VarString const& callbackWantedText);
    virtual void setWebSiteBaseUrl(VarString const& webSiteBaseUrl);
    virtual void setWindowsUser(VarString const& windowsUser);
    virtual void setSourceApplication(Int16 const& sourceApplication);
    virtual void setUId(Int32 const& uid);
    virtual void setSendEmail(bool const& sendEmail);
    virtual void setCallbackStatus(Int16 const& callbackStatus);
    virtual void setReference(VarString const& reference);

protected:
    NewCallbackDM();

private:
    Int16 m_BranchNo;
    Int32 m_CustomerNo;
    Int16 m_CstBranchNo;
    Int16 m_DivisionNo;
    Int16 m_ReasonNo;
    VarString m_CritText;
    Int16 m_CritLevel;
    Int32 m_CallbackTimeWished;
    Int32 m_CallbackDateWished;
    VarString m_State;
    VarString m_UserName;
    VarString m_ContactPerson;
    VarString m_CallbackWantedText;
    VarString m_WebSiteBaseUrl;
    VarString m_WindowsUser;
    Int16 m_SourceApplication;
    Int32 m_UId;
    bool m_SendEmail;
    Int16 m_CallbackStatus;
    VarString m_Reference;

    NewCallbackDM(const NewCallbackDM&);
    NewCallbackDM& operator=(const NewCallbackDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKDM_H
