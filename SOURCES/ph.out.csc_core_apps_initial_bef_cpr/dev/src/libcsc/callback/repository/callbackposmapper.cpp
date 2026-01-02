/*
 * callbackposmapper.cpp
 *
 *  Created on: 19.05.2017
 *  Author: sebastian.barth
 */

#include "callbackposmapper.h"
#include "callback/domainmodule/callbackposdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackPosMapper::CallbackPosMapper(domMod::ICallbackPosPtr callbackPos)
    : m_CallbackPos(*dynamic_cast<domMod::CallbackPosDM*>(callbackPos.get()))
{
}

CallbackPosMapper::~CallbackPosMapper()
{
}

void CallbackPosMapper::setText(basar::VarString const& text)
{
    m_CallbackPos.m_Text = text;
    m_CallbackPos.m_Text.setClean();
}

void CallbackPosMapper::setCreationDate(basar::Int32 const& creationDate)
{
    m_CallbackPos.m_CreationDate = creationDate;
    m_CallbackPos.m_CreationDate.setClean();
}

void CallbackPosMapper::setCreationTime(basar::Int32 const& creationTime)
{
    m_CallbackPos.m_CreationTime = creationTime;
    m_CallbackPos.m_CreationTime.setClean();
}

void CallbackPosMapper::setUserName(basar::VarString const& userName)
{
    m_CallbackPos.m_UserName = userName;
    m_CallbackPos.m_UserName.setClean();
}

void CallbackPosMapper::setCallbackNo(basar::Int32 const callbackNo)
{
    m_CallbackPos.m_CallbackNo = callbackNo;
    m_CallbackPos.m_CallbackNo.setClean();
}

void CallbackPosMapper::setCallbackPosNo(basar::Int32 const callbackPosNo)
{
    m_CallbackPos.m_CallbackPosNo = callbackPosNo;
    m_CallbackPos.m_CallbackPosNo.setClean();
}

void CallbackPosMapper::setCallbackPosNoDone(basar::Int32 const callbackPosNoDone)
{
    m_CallbackPos.m_CallbackPosNoDone = callbackPosNoDone;
    m_CallbackPos.m_CallbackPosNoDone.setClean();
}

void CallbackPosMapper::setCallbackTimeWished(basar::Int32 const& callbackTimeWished)
{
    m_CallbackPos.m_CallbackTimeWished = callbackTimeWished;
    m_CallbackPos.m_CallbackTimeWished.setClean();
}

void CallbackPosMapper::setCallbackDateWished(basar::Int32 const& callbackDateWished)
{
    m_CallbackPos.m_CallbackDateWished = callbackDateWished;
    m_CallbackPos.m_CallbackDateWished.setClean();
}

void CallbackPosMapper::setDivisionName(basar::VarString const& divisionName)
{
    m_CallbackPos.m_DivisionName = divisionName;
    m_CallbackPos.m_DivisionName.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
