/*
 * callbackreasondm.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "callbackreasondm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackReasonDM::CallbackReasonDM()
{
}

CallbackReasonDM::~CallbackReasonDM()
{
}

ICallbackReasonPtr CallbackReasonDM::create()
{
    return ICallbackReasonPtr(new CallbackReasonDM());
}

Int16 const& CallbackReasonDM::getBranchNo() const
{
    return m_BranchNo;
}

Int16 const& CallbackReasonDM::getDivisionNo() const
{
    return m_DivisionNo;
}

Int16 const& CallbackReasonDM::getReasonNo() const
{
    return m_ReasonNo;
}

VarString const& CallbackReasonDM::getReasonName() const
{
    return m_ReasonName;
}

VarString const& CallbackReasonDM::getMailingList() const
{
    return m_MailingList;
}

void CallbackReasonDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CallbackReasonDM::setDivisionNo(Int16 const& divisionNo)
{
    m_DivisionNo = divisionNo;
}

void CallbackReasonDM::setReasonNo(Int16 const& reasonNo)
{
    m_ReasonNo = reasonNo;
}

void CallbackReasonDM::setReasonName(VarString const& reasonName)
{
    m_ReasonName = reasonName;
}

void CallbackReasonDM::setMailingList(VarString const& mailingList)
{
    m_MailingList = mailingList;
}

std::ostream& CallbackReasonDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_BranchNo=<" << m_BranchNo << ">"
        << ", m_DivisionNo=<" << m_DivisionNo << ">"
        << ", m_ReasonNo=<" << m_ReasonNo << ">"
        << ", m_ReasonName=<" << m_ReasonName << ">"
        << ", m_MailingList=<" << m_MailingList << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
