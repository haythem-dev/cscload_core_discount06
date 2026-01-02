/*
 * callbackoverviewitemdm.cpp
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#include "callbackoverviewitemdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackOverviewItemDM::CallbackOverviewItemDM()
{
}

CallbackOverviewItemDM::~CallbackOverviewItemDM()
{
}

ICallbackOverviewItemPtr CallbackOverviewItemDM::create()
{
    return ICallbackOverviewItemPtr(new CallbackOverviewItemDM());
}

Int32 const& CallbackOverviewItemDM::getCallbackNo() const
{
    return m_CallbackNo;
}

Int16 const& CallbackOverviewItemDM::getBranchNo() const
{
    return m_BranchNo;
}

Int32 const& CallbackOverviewItemDM::getCallbackDate() const
{
    return m_CallbackDate;
}

Int32 const& CallbackOverviewItemDM::getCallbackTime() const
{
    return m_CallbackTime;
}

VarString const& CallbackOverviewItemDM::getReasonName() const
{
    return m_ReasonName;
}

VarString const& CallbackOverviewItemDM::getPharmacyName() const
{
    return m_PharmacyName;
}

VarString const& CallbackOverviewItemDM::getCity() const
{
    return m_City;
}

Int16 const& CallbackOverviewItemDM::getCritLevel() const
{
    return m_CritLevel;
}

VarString const& CallbackOverviewItemDM::getCallbackStatus() const
{
	return m_CallbackStatus;
}

VarString const& CallbackOverviewItemDM::getDivisionName() const
{
	return m_DivisionName;
}

VarString const& CallbackOverviewItemDM::getReference() const
{
    return m_Reference;
}

void CallbackOverviewItemDM::setCallbackNo(Int32 const& callbackNo)
{
    m_CallbackNo = callbackNo;
}

void CallbackOverviewItemDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CallbackOverviewItemDM::setCallbackDate(Int32 const& callbackDate)
{
    m_CallbackDate = callbackDate;
}

void CallbackOverviewItemDM::setCallbackTime(Int32 const& callbackTime)
{
    m_CallbackTime = callbackTime;
}

void CallbackOverviewItemDM::setReasonName(VarString const& reasonName)
{
    m_ReasonName = reasonName;
}

void CallbackOverviewItemDM::setPharmacyName(VarString const& pharmacyName)
{
    m_PharmacyName = pharmacyName;
}

void CallbackOverviewItemDM::setCity(VarString const& city)
{
    m_City = city;
}

void CallbackOverviewItemDM::setCritLevel(Int16 const& critLevel)
{
    m_CritLevel = critLevel;
}

void CallbackOverviewItemDM::setCallbackStatus(VarString const& callbackStatus)
{
	m_CallbackStatus = callbackStatus;
}

void CallbackOverviewItemDM::setDivisionName(VarString const& divisionName)
{
	m_DivisionName = divisionName;
}

void CallbackOverviewItemDM::setReference(VarString const& reference) 
{
    m_Reference = reference;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
