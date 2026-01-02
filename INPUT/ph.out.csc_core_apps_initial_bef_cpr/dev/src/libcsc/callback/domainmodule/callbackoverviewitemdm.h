/*
 * callbackoverviewitemdm.h
 *
 *  Created on: 22.05.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDM_H

#include "icallbackoverviewitemptr.h"
#include "icallbackoverviewitem.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {

namespace repo {
class CallbackOverviewItemMapper;
}

namespace domMod {

class CallbackOverviewItemDM : public ICallbackOverviewItem
{
    // because of OR mapping
    friend class repo::CallbackOverviewItemMapper;

public:
    virtual ~CallbackOverviewItemDM();

    static ICallbackOverviewItemPtr create();

    virtual Int32 const& getCallbackNo() const;
    virtual Int16 const& getBranchNo() const;
    virtual Int32 const& getCallbackDate() const;
    virtual Int32 const& getCallbackTime() const;
    virtual VarString const& getReasonName() const;
    virtual VarString const& getPharmacyName() const;
    virtual VarString const& getCity() const;
    virtual Int16 const& getCritLevel() const;
    virtual VarString const& getCallbackStatus() const;
    virtual VarString const& getDivisionName() const;
    virtual VarString const& getReference() const;

public:
    virtual void setCallbackNo(Int32 const& callbackNo);
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setCallbackDate(Int32 const& callbackDate);
    virtual void setCallbackTime(Int32 const& callbackTime);
    virtual void setReasonName(VarString const& reasonName);
    virtual void setPharmacyName(VarString const& pharmacyName);
    virtual void setCity(VarString const& city);
    virtual void setCritLevel(Int16 const& critLevel);
    virtual void setCallbackStatus(VarString const& callbackStatus);
    virtual void setDivisionName(VarString const& divisionName);
    virtual void setReference(VarString const& reference);

protected:
    CallbackOverviewItemDM();

private:
    Int32 m_CallbackNo;
    Int16 m_BranchNo;
    Int32 m_CallbackDate;
    Int32 m_CallbackTime;
    VarString m_ReasonName;
    VarString m_PharmacyName;
    VarString m_City;
    Int16 m_CritLevel;
    VarString m_CallbackStatus;
    VarString m_DivisionName;
    VarString m_Reference;

    CallbackOverviewItemDM(const CallbackOverviewItemDM&);
    CallbackOverviewItemDM& operator=(const CallbackOverviewItemDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKOVERVIEWITEMDM_H
