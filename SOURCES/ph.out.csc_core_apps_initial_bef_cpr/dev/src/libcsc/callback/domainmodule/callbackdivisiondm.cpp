/*
 * callbackdivisiondm.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "callbackdivisiondm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackDivisionDM::CallbackDivisionDM()
{
}

CallbackDivisionDM::~CallbackDivisionDM()
{
}

ICallbackDivisionPtr CallbackDivisionDM::create()
{
    return ICallbackDivisionPtr(new CallbackDivisionDM());
}

Int16 const& CallbackDivisionDM::getBranchNo() const
{
    return m_BranchNo;
}

Int16 const& CallbackDivisionDM::getDivisionNo() const
{
    return m_DivisionNo;
}

VarString const& CallbackDivisionDM::getDivisionName() const
{
    return m_DivisionName;
}

VarString const& CallbackDivisionDM::getMailingList() const
{
    return m_MailingList;
}

void CallbackDivisionDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CallbackDivisionDM::setDivisionNo(Int16 const& divisionNo)
{
    m_DivisionNo = divisionNo;
}

void CallbackDivisionDM::setDivisionName(VarString const& divisionName)
{
    m_DivisionName = divisionName;
}

void CallbackDivisionDM::setMailingList(VarString const& mailingList)
{
    m_MailingList = mailingList;
}

std::ostream& CallbackDivisionDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_BranchNo=<" << m_BranchNo << ">"
        << ", m_DivisionNo=<" << m_DivisionNo << ">"
        << ", m_DivisionName=<" << m_DivisionName << ">"
        << ", m_MailingList=<" << m_MailingList << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
