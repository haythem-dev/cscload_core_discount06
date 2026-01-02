/*
 * callbackdm.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDM_H

#include "icallbackptr.h"
#include "icallback.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {

namespace repo {
class CallbackMapper;
}

namespace domMod {

class CallbackDM : public ICallback
{
    // because of OR mapping
    friend class repo::CallbackMapper;

public:
    virtual ~CallbackDM();

    static ICallbackPtr create();

    virtual Int32 const& getCritNo() const;
    virtual Int32 const& getCallbackDate() const;
    virtual Int32 const& getCallbackTime() const;
    virtual Int16 const& getCritLevel() const;
    virtual VarString const& getTitle() const;
    virtual Int16 const& getBranchNo() const;
    virtual Int16 const& getCstBranchNo() const;
    virtual Int32 const& getCustomerNo() const;
    virtual VarString const& getCustomerClassTag() const;
    virtual VarString const& getPharmacyName() const;
    virtual VarString const& getOwnerName() const;
    virtual VarString const& getStreet() const;
    virtual VarString const& getCity() const;
    virtual VarString const& getZipCode() const;
    virtual VarString const& getTelefonNo() const;
    virtual VarString const& getSpeedDialNo() const;
    virtual VarString const& getFaxNo() const;
    virtual Int16 const& getCallbackStatus() const;
    virtual VarString const& getReference() const;

public:
    virtual void setCritNo(Int32 const& callbackDate);
    virtual void setCallbackDate(Int32 const& callbackDate);
    virtual void setCallbackTime(Int32 const& callbackTime);
    virtual void setCritLevel(Int16 const& critLevel);
    virtual void setTitle(VarString const& title);
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setCstBranchNo(Int16 const& cstBranchNo);
    virtual void setCustomerNo(Int32 const& customerNo);
    virtual void setCustomerClassTag(VarString const& customerClassTag);
    virtual void setPharmacyName(VarString const& pharmacyName);
    virtual void setOwnerName(VarString const& ownerName);
    virtual void setStreet(VarString const& street);
    virtual void setCity(VarString const& city);
    virtual void setZipCode(VarString const& zipCode);
    virtual void setTelefonNo(VarString const& telefonNo);
    virtual void setSpeedDialNo(VarString const& speedDialNo);
    virtual void setFaxNo(VarString const& faxNo);
    virtual void setCallbackStatus(Int16 const& callbackStatus);
    virtual void setReference(VarString const& reference);

protected:
    CallbackDM();

private:
    Int32 m_CritNo;
    Int32 m_CallbackDate;
    Int32 m_CallbackTime;
    Int16 m_CritLevel;
    VarString m_Title;
    Int16 m_BranchNo;
    Int16 m_CstBranchNo;
    Int32 m_CustomerNo;
    VarString m_CustomerClassTag;
    VarString m_PharmacyName;
    VarString m_OwnerName;
    VarString m_Street;
    VarString m_City;
    VarString m_ZipCode;
    VarString m_TelefonNo;
    VarString m_SpeedDialNo;
    VarString m_FaxNo;
    Int16 m_CallbackStatus;
    VarString m_Reference;

    CallbackDM(const CallbackDM&);
    CallbackDM& operator=(const CallbackDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDM_H
