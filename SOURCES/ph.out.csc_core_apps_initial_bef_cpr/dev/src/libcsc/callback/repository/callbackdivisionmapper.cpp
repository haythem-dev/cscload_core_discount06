/*
 * callbackdivisionmapper.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "callbackdivisionmapper.h"
#include "callback/domainmodule/callbackdivisiondm.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace callback {
namespace repo {

CallbackDivisionMapper::CallbackDivisionMapper(domMod::ICallbackDivisionPtr callbackDivision)
    : m_CallbackDivision(*dynamic_cast<domMod::CallbackDivisionDM*>(callbackDivision.get()))
{
}

CallbackDivisionMapper::~CallbackDivisionMapper()
{
}

void CallbackDivisionMapper::setBranchNo(basar::Int16 const branchNo)
{
    m_CallbackDivision.m_BranchNo = branchNo;
    m_CallbackDivision.m_BranchNo.setClean();
}

void CallbackDivisionMapper::setDivisionNo(basar::Int16 const divisionNo)
{
    m_CallbackDivision.m_DivisionNo = divisionNo;
    m_CallbackDivision.m_DivisionNo.setClean();
}

void CallbackDivisionMapper::setDivisionName(basar::VarString const divisionName)
{
    m_CallbackDivision.m_DivisionName = divisionName;
    m_CallbackDivision.m_DivisionName.setClean();
}

void CallbackDivisionMapper::setMailingList(basar::VarString const mailingList)
{
    m_CallbackDivision.m_MailingList = mailingList;
    m_CallbackDivision.m_MailingList.setClean();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc
