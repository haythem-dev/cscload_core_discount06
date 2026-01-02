/*
 * callbackitemdm.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "callbackitemdm.h"

namespace libcsc {
namespace callback {
namespace domMod {

CallbackItemDM::CallbackItemDM()
{
}

CallbackItemDM::~CallbackItemDM()
{
}

ICallbackItemPtr CallbackItemDM::create()
{
    return ICallbackItemPtr(new CallbackItemDM());
}

Int32 const& CallbackItemDM::getCallbackNo() const
{
    return m_CallbackNo;
}

Int32 const& CallbackItemDM::getCallbackPartNo() const
{
    return m_CallbackPartNo;
}


Int16 const& CallbackItemDM::getDivisionNo() const
{
    return m_DivisionNo;
}

Int32 const& CallbackItemDM::getCritNo() const
{
    return m_CritNo;
}

VarString const& CallbackItemDM::getPosTypeTag() const
{
    return m_PosTypeTag;
}

Int32 const& CallbackItemDM::getPosNo() const
{
    return m_PosNo;
}

Int32 const& CallbackItemDM::getPosNoDone() const
{
    return m_PosNoDone;
}

Int32 const& CallbackItemDM::getCallbackTimeWished() const
{
    return m_CallbackTimeWished;
}

Int32 const& CallbackItemDM::getCallbackDateWished() const
{
    return m_CallbackDateWished;
}

Int16 const& CallbackItemDM::getCallbackTime() const
{
    return m_CallbackTime;
}

VarString const& CallbackItemDM::getState() const
{
    return m_State;
}


VarString const& CallbackItemDM::getLockTag() const
{
    return m_LockTag;
}

Int16 const& CallbackItemDM::getShiftCount() const
{
    return m_ShiftCount;
}

Int16 const& CallbackItemDM::getReasonNo() const
{
    return m_ReasonNo;
}

Int16 const& CallbackItemDM::getCallbackStatus() const
{
	return m_CallbackStatus;
}

VarString const& CallbackItemDM::getReference() const
{
    return m_Reference;
}

void CallbackItemDM::setCallbackNo(Int32 const& callbackNo)
{
    m_CallbackNo = callbackNo;
}

void CallbackItemDM::setCallbackPartNo(Int32 const& callbackPartNo)
{
    m_CallbackPartNo = callbackPartNo;
}

void CallbackItemDM::setDivisionNo(Int16 const& callbackDivisionNo)
{
    m_DivisionNo = callbackDivisionNo;
}

void CallbackItemDM::setCritNo(Int32 const& critNo)
{
    m_CritNo = critNo;
}

void CallbackItemDM::setPosTypeTag(VarString const& posTypeTag)
{
    m_PosTypeTag = posTypeTag;
}

void CallbackItemDM::setPosNo(Int32 const& posNo)
{
    m_PosNo = posNo;
}

void CallbackItemDM::setPosNoDone(Int32 const& posNoDone)
{
    m_PosNoDone = posNoDone;
}

void CallbackItemDM::setCallbackTimeWished(Int32 const& callbackTimeWished)
{
    m_CallbackTimeWished = callbackTimeWished;
}

void CallbackItemDM::setCallbackDateWished(Int32 const& callbackDateWished)
{
    m_CallbackDateWished = callbackDateWished;
}

void CallbackItemDM::setCallbackTime(Int16 const& callbackTime)
{
    m_CallbackTime = callbackTime;
}

void CallbackItemDM::setState(VarString const& state)
{
    m_State = state;
}

void CallbackItemDM::setLockTag(VarString const& lockTag)
{
    m_LockTag = lockTag;
}

void CallbackItemDM::setShiftCount(Int16 const& shiftCount)
{
    m_ShiftCount = shiftCount;
}

void CallbackItemDM::setReasonNo(Int16 const& reasonNo)
{
    m_ReasonNo = reasonNo;
}

void CallbackItemDM::setCallbackStatus(Int16 const& callbackStatus)
{
	m_CallbackStatus = callbackStatus;
}

void CallbackItemDM::setReference(VarString const& reference)
{
    m_Reference = reference;
}

std::ostream& CallbackItemDM::toStream(std::ostream& strm /*= std::cout*/) const
{
    strm
        << "m_CallbackNo=<" << m_CallbackNo << ">"
        << ", m_CallbackPartNo=<" << m_CallbackPartNo << ">"
        << ", m_CritNo=<" << m_CritNo << ">"
        << ", m_PosTypeTag=<" << m_PosTypeTag << ">"
        << ", m_PosNo=<" << m_PosNo << ">"
        << ", m_PosNrDone=<" << m_PosNoDone << ">"
        << ", m_CallbackTimeWished=<" << m_CallbackTimeWished << ">"
        << ", m_CallbackDateWished=<" << m_CallbackDateWished << ">"
        << ", m_CallbackTime=<" << m_CallbackTime << ">"
        << ", m_State=<" << m_State << ">"
        << ", m_LockTag=<" << m_LockTag << ">"
        << ", m_ShiftCount=<" << m_ShiftCount << ">"
        << ", m_ReasonNo=<" << m_ReasonNo << ">"
        << ", m_CallbackStatus=<" << m_CallbackStatus << ">";
    return strm;
}

} // namespace domMod
} // namespace callback
} // namespace libcsc
