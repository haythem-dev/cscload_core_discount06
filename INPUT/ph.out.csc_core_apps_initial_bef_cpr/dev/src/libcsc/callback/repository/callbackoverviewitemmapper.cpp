/*
 * callbackoverviewitemmapper.cpp
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#include "callbackoverviewitemmapper.h"
#include "callback/domainmodule/callbackoverviewitemdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackOverviewItemMapper::CallbackOverviewItemMapper(domMod::ICallbackOverviewItemPtr callbackItem)
    : m_Callback(*dynamic_cast<domMod::CallbackOverviewItemDM*>(callbackItem.get()))
{
}

CallbackOverviewItemMapper::~CallbackOverviewItemMapper()
{
}

void CallbackOverviewItemMapper::setCallbackNo(basar::Int32 const callbackNo)
{
    m_Callback.m_CallbackNo = callbackNo;
    m_Callback.m_CallbackNo.setClean();
}

void CallbackOverviewItemMapper::setBranchNo(basar::Int16 const& branchNo)
{
    m_Callback.m_BranchNo = branchNo;
    m_Callback.m_BranchNo.setClean();
}

void CallbackOverviewItemMapper::setCallbackDate(basar::Int32 const& callbackDate)
{
    m_Callback.m_CallbackDate = callbackDate;
    m_Callback.m_CallbackDate.setClean();
}

void CallbackOverviewItemMapper::setCallbackTime(basar::Int32 const& callbacktime)
{
    m_Callback.m_CallbackTime = callbacktime;
    m_Callback.m_CallbackTime.setClean();
}

void CallbackOverviewItemMapper::setReasonName(basar::VarString const& reasonName)
{
    m_Callback.m_ReasonName = reasonName;
    m_Callback.m_ReasonName.setClean();
}

void CallbackOverviewItemMapper::setPharmacyName(basar::VarString const& pharmacyName)
{
    m_Callback.m_PharmacyName = pharmacyName;
    m_Callback.m_PharmacyName.setClean();
}

void CallbackOverviewItemMapper::setCity(basar::VarString const& city)
{
    m_Callback.m_City = city;
    m_Callback.m_City.setClean();
}

void CallbackOverviewItemMapper::setCritLevel(basar::Int16 const& critLevel)
{
    m_Callback.m_CritLevel = critLevel;
    m_Callback.m_CritLevel.setClean();
}

void CallbackOverviewItemMapper::setCallbackStatus(basar::VarString const& callbackStatus)
{
 	m_Callback.m_CallbackStatus = callbackStatus;
	m_Callback.m_CallbackStatus.setClean();
}

void CallbackOverviewItemMapper::setDivisionName(basar::VarString const& divisionName)
{
	m_Callback.m_DivisionName = divisionName;
	m_Callback.m_DivisionName.setClean();
}

void CallbackOverviewItemMapper::setReference(basar::VarString const& reference) 
{
    m_Callback.m_Reference = reference;
    m_Callback.m_Reference = reference;
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
