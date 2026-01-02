/*
 * critposdm.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "critposdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CritPosDM::CritPosDM()
{
}

CritPosDM::~CritPosDM()
{
}

ICritPosPtr CritPosDM::create()
{
    return ICritPosPtr(new CritPosDM());
}

Int32 const& CritPosDM::getPosNo() const
{
    return m_PosNo;
}

VarString const& CritPosDM::getPosTypeTag() const
{
    return m_PosTypeTag;
}

Int32 const& CritPosDM::getCritNo() const
{
    return m_CritNo;
}

VarString const& CritPosDM::getText() const
{
    return m_Text;
}

Int32 const& CritPosDM::getUId() const
{
    return m_UId;
}

Int16 const& CritPosDM::getBranchNo() const
{
    return m_BranchNo;
}

Int32 const& CritPosDM::getDate() const
{
    return m_Date;
}

Int32 const& CritPosDM::getTime() const
{
    return m_Time;
}

VarString const& CritPosDM::getWindowsUserId() const
{
    return m_WindowsUserId;
}

Int16 const& CritPosDM::getSourceApplication() const
{
    return m_SourceApplication;
}

void CritPosDM::setPosNo(Int32 const& posNo)
{
    m_PosNo = posNo;
}

void CritPosDM::setPosTypeTag(VarString const& posTypeTag)
{
    m_PosTypeTag = posTypeTag;
}

void CritPosDM::setCritNo(Int32 const& critNo)
{
    m_CritNo = critNo;
}

void CritPosDM::setText(VarString const& text)
{
    m_Text = text;
}

void CritPosDM::setUId(Int32 const& uId)
{
    m_UId = uId;
}

void CritPosDM::setBranchNo(Int16 const& branchNo)
{
    m_BranchNo = branchNo;
}

void CritPosDM::setDate(Int32 const& date)
{
    m_Date = date;
}

void CritPosDM::setTime(Int32 const& time)
{
    m_Time = time;
}

void CritPosDM::setWindowsUserId(VarString const& windowsUserId)
{
    m_WindowsUserId = windowsUserId;
}

void CritPosDM::setSourceApplication(Int16 const& sourceApplication)
{
    m_SourceApplication = sourceApplication;
}

std::ostream& CritPosDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_PosNo=<" << m_PosNo << ">"
        << ", m_PosTypeTag=<" << m_PosTypeTag << ">"
        << ", m_CritNo=<" << m_CritNo << ">"
        << ", m_Text=<" << m_Text << ">"
        << ", m_UId=<" << m_UId << ">"
        << ", m_BranchNo=<" << m_BranchNo << ">"
        << ", m_Date=<" << m_Date << ">"
        << ", m_Time=<" << m_Time << ">"
        << ", m_WindowsUserId=<" << m_WindowsUserId << ">"
        << ", m_SourceApplication=<" << m_SourceApplication << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
