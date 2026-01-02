/*
 * newcallbackcritposdm.cpp
 *
 *  Created on: 30.06.2016
 *  Author: sebastian.barth
 */

#include "newcallbackcritposdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

NewCallbackCritPosDM::NewCallbackCritPosDM()
{
}

NewCallbackCritPosDM::~NewCallbackCritPosDM()
{
}

INewCallbackCritPosPtr NewCallbackCritPosDM::create()
{
    return INewCallbackCritPosPtr(new NewCallbackCritPosDM());
}

basar::Int32 const& NewCallbackCritPosDM::getCallbackNo() const
{
    return m_CallbackNo;
}

basar::Int16 const& NewCallbackCritPosDM::getBranchNo() const
{
    return m_BranchNo;
}

basar::Int32 const& NewCallbackCritPosDM::getUId() const
{
    return m_UId;
}

basar::VarString const& NewCallbackCritPosDM::getText() const
{
    return m_Text;
}

basar::VarString const& NewCallbackCritPosDM::getWindowsUser() const
{
    return m_WindowsUser;
}

basar::Int16 const& NewCallbackCritPosDM::getSourceApplication() const
{
    return m_SourceApplication;
}

basar::Int16 const& NewCallbackCritPosDM::getCallbackStatus() const
{
	return m_CallbackStatus;
}

void NewCallbackCritPosDM::setBranchNo(basar::Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void NewCallbackCritPosDM::setCallbackNo(basar::Int32 const& callbackNo)
{
    m_CallbackNo = callbackNo;
}

void NewCallbackCritPosDM::setUId(basar::Int32 const& uid)
{
    m_UId = uid;
}

void NewCallbackCritPosDM::setText(basar::VarString const& text)
{
    m_Text = text;
}

void NewCallbackCritPosDM::setWindowsUser(basar::VarString const& windowsUser)
{
    m_WindowsUser = windowsUser;
}

void NewCallbackCritPosDM::setSourceApplication(basar::Int16 const& sourceApplication)
{
    m_SourceApplication = sourceApplication;
}

void NewCallbackCritPosDM::setCallbackStatus(basar::Int16 const& callbackStatus)
{
	m_CallbackStatus = callbackStatus;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
