/*
 * callbackdivisionmapper.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKDIVISIONMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKDIVISIONMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackdivisionptr.h"

namespace libcsc {
namespace callback {

namespace domMod {
class CallbackDivisionDM;
}

namespace repo {

class CallbackSqlMapper;

class CallbackDivisionMapper
{
    friend class CallbackSqlMapper;

protected:
    CallbackDivisionMapper(domMod::ICallbackDivisionPtr callbackDivision);
    virtual ~CallbackDivisionMapper();

    virtual void setBranchNo(basar::Int16 const branchNo);
    virtual void setDivisionNo(basar::Int16 const divisionNo);
    virtual void setDivisionName(basar::VarString const divisionName);
    virtual void setMailingList(basar::VarString const mailingList);

private:
    domMod::CallbackDivisionDM& m_CallbackDivision;

    CallbackDivisionMapper& operator=(CallbackDivisionMapper const&);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKDIVISIONMAPPER_H
