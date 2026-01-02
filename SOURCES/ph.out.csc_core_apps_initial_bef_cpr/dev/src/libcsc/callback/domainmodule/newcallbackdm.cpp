/*
 * newcallbackdm.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "newcallbackdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

NewCallbackDM::NewCallbackDM()
{
}

NewCallbackDM::~NewCallbackDM()
{
}

INewCallbackPtr NewCallbackDM::create()
{
    return INewCallbackPtr(new NewCallbackDM());
}

Int16 const& NewCallbackDM::getBranchNo() const
{
    return m_BranchNo;
}

Int32 const& NewCallbackDM::getCustomerNo() const
{
    return m_CustomerNo;
}

Int16 const& NewCallbackDM::getCstBranchNo() const
{
    return m_CstBranchNo;
}

Int16 const& NewCallbackDM::getDivisionNo() const
{
    return m_DivisionNo;
}

Int16 const& NewCallbackDM::getReasonNo() const
{
    return m_ReasonNo;
}

VarString const& NewCallbackDM::getCritText() const
{
    return m_CritText;
}

Int16 const& NewCallbackDM::getCritLevel() const
{
    return m_CritLevel;
}

Int32 const& NewCallbackDM::getCallbackTimeWished() const
{
    return m_CallbackTimeWished;
}

Int32 const& NewCallbackDM::getCallbackDateWished() const
{
    return m_CallbackDateWished;
}

VarString const& NewCallbackDM::getState() const
{
    return m_State;
}

VarString const& NewCallbackDM::getUserName() const
{
    return m_UserName;
}

VarString const& NewCallbackDM::getContactPerson() const
{
    return m_ContactPerson;
}

VarString const& NewCallbackDM::getCallbackWantedText() const
{
    return m_CallbackWantedText;
}

VarString const& NewCallbackDM::getWebSiteBaseUrl() const
{
    return m_WebSiteBaseUrl;
}

VarString const& NewCallbackDM::getWindowsUser() const
{
    return m_WindowsUser;
}

Int16 const& NewCallbackDM::getSourceApplication() const
{
    return m_SourceApplication;
}

Int32 const& NewCallbackDM::getUId() const
{
    return m_UId;
}

bool const& NewCallbackDM::getSendEmail() const
{
    return m_SendEmail;
}

Int16 const& NewCallbackDM::getCallbackStatus() const
{
	return m_CallbackStatus;
}

VarString const& NewCallbackDM::getReference() const
{
    return m_Reference;
}

void NewCallbackDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void NewCallbackDM::setCustomerNo(Int32 const& customerNo)
{
    m_CustomerNo = customerNo;
}

void NewCallbackDM::setCstBranchNo(Int16 const& cstBranchNo)
{
    m_CstBranchNo = cstBranchNo;
}

void NewCallbackDM::setDivisionNo(Int16 const& divisionNo)
{
    m_DivisionNo = divisionNo;
}

void NewCallbackDM::setReasonNo(Int16 const& reasonNo)
{
    m_ReasonNo = reasonNo;
}

void NewCallbackDM::setCritText(VarString const& critText)
{
    m_CritText = critText;
}

void NewCallbackDM::setCritLevel(Int16 const& CritLevel)
{
    m_CritLevel = CritLevel;
}

void NewCallbackDM::setCallbackTimeWished(Int32 const& callbackTimeWished)
{
    m_CallbackTimeWished = callbackTimeWished;
}

void NewCallbackDM::setCallbackDateWished(Int32 const& callbackDateWished)
{
    m_CallbackDateWished = callbackDateWished;
}

void NewCallbackDM::setState(VarString const& state)
{
    m_State = state;
}

void NewCallbackDM::setUserName(VarString const& userName)
{
    m_UserName = userName;
}

void NewCallbackDM::setContactPerson(VarString const& contactPerson)
{
    m_ContactPerson = contactPerson;
}

void NewCallbackDM::setCallbackWantedText(VarString const& callbackWantedText)
{
    m_CallbackWantedText = callbackWantedText;
}

void NewCallbackDM::setWebSiteBaseUrl(VarString const& webSiteBaseUrl)
{
    m_WebSiteBaseUrl = webSiteBaseUrl;
}

void NewCallbackDM::setWindowsUser(VarString const& windowsUser)
{
    m_WindowsUser = windowsUser;
}

void NewCallbackDM::setSourceApplication(Int16 const& sourceApplication)
{
    m_SourceApplication = sourceApplication;
}

void NewCallbackDM::setUId(Int32 const& uid)
{
    m_UId = uid;
}

void NewCallbackDM::setSendEmail(bool const& sendEmail)
{
    m_SendEmail = sendEmail;
}

void NewCallbackDM::setCallbackStatus(Int16 const& callbackStatus)
{
	m_CallbackStatus = callbackStatus;
}

void NewCallbackDM::setReference(VarString const& reference)
{
    m_Reference = reference;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
