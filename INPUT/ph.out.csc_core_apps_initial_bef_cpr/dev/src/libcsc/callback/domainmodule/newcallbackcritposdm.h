/*
 * newcallbackcritposdm.h
 *
 *  Created on: 30.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKCRITPOSDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKCRITPOSDM_H

#include "inewcallbackcritposptr.h"
#include "inewcallbackcritpos.h"
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {

namespace repo {
class CallbackMapper;
}

namespace domMod {

class NewCallbackCritPosDM : public INewCallbackCritPos
{
    // because of OR mapping
    friend class repo::CallbackMapper;

public:
    virtual ~NewCallbackCritPosDM();

    static INewCallbackCritPosPtr create();

    virtual basar::Int32 const& getCallbackNo() const;
    virtual basar::Int16 const& getBranchNo() const;
    virtual basar::Int32 const& getUId() const;
    virtual basar::VarString const& getText() const;
    virtual basar::VarString const& getWindowsUser() const;
    virtual basar::Int16 const& getSourceApplication() const;
    virtual basar::Int16 const& getCallbackStatus() const;

public:
    virtual void setCallbackNo(basar::Int32 const& callbackNo);
    virtual void setBranchNo(basar::Int16 const& branchNo);
    virtual void setUId(basar::Int32 const& uid);
    virtual void setText(basar::VarString const& text);
    virtual void setWindowsUser(basar::VarString const& windowsUser);
    virtual void setSourceApplication(basar::Int16 const& sourceApplication);
    virtual void setCallbackStatus(basar::Int16 const& callbackStatus);

protected:
    NewCallbackCritPosDM();

private:
    basar::Int32 m_CallbackNo;
    basar::Int16 m_BranchNo;
    basar::Int32 m_UId;
    basar::VarString m_Text;
    basar::VarString m_WindowsUser;
    basar::Int16 m_SourceApplication;
    basar::Int16 m_CallbackStatus;

    NewCallbackCritPosDM(const NewCallbackCritPosDM&);
    NewCallbackCritPosDM& operator=(const NewCallbackCritPosDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_NEWCALLBACKCRITPOSDM_H
