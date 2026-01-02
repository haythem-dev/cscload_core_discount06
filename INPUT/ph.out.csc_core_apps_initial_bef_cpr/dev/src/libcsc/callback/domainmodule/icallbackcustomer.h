/*
 * icallbackcustomer.h
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMER_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMER_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICallbackCustomer : public base::IDomainModule
{
public:
    virtual ~ICallbackCustomer() {};

    virtual Int16 const& getBranchNo() const = 0;
    virtual Int16 const& getOrigBranchNo() const = 0;
    virtual Int32 const& getCustomerNo() const = 0;
    virtual Int16 const& getCstBranchNo() const = 0;
    virtual VarString const& getPharmacyName() const = 0;
    virtual VarString const& getOwnerName() const = 0;
    virtual VarString const& getZipCode() const = 0;
    virtual VarString const& getCity() const = 0;
    virtual VarString const& getStreet() const = 0;
    virtual VarString const& getTelefonNo() const = 0;
    virtual VarString const& getSpeedDialNo() const = 0;

public:
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setOrigBranchNo(Int16 const& origBranchNo) = 0;
    virtual void setCustomerNo(Int32 const& customerNo) = 0;
    virtual void setCstBranchNo(Int16 const& cstBranchNo) = 0;
    virtual void setPharmacyName(VarString const& pharmacyName) = 0;
    virtual void setOwnerName(VarString const& ownerName) = 0;
    virtual void setZipCode(VarString const& zipCode) = 0;
    virtual void setCity(VarString const& city) = 0;
    virtual void setStreet(VarString const& street) = 0;
    virtual void setTelefonNo(VarString const& telefonNo) = 0;
    virtual void setSpeedDialNo(VarString const& speedDialNo) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKCUSTOMER_H
