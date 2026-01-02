/*
 * callbackreasonmapper.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "callbackreasonmapper.h"
#include "callback/domainmodule/callbackreasondm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackReasonMapper::CallbackReasonMapper(domMod::ICallbackReasonPtr callbackReason)
    : m_CallbackReason(*dynamic_cast<domMod::CallbackReasonDM*>(callbackReason.get()))
{
}

CallbackReasonMapper::~CallbackReasonMapper()
{
}

void CallbackReasonMapper::setBranchNo(basar::Int16 const branchNo)
{
    m_CallbackReason.m_BranchNo = branchNo;
    m_CallbackReason.m_BranchNo.setClean();
}

void CallbackReasonMapper::setDivisionNo(basar::Int16 const divisionNo)
{
    m_CallbackReason.m_DivisionNo = divisionNo;
    m_CallbackReason.m_DivisionNo.setClean();
}

void CallbackReasonMapper::setReasonNo(basar::Int16 const reasonNo)
{
    m_CallbackReason.m_ReasonNo = reasonNo;
    m_CallbackReason.m_ReasonNo.setClean();
}

void CallbackReasonMapper::setReasonName(basar::VarString const reasonName)
{
    m_CallbackReason.m_ReasonName = reasonName;
    m_CallbackReason.m_ReasonName.setClean();
}

void CallbackReasonMapper::setMailingList(basar::VarString const mailingList)
{
    m_CallbackReason.m_MailingList = mailingList;
    m_CallbackReason.m_MailingList.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
