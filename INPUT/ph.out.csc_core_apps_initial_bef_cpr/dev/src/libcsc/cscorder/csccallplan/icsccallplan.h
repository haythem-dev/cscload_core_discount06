#ifndef GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCCALLPLAN_H
#define GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCCALLPLAN_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>

namespace libcsc {
namespace cscorder {
namespace domMod {

typedef libcsc::Property<basar::Int32> Int32;

class ICSCCallplan
{
public:
    virtual ~ICSCCallplan(){};

    virtual Int16 const& getBranchNo() const = 0;
    virtual Int32 const& getCustomerNo() const = 0;
    virtual Int32 const& getDate() const = 0;
    virtual Int32 const& getTimeNow() const = 0;
    virtual Int32 const& getTimeFrom() const = 0;
    virtual Int32 const& getTimeTo() const = 0;
    virtual Int32 const& getCallTime() const = 0;
    virtual Int16 const& getAction() const = 0;

    virtual void setClean() = 0;

    virtual void setBranchNo(Int16 const& branchno) = 0;
    virtual void setCustomerNo(Int32 const& customerno) = 0;
    virtual void setDate(Int32 const& date) = 0;
    virtual void setTimeNow(Int32 const& timenow) = 0;
    virtual void setTimeFrom(Int32 const& timefrom) = 0;
    virtual void setTimeTo(Int32 const& timeto) = 0;
    virtual void setCallTime(Int32 const& calltime) = 0;
    virtual void setAction(Int16 const& action) = 0;
};

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCCALLPLAN_H
