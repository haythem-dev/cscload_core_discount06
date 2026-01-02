/*
 * icallback.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACK_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACK_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallback
{
public:
    virtual ~ICallback() {};

    virtual Int32 const& getCritNo() const = 0;
    virtual Int32 const& getCallbackDate() const = 0;
    virtual Int32 const& getCallbackTime() const = 0;
    virtual Int16 const& getCritLevel() const = 0;
    virtual VarString const& getTitle() const = 0;
    virtual Int16 const& getBranchNo() const = 0;
    virtual Int16 const& getCstBranchNo() const = 0;
    virtual Int32 const& getCustomerNo() const = 0;
    virtual VarString const& getCustomerClassTag() const = 0;
    virtual VarString const& getPharmacyName() const = 0;
    virtual VarString const& getOwnerName() const = 0;
    virtual VarString const& getStreet() const = 0;
    virtual VarString const& getCity() const = 0;
    virtual VarString const& getZipCode() const = 0;
    virtual VarString const& getTelefonNo() const = 0;
    virtual VarString const& getSpeedDialNo() const = 0;
    virtual VarString const& getFaxNo() const = 0;
    virtual Int16 const& getCallbackStatus() const = 0;
    virtual VarString const& getReference() const = 0;

public:
    virtual void setCritNo(Int32 const& critNo) = 0;
    virtual void setCallbackDate(Int32 const& callbackDate) = 0;
    virtual void setCallbackTime(Int32 const& callbackTime) = 0;
    virtual void setCritLevel(Int16 const& critLevel) = 0;
    virtual void setTitle(VarString const& title) = 0;
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setCstBranchNo(Int16 const& cstBranchNo) = 0;
    virtual void setCustomerNo(Int32 const& customerNo) = 0;
    virtual void setCustomerClassTag(VarString const& customerClassTag) = 0;
    virtual void setPharmacyName(VarString const& pharmacyName) = 0;
    virtual void setOwnerName(VarString const& ownerName) = 0;
    virtual void setStreet(VarString const& street) = 0;
    virtual void setCity(VarString const& city) = 0;
    virtual void setZipCode(VarString const& zipCode) = 0;
    virtual void setTelefonNo(VarString const& telefonNo) = 0;
    virtual void setSpeedDialNo(VarString const& speedDialNo) = 0;
    virtual void setFaxNo(VarString const& faxNo) = 0;
    virtual void setCallbackStatus(Int16 const& callbackStatus) = 0;
    virtual void setReference(VarString const& reference) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACK_H
