/*
 * icallbackreason.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKREASON_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKREASON_H

#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackReason : public base::IDomainModule
{
public:
    virtual ~ICallbackReason() {};

    virtual Int16 const& getBranchNo() const = 0;
    virtual Int16 const& getDivisionNo() const = 0;
    virtual Int16 const& getReasonNo() const = 0;
    virtual VarString const& getReasonName() const = 0;
    virtual VarString const& getMailingList() const = 0;

public:
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setDivisionNo(Int16 const& divisionNo) = 0;
    virtual void setReasonNo(Int16 const& reasonNo) = 0;
    virtual void setReasonName(VarString const& reasonName) = 0;
    virtual void setMailingList(VarString const& mailingList) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKREASON_H
