/*
 * callbackposdm.cpp
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#include "callbackposdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackPosDM::CallbackPosDM()
{
}

CallbackPosDM::~CallbackPosDM()
{
}

ICallbackPosPtr CallbackPosDM::create()
{
    return ICallbackPosPtr(new CallbackPosDM());
}

VarString const& CallbackPosDM::getText() const
{
    return m_Text;
}

Int32 const& CallbackPosDM::getCreationDate() const
{
    return m_CreationDate;
}

Int32 const& CallbackPosDM::getCreationTime() const
{
    return m_CreationTime;
}

VarString const& CallbackPosDM::getUserName() const
{
    return m_UserName;
}

Int32 const& CallbackPosDM::getCallbackNo() const
{
    return m_CallbackNo;
}

Int32 const& CallbackPosDM::getCallbackPosNo() const
{
    return m_CallbackPosNo;
}

Int32 const& CallbackPosDM::getCallbackPosNoDone() const
{
    return m_CallbackPosNoDone;
}

Int32 const& CallbackPosDM::getCallbackTimeWished() const
{
    return m_CallbackTimeWished;
}

Int32 const& CallbackPosDM::getCallbackDateWished() const
{
    return m_CallbackDateWished;
}

VarString const& CallbackPosDM::getDivisionName() const
{
    return m_DivisionName;
}

void CallbackPosDM::setText(VarString const& text)
{
    m_Text = text;
}

void CallbackPosDM::setCreationDate(Int32 const& creationDate)
{
    m_CreationDate = creationDate;
}

void CallbackPosDM::setCreationTime(Int32 const& creationTime)
{
    m_CreationTime = creationTime;
}

void CallbackPosDM::setUserName(VarString const& userName)
{
    m_UserName = userName;
}

void CallbackPosDM::setCallbackNo(Int32 const& callbackNo)
{
    m_CallbackNo = callbackNo;
}

void CallbackPosDM::setCallbackPosNo(Int32 const& callbackPosNo)
{
    m_CallbackPosNo = callbackPosNo;
}

void CallbackPosDM::setCallbackPosNoDone(Int32 const& callbackPosNoDone)
{
    m_CallbackPosNoDone = callbackPosNoDone;
}

void CallbackPosDM::setCallbackTimeWished(Int32 const& callbackTimeWished)
{
    m_CallbackTimeWished = callbackTimeWished;
}

void CallbackPosDM::setCallbackDateWished(Int32 const& callbackDateWished)
{
    m_CallbackDateWished = callbackDateWished;
}

void CallbackPosDM::setDivisionName(VarString const& divisionName)
{
    m_DivisionName = divisionName;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
