/*
 * callbackmapper.cpp
 *
 *  Created on: 13.05.2016
 *  Author: sebastian.barth
 */

#include "callbackmapper.h"
#include "callback/domainmodule/callbackdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackMapper::CallbackMapper(domMod::ICallbackPtr callbackItem)
    : m_Callback(*dynamic_cast<domMod::CallbackDM*>(callbackItem.get()))
{
}

CallbackMapper::~CallbackMapper()
{
}

void CallbackMapper::setCritNo(basar::Int32 const& critNo)
{
    m_Callback.m_CritNo = critNo;
    m_Callback.m_CritNo.setClean();
}

void CallbackMapper::setCallbackDate(basar::Int32 const& callbackDate)
{
    m_Callback.m_CallbackDate = callbackDate;
    m_Callback.m_CallbackDate.setClean();
}

void CallbackMapper::setCallbackTime(basar::Int32 const& callbacktime)
{
    m_Callback.m_CallbackTime = callbacktime;
    m_Callback.m_CallbackTime.setClean();
}

void CallbackMapper::setCritLevel(basar::Int16 const& critLevel)
{
    m_Callback.m_CritLevel = critLevel;
    m_Callback.m_CritLevel.setClean();
}

void CallbackMapper::setTitle(basar::VarString const& title)
{
    m_Callback.m_Title = title;
    m_Callback.m_Title.setClean();
}

void CallbackMapper::setBranchNo(basar::Int16 const& branchNo)
{
    m_Callback.m_BranchNo = branchNo;
    m_Callback.m_BranchNo.setClean();
}

void CallbackMapper::setCstBranchNo(basar::Int16 const& cstBranchNo)
{
    m_Callback.m_CstBranchNo = cstBranchNo;
    m_Callback.m_CstBranchNo.setClean();
}

void CallbackMapper::setCustomerNo(basar::Int32 const& customerNo)
{
    m_Callback.m_CustomerNo = customerNo;
    m_Callback.m_Title.setClean();
}

void CallbackMapper::setCustomerClassTag(basar::VarString const& customerClassTag)
{
    m_Callback.m_CustomerClassTag = customerClassTag;
    m_Callback.m_CustomerClassTag.setClean();
}

void CallbackMapper::setPharmacyName(basar::VarString const& pharmacyName)
{
    m_Callback.m_PharmacyName = pharmacyName;
    m_Callback.m_PharmacyName.setClean();
}

void CallbackMapper::setOwnerName(basar::VarString const& ownerName)
{
    m_Callback.m_OwnerName = ownerName;
    m_Callback.m_OwnerName.setClean();
}

void CallbackMapper::setStreet(basar::VarString const& street)
{
    m_Callback.m_Street = street;
    m_Callback.m_Street.setClean();
}

void CallbackMapper::setCity(basar::VarString const& city)
{
    m_Callback.m_City = city;
    m_Callback.m_City.setClean();
}

void CallbackMapper::setZipCode(basar::VarString const& zipCode)
{
    m_Callback.m_ZipCode = zipCode;
    m_Callback.m_ZipCode.setClean();
}

void CallbackMapper::setTelefonNo(basar::VarString const& telefonNo)
{
    m_Callback.m_TelefonNo = telefonNo;
    m_Callback.m_TelefonNo.setClean();
}

void CallbackMapper::setSpeedDialNo(basar::VarString const& speedDialNo)
{
    m_Callback.m_SpeedDialNo = speedDialNo;
    m_Callback.m_SpeedDialNo.setClean();
}

void CallbackMapper::setFaxNo(basar::VarString const& faxNo)
{
    m_Callback.m_FaxNo = faxNo;
    m_Callback.m_FaxNo.setClean();
}

void CallbackMapper::setCallbackStatus(basar::Int16 const& callbackStatus)
{
	m_Callback.m_CallbackStatus = callbackStatus;
	m_Callback.m_CallbackStatus.setClean();
}

void CallbackMapper::setReference(basar::VarString const& reference)
{
    m_Callback.m_Reference = reference;
    m_Callback.m_Reference.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
