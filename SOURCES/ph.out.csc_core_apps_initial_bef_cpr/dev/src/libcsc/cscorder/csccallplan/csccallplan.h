#ifndef GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLAN_H
#define GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLAN_H

#include "icsccallplanptr.h"
#include "icsccallplan.h"

namespace libcsc {
namespace cscorder {
namespace repo {
    class CSCCallplanMapperBase;
}
namespace domMod {

class CSCCallplan : public ICSCCallplan
{
    // because of OR mapping
    friend class repo::CSCCallplanMapperBase;

public:
    CSCCallplan();
    virtual ~CSCCallplan();

    static ICSCCallplanPtr create();

    virtual Int16 const& getBranchNo() const;
    virtual Int32 const& getCustomerNo() const;
    virtual Int32 const& getDate() const;
    virtual Int32 const& getTimeNow() const;
    virtual Int32 const& getTimeFrom() const;
    virtual Int32 const& getTimeTo() const;
    virtual Int32 const& getCallTime() const;
    virtual Int16 const& getAction() const;

    virtual void setClean();

    virtual void setBranchNo(Int16 const& branchno);
    virtual void setCustomerNo(Int32 const& customerno);
    virtual void setDate(Int32 const& date);
    virtual void setTimeNow(Int32 const& timenow);
    virtual void setTimeFrom(Int32 const& timefrom);
    virtual void setTimeTo(Int32 const& timeto);
    virtual void setCallTime(Int32 const& calltime);
    virtual void setAction(Int16 const& action);

private:
    Int16 m_BranchNo;
    Int32 m_CustomerNo;
    Int32 m_Date;
    Int32 m_TimeNow;
    Int32 m_TimeFrom;
    Int32 m_TimeTo;
    Int32 m_CallTime;
    Int16 m_Action;

    CSCCallplan(const CSCCallplan&);
    CSCCallplan& operator=(const CSCCallplan&);
};

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_DOMMOD_CSCORDER_CSCCALLPLAN_H
