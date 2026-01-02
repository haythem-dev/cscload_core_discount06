/*
 * callbackreasondm.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONDM_H

#include "icallbackreasonptr.h"
#include "icallbackreason.h"

namespace libcsc {
namespace callback {

namespace repo {
class CallbackReasonMapper;
}

namespace domMod {

class CallbackReasonDM : public ICallbackReason
{
    // because of OR mapping
    friend class repo::CallbackReasonMapper;

public:
    virtual ~CallbackReasonDM();

    static ICallbackReasonPtr create();

    virtual Int16 const& getBranchNo() const;
    virtual Int16 const& getDivisionNo() const;
    virtual Int16 const& getReasonNo() const;
    virtual VarString const& getReasonName() const;
    virtual VarString const& getMailingList() const;

public:
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setDivisionNo(Int16 const& divisionNo);
    virtual void setReasonNo(Int16 const& reasonNo);
    virtual void setReasonName(VarString const& reasonName);
    virtual void setMailingList(VarString const& mailingList);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CallbackReasonDM();

private:
    Int16 m_BranchNo;
    Int16 m_DivisionNo;
    Int16 m_ReasonNo;
    VarString m_ReasonName;
    VarString m_MailingList;

    CallbackReasonDM(const CallbackReasonDM&);
    CallbackReasonDM& operator=(const CallbackReasonDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKREASONDM_H
