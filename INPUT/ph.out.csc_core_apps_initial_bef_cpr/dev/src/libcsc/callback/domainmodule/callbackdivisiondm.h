/*
 * callbackdivisiondm.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H

#include "icallbackdivisionptr.h"
#include "icallbackdivision.h"

namespace libcsc {
namespace callback {

namespace repo {
class CallbackDivisionMapper;
}

namespace domMod {

class CallbackDivisionDM : public ICallbackDivision
{
    // because of OR mapping
    friend class repo::CallbackDivisionMapper;

public:
    virtual ~CallbackDivisionDM();

    static ICallbackDivisionPtr create();

    virtual Int16 const& getBranchNo() const;
    virtual Int16 const& getDivisionNo() const;
    virtual VarString const& getDivisionName() const;
    virtual VarString const& getMailingList() const;

public:
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setDivisionNo(Int16 const& divisionNo);
    virtual void setDivisionName(VarString const& divisionName);
    virtual void setMailingList(VarString const& mailingList);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CallbackDivisionDM();

private:
    Int16 m_BranchNo;
    Int16 m_DivisionNo;
    VarString m_DivisionName;
    VarString m_MailingList;

    CallbackDivisionDM(const CallbackDivisionDM&);
    CallbackDivisionDM& operator=(const CallbackDivisionDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H
