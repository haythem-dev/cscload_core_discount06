/*
 * callbackcustomermapper.h
 *
 *  Created on: 13.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKCUSTOMERMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKCUSTOMERMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackcustomerptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackCustomerDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackCustomerMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackCustomerMapper(domMod::ICallbackCustomerPtr callbackCustomer);
    virtual ~CallbackCustomerMapper();

    virtual void setBranchNo(basar::Int16 const branchNo);
    virtual void setOrigBranchNo(basar::Int16 const origBranchNo);
    virtual void setCustomerNo(basar::Int32 const customerNo);
    virtual void setCstBranchNo(basar::Int16 const cstBranchNo);
    virtual void setPharmacyName(basar::VarString const pharmacyName);
    virtual void setOwnerName(basar::VarString const ownerName);
    virtual void setZipCode(basar::VarString const zipCode);
    virtual void setCity(basar::VarString const city);
    virtual void setStreet(basar::VarString const street);
    virtual void setTelefonNo(basar::VarString const telefonNo);
    virtual void setSpeedDialNo(basar::VarString const speedDialNo);

private:
    domMod::CallbackCustomerDM& m_CallbackCustomer;

    CallbackCustomerMapper& operator=(CallbackCustomerMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKCUSTOMERMAPPER_H
