/*
 * callbackcustomerdm.h
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDM_H

#include "icallbackcustomerptr.h"
#include "icallbackcustomer.h"

namespace libcsc {
namespace callback {

namespace repo {
class CallbackCustomerMapper;
}

namespace domMod {

class CallbackCustomerDM : public ICallbackCustomer
{
    // because of OR mapping
    friend class repo::CallbackCustomerMapper;

public:
    virtual ~CallbackCustomerDM();

    static ICallbackCustomerPtr create();

    virtual Int16 const& getBranchNo() const;
    virtual Int16 const& getOrigBranchNo() const;
    virtual Int32 const& getCustomerNo() const;
    virtual Int16 const& getCstBranchNo() const;
    virtual VarString const& getPharmacyName() const;
    virtual VarString const& getOwnerName() const;
    virtual VarString const& getZipCode() const;
    virtual VarString const& getCity() const;
    virtual VarString const& getStreet() const;
    virtual VarString const& getTelefonNo() const;
    virtual VarString const& getSpeedDialNo() const;

public:
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setOrigBranchNo(Int16 const& origBranchNo);
    virtual void setCustomerNo(Int32 const& customerNo);
    virtual void setCstBranchNo(Int16 const& cstBranchNo);
    virtual void setPharmacyName(VarString const& pharmacyName);
    virtual void setOwnerName(VarString const& ownerName);
    virtual void setZipCode(VarString const& zipCode);
    virtual void setCity(VarString const& city);
    virtual void setStreet(VarString const& street);
    virtual void setTelefonNo(VarString const& telefonNo);
    virtual void setSpeedDialNo(VarString const& speedDialNo);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CallbackCustomerDM();

private:
    Int16 m_BranchNo;
    Int16 m_OrigBranchNo;
    Int32 m_CustomerNo;
    Int16 m_CstBranchNo;
    VarString m_PharmacyName;
    VarString m_OwnerName;
    VarString m_ZipCode;
    VarString m_City;
    VarString m_Street;
    VarString m_TelefonNo;
    VarString m_SpeedDialNo;

    CallbackCustomerDM(const CallbackCustomerDM&);
    CallbackCustomerDM& operator=(const CallbackCustomerDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKCUSTOMERDM_H
