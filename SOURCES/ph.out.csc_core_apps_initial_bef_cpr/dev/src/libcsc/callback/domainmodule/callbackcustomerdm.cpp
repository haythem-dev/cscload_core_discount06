/*
 * callbackcustomerdm.cpp
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#include "callbackcustomerdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackCustomerDM::CallbackCustomerDM()
{
}

CallbackCustomerDM::~CallbackCustomerDM()
{
}

ICallbackCustomerPtr CallbackCustomerDM::create()
{
    return ICallbackCustomerPtr(new CallbackCustomerDM());
}

Int16 const& CallbackCustomerDM::getBranchNo() const
{
    return m_BranchNo;
}

Int16 const& CallbackCustomerDM::getOrigBranchNo() const
{
    return m_OrigBranchNo;
}

Int32 const& CallbackCustomerDM::getCustomerNo() const
{
    return m_CustomerNo;
}

Int16 const& CallbackCustomerDM::getCstBranchNo() const
{
    return m_CstBranchNo;
}

VarString const& CallbackCustomerDM::getPharmacyName() const
{
    return m_PharmacyName;
}

VarString const& CallbackCustomerDM::getOwnerName() const
{
    return m_OwnerName;
}

VarString const& CallbackCustomerDM::getZipCode() const
{
    return m_ZipCode;
}

VarString const& CallbackCustomerDM::getCity() const
{
    return m_City;
}

VarString const& CallbackCustomerDM::getStreet() const
{
    return m_Street;
}

VarString const& CallbackCustomerDM::getTelefonNo() const
{
    return m_TelefonNo;
}

VarString const& CallbackCustomerDM::getSpeedDialNo() const
{
    return m_SpeedDialNo;
}

void CallbackCustomerDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CallbackCustomerDM::setOrigBranchNo(Int16 const& origBranchNo)
{
    m_OrigBranchNo = origBranchNo;
}

void CallbackCustomerDM::setCustomerNo(Int32 const& customerNo)
{
    m_CustomerNo = customerNo;
}

void CallbackCustomerDM::setCstBranchNo(Int16 const& cstBranchNo)
{
    m_CstBranchNo = cstBranchNo;
}

void CallbackCustomerDM::setPharmacyName(VarString const& pharmacyName)
{
    m_PharmacyName = pharmacyName;
}

void CallbackCustomerDM::setOwnerName(VarString const& ownerName)
{
    m_OwnerName = ownerName;
}

void CallbackCustomerDM::setZipCode(VarString const& zipCode)
{
    m_ZipCode = zipCode;
}

void CallbackCustomerDM::setCity(VarString const& city)
{
    m_City = city;
}

void CallbackCustomerDM::setStreet(VarString const& street)
{
    m_Street = street;
}

void CallbackCustomerDM::setTelefonNo(VarString const& telefonNo)
{
    m_TelefonNo = telefonNo;
}

void CallbackCustomerDM::setSpeedDialNo(VarString const& speedDialNo)
{
    m_SpeedDialNo = speedDialNo;
}

std::ostream& CallbackCustomerDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_BranchNo=<" << m_BranchNo << ">"
        << ", m_OrigBranchNo=<" << m_OrigBranchNo << ">"
        << ", m_CustomerNo=<" << m_CustomerNo << ">"
        << ", m_CstBranchNo=<" << m_CstBranchNo << ">"
        << ", m_PharmacyName=<" << m_PharmacyName << ">"
        << ", m_OwnerName=<" << m_OwnerName << ">"
        << ", m_ZipCode=<" << m_ZipCode << ">"
        << ", m_City=<" << m_City << ">"
        << ", m_Street=<" << m_Street << ">"
        << ", m_TelefonNo=<" << m_TelefonNo << ">"
        << ", m_SpeedDialNo=<" << m_SpeedDialNo << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
