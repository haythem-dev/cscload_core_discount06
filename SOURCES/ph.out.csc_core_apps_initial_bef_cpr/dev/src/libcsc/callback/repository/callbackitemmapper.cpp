/*
 * callbackitemmapper.cpp
 *
 *  Created on: 13.05.2016
 *  Author: sebastian.barth
 */

#include "callbackitemmapper.h"
#include "callback/domainmodule/callbackitemdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackItemMapper::CallbackItemMapper(domMod::ICallbackItemPtr callbackItem)
    : m_CallbackItem(*dynamic_cast<domMod::CallbackItemDM*>(callbackItem.get()))
{
}

CallbackItemMapper::~CallbackItemMapper()
{
}

void CallbackItemMapper::setCallbackNo(basar::Int32 const callbackNo)
{
    m_CallbackItem.m_CallbackNo = callbackNo;
    m_CallbackItem.m_CallbackNo.setClean();
}

void CallbackItemMapper::setCritNo(basar::Int32 const critNo)
{
    m_CallbackItem.m_CritNo = critNo;
    m_CallbackItem.m_CritNo.setClean();
}

void CallbackItemMapper::setPosTypeTag(basar::VarString const posTypeTag)
{
    m_CallbackItem.m_PosTypeTag = posTypeTag;
    m_CallbackItem.m_PosTypeTag.setClean();
}

void CallbackItemMapper::setPosNoDone(basar::Int32 const posNoDone)
{
    m_CallbackItem.m_PosNoDone = posNoDone;
    m_CallbackItem.m_PosNoDone.setClean();
}

void CallbackItemMapper::setLockTag(basar::VarString const lockTag)
{
    m_CallbackItem.m_LockTag = lockTag;
    m_CallbackItem.m_LockTag.setClean();
}

void CallbackItemMapper::setCallbackStatus(basar::Int16 const callbackStatus)
{
	m_CallbackItem.m_CallbackStatus = callbackStatus;
	m_CallbackItem.m_CallbackStatus.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
