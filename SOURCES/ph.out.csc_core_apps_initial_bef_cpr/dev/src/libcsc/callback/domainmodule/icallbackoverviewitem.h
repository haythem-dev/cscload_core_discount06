/*
 * icallbackoverviewitem.h
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKOVERVIEWITEM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKOVERVIEWITEM_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackOverviewItem
{
public:
    virtual ~ICallbackOverviewItem() {};

    virtual Int32 const& getCallbackNo() const = 0;
    virtual Int16 const& getBranchNo() const = 0;
    virtual Int32 const& getCallbackDate() const = 0;
    virtual Int32 const& getCallbackTime() const = 0;
    virtual VarString const& getReasonName() const = 0;
    virtual VarString const& getPharmacyName() const = 0;
    virtual VarString const& getCity() const = 0;
    virtual Int16 const& getCritLevel() const = 0;
    virtual VarString const& getCallbackStatus() const = 0;
    virtual VarString const& getDivisionName() const = 0;
    virtual VarString const& getReference() const = 0;

public:
    virtual void setCallbackNo(Int32 const& callbackNo) = 0;
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setCallbackDate(Int32 const& callbackDate) = 0;
    virtual void setCallbackTime(Int32 const& callbackTime) = 0;
    virtual void setReasonName(VarString const& reasonName) = 0;
    virtual void setPharmacyName(VarString const& pharmacyName) = 0;
    virtual void setCity(VarString const& city) = 0;
    virtual void setCritLevel(Int16 const& critLevel) = 0;
    virtual void setCallbackStatus(VarString const& callbackStatus) = 0;
    virtual void setDivisionName(VarString const& divisionName) = 0;
    virtual void setReference(VarString const& reference) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKOVERVIEWITEM_H
