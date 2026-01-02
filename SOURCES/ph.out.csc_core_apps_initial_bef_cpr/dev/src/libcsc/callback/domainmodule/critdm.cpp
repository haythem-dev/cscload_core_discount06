/*
 * critdm.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "critdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CritDM::CritDM()
{
}

CritDM::~CritDM()
{
}

ICritPtr CritDM::create()
{
    return ICritPtr(new CritDM());
}

Int32 const& CritDM::getCritNo() const
{
    return m_CritNo;
}

Int16 const& CritDM::getBranchNo() const
{
    return m_BranchNo;
}

Int32 const& CritDM::getCustomerNo() const
{
    return m_CustomerNo;
}

Int16 const& CritDM::getCstBranchNo() const
{
    return m_CstBranchNo;
}

Int32 const& CritDM::getDate() const
{
    return m_Date;
}

Int32 const& CritDM::getTime() const
{
    return m_Time;
}

Int32 const& CritDM::getUId() const
{
    return m_UId;
}

VarString const& CritDM::getTitle() const
{
    return m_Title;
}

Int16 const& CritDM::getCritLevel() const
{
    return m_CritLevel;
}

void CritDM::setCritNo(Int32 const& critNo)
{
    m_CritNo = critNo;
}

void CritDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CritDM::setCustomerNo(Int32 const& customerNo)
{
    m_CustomerNo = customerNo;
}

void CritDM::setCstBranchNo(Int16 const& cstBranchNo)
{
    m_CstBranchNo = cstBranchNo;
}

void CritDM::setDate(Int32 const& date)
{
    m_Date = date;
}

void CritDM::setTime(Int32 const& time)
{
    m_Time = time;
}

void CritDM::setUId(Int32 const& uid)
{
    m_UId = uid;
}

void CritDM::setTitle(VarString const& title)
{
    m_Title = title;
}

void CritDM::setCritLevel(Int16 const& critLevel)
{
    m_CritLevel = critLevel;
}

std::ostream& CritDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_CritNo=<" << m_CritNo << ">"
        << ", m_BranchNo=<" << m_BranchNo << ">"
        << ", m_CustomerNo=<" << m_CustomerNo << ">"
        << ", m_Date=<" << m_Date << ">"
        << ", m_Time=<" << m_Time << ">"
        << ", m_UId=<" << m_UId << ">"
        << ", m_Title=<" << m_Title << ">"
        << ", m_CritLevel=<" << m_CritLevel << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
