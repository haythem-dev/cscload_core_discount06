#include "csccallplan.h"
#include "csccallplanptr.h"

namespace libcsc {
namespace cscorder {
namespace domMod {


CSCCallplan::CSCCallplan()
{
    m_BranchNo = 0;
    m_CustomerNo = 0;
    m_Date = 0;
    m_TimeNow = 0;
    m_TimeFrom = 0;
    m_TimeTo = 0;
    m_CallTime = 0;
    m_Action = 0;
}

CSCCallplan::~CSCCallplan()
{
}

ICSCCallplanPtr CSCCallplan::create()
{
    return ICSCCallplanPtr(new CSCCallplan());
}

void CSCCallplan::setClean()
{
    m_BranchNo.setClean();
    m_CustomerNo.setClean();
    m_Date.setClean();
    m_TimeNow.setClean();
    m_TimeFrom.setClean();
    m_TimeTo.setClean();
    m_CallTime.setClean();
    m_Action.setClean();
}

void CSCCallplan::setBranchNo(Int16 const& branchno)
{
    m_BranchNo = branchno;
}

void CSCCallplan::setCustomerNo(Int32 const& customerno)
{
    m_CustomerNo = customerno;
}

void CSCCallplan::setDate(Int32 const& date)
{
    m_Date = date;
}

void CSCCallplan::setTimeNow(Int32 const& timenow)
{
    m_TimeNow = timenow;
}

void CSCCallplan::setTimeFrom(Int32 const& timefrom)
{
    m_TimeFrom = timefrom;
}

void CSCCallplan::setTimeTo(Int32 const& timeto)
{
    m_TimeTo = timeto;
}

void CSCCallplan::setCallTime(Int32 const& calltime)
{
    m_CallTime = calltime;
}

void CSCCallplan::setAction(Int16 const& action)
{
    m_Action = action;
}

Int16 const& CSCCallplan::getBranchNo() const
{
    return m_BranchNo;
}

Int32 const& CSCCallplan::getCustomerNo() const
{
    return m_CustomerNo;
}

Int32 const& CSCCallplan::getDate() const
{
    return m_Date;
}

Int32 const& CSCCallplan::getTimeNow() const
{
    return m_TimeNow;
}

Int32 const& CSCCallplan::getTimeFrom() const
{
    return m_TimeFrom;
}

Int32 const& CSCCallplan::getTimeTo() const
{
    return m_TimeTo;
}

Int32 const& CSCCallplan::getCallTime() const
{
    return m_CallTime;
}

Int16 const& CSCCallplan::getAction() const
{
    return m_Action;
}

} // namespace domMod
} // namespace cscorder
} // namespace libcsc
