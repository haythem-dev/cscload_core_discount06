/*
 * callbackdm.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "callbackdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackDM::CallbackDM()
{
}

CallbackDM::~CallbackDM()
{
}

ICallbackPtr CallbackDM::create()
{
    return ICallbackPtr(new CallbackDM());
}

Int32 const& CallbackDM::getCritNo() const
{
    return m_CritNo;
}

Int32 const& CallbackDM::getCallbackDate() const
{
    return m_CallbackDate;
}

Int32 const& CallbackDM::getCallbackTime() const
{
    return m_CallbackTime;
}

Int16 const& CallbackDM::getCritLevel() const
{
    return m_CritLevel;
}

VarString const& CallbackDM::getTitle() const
{
    return m_Title;
}

Int16 const& CallbackDM::getBranchNo() const
{
    return m_BranchNo;
}

Int16 const& CallbackDM::getCstBranchNo() const
{
    return m_CstBranchNo;
}

Int32 const& CallbackDM::getCustomerNo() const
{
    return m_CustomerNo;
}

VarString const& CallbackDM::getCustomerClassTag() const
{
    return m_CustomerClassTag;
}

VarString const& CallbackDM::getPharmacyName() const
{
    return m_PharmacyName;
}

VarString const& CallbackDM::getOwnerName() const
{
    return m_OwnerName;
}

VarString const& CallbackDM::getStreet() const
{
    return m_Street;
}

VarString const& CallbackDM::getCity() const
{
    return m_City;
}

VarString const& CallbackDM::getZipCode() const
{
    return m_ZipCode;
}

VarString const& CallbackDM::getTelefonNo() const
{
    return m_TelefonNo;
}

VarString const& CallbackDM::getSpeedDialNo() const
{
    return m_SpeedDialNo;
}

VarString const& CallbackDM::getFaxNo() const
{
    return m_FaxNo;
}

Int16 const& CallbackDM::getCallbackStatus() const
{
	return m_CallbackStatus;
}

VarString const& CallbackDM::getReference() const
{
    return m_Reference;
}

void CallbackDM::setCritNo(Int32 const& critNo)
{
    m_CritNo = critNo;
}

void CallbackDM::setCallbackDate(Int32 const& callbackDate)
{
    m_CallbackDate = callbackDate;
}

void CallbackDM::setCallbackTime(Int32 const& callbackTime)
{
    m_CallbackTime = callbackTime;
}

void CallbackDM::setCritLevel(Int16 const& critLevel)
{
    m_CritLevel = critLevel;
}

void CallbackDM::setTitle(VarString const& title)
{
    m_Title = title;
}

void CallbackDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CallbackDM::setCstBranchNo(Int16 const& cstBranchNo)
{
    m_CstBranchNo = cstBranchNo;
}

void CallbackDM::setCustomerNo(Int32 const& customerNo)
{
    m_CustomerNo = customerNo;
}

void CallbackDM::setCustomerClassTag(VarString const& customerClassTag)
{
    m_CustomerClassTag = customerClassTag;
}

void CallbackDM::setPharmacyName(VarString const& pharmacyName)
{
    m_PharmacyName = pharmacyName;
}

void CallbackDM::setOwnerName(VarString const& ownerName)
{
    m_OwnerName = ownerName;
}

void CallbackDM::setStreet(VarString const& street)
{
    m_Street = street;
}

void CallbackDM::setCity(VarString const& city)
{
    m_City = city;
}

void CallbackDM::setZipCode(VarString const& zipCode)
{
    m_ZipCode = zipCode;
}

void CallbackDM::setTelefonNo(VarString const& telefonNo)
{
    m_TelefonNo = telefonNo;
}

void CallbackDM::setSpeedDialNo(VarString const& speedDialNo)
{
    m_SpeedDialNo = speedDialNo;
}

void CallbackDM::setFaxNo(VarString const& faxNo)
{
    m_FaxNo = faxNo;
}

void CallbackDM::setCallbackStatus(Int16 const& callbackStatus)
{
	m_CallbackStatus = callbackStatus;
}

void CallbackDM::setReference(VarString const& reference)
{
    m_Reference = reference;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
