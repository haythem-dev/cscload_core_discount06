/*
 * callbackcustomermapper.cpp
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#include "callbackcustomermapper.h"
#include "callback/domainmodule/callbackcustomerdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackCustomerMapper::CallbackCustomerMapper(domMod::ICallbackCustomerPtr callbackCustomer)
    : m_CallbackCustomer(*dynamic_cast<domMod::CallbackCustomerDM*>(callbackCustomer.get()))
{
}

CallbackCustomerMapper::~CallbackCustomerMapper()
{
}

void CallbackCustomerMapper::setBranchNo(basar::Int16 const branchNo)
{
    m_CallbackCustomer.m_BranchNo = branchNo;
    m_CallbackCustomer.m_BranchNo.setClean();
}

void CallbackCustomerMapper::setOrigBranchNo(basar::Int16 const origBranchNo)
{
    m_CallbackCustomer.m_OrigBranchNo = origBranchNo;
    m_CallbackCustomer.m_OrigBranchNo.setClean();
}

void CallbackCustomerMapper::setCustomerNo(basar::Int32 const customerNo)
{
    m_CallbackCustomer.m_CustomerNo = customerNo;
    m_CallbackCustomer.m_CustomerNo.setClean();
}

void CallbackCustomerMapper::setCstBranchNo(basar::Int16 const cstBranchNo)
{
    m_CallbackCustomer.m_CstBranchNo = cstBranchNo;
    m_CallbackCustomer.m_CstBranchNo.setClean();
}

void CallbackCustomerMapper::setPharmacyName(basar::VarString const pharmacyName)
{
    m_CallbackCustomer.m_PharmacyName = pharmacyName;
    m_CallbackCustomer.m_PharmacyName.setClean();
}

void CallbackCustomerMapper::setOwnerName(basar::VarString const ownerName)
{
    m_CallbackCustomer.m_OwnerName = ownerName;
    m_CallbackCustomer.m_OwnerName.setClean();
}

void CallbackCustomerMapper::setZipCode(basar::VarString const zipCode)
{
    m_CallbackCustomer.m_ZipCode = zipCode;
    m_CallbackCustomer.m_ZipCode.setClean();
}

void CallbackCustomerMapper::setCity(basar::VarString const city)
{
    m_CallbackCustomer.m_City = city;
    m_CallbackCustomer.m_City.setClean();
}

void CallbackCustomerMapper::setStreet(basar::VarString const street)
{
    m_CallbackCustomer.m_Street = street;
    m_CallbackCustomer.m_Street.setClean();
}

void CallbackCustomerMapper::setTelefonNo(basar::VarString const telefonNo)
{
    m_CallbackCustomer.m_TelefonNo = telefonNo;
    m_CallbackCustomer.m_TelefonNo.setClean();
}

void CallbackCustomerMapper::setSpeedDialNo(basar::VarString const speedDialNo)
{
    m_CallbackCustomer.m_SpeedDialNo = speedDialNo;
    m_CallbackCustomer.m_SpeedDialNo.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
