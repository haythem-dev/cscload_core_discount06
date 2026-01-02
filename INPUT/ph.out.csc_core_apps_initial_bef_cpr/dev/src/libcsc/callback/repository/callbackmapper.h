/*
 * callbackmapper.h
 *
 *  Created on: 13.05.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackMapper(domMod::ICallbackPtr callback);
    virtual ~CallbackMapper();

    virtual void setCritNo(basar::Int32 const& critNo);
    virtual void setCallbackDate(basar::Int32 const& callbackDate);
    virtual void setCallbackTime(basar::Int32 const& callbacktime);
    virtual void setCritLevel(basar::Int16 const& critLevel);
    virtual void setTitle(basar::VarString const& title);
    virtual void setBranchNo(basar::Int16 const& branchNo);
    virtual void setCstBranchNo(basar::Int16 const& cstBranchNo);
    virtual void setCustomerNo(basar::Int32 const& customerNo);
    virtual void setCustomerClassTag(basar::VarString const& customerClassTag);
    virtual void setPharmacyName(basar::VarString const& pharmacyName);
    virtual void setOwnerName(basar::VarString const& ownerName);
    virtual void setStreet(basar::VarString const& street);
    virtual void setCity(basar::VarString const& city);
    virtual void setZipCode(basar::VarString const& zipCode);
    virtual void setTelefonNo(basar::VarString const& telefonNo);
    virtual void setSpeedDialNo(basar::VarString const& speedDialNo);
    virtual void setFaxNo(basar::VarString const& faxNo);
    virtual void setCallbackStatus(basar::Int16 const& callbackStatus);
    virtual void setReference(basar::VarString const& reference);

private:
    domMod::CallbackDM& m_Callback;

    CallbackMapper& operator=(CallbackMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKMAPPER_H
