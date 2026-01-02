/*
 * inewcallbackcritpos.h
 *
 *  Created on: 30.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOS_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOS_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace callback {
namespace domMod {

class INewCallbackCritPos
{
public:
    virtual ~INewCallbackCritPos() {};

    virtual basar::Int32 const& getCallbackNo() const = 0;
    virtual basar::Int16 const& getBranchNo() const = 0;
    virtual basar::Int32 const& getUId() const = 0;
    virtual basar::VarString const& getText() const = 0;
    virtual basar::VarString const& getWindowsUser() const = 0;
    virtual basar::Int16 const& getSourceApplication() const = 0;
    virtual basar::Int16 const& getCallbackStatus() const = 0;

public:
    virtual void setCallbackNo(basar::Int32 const& callbackNo) = 0;
    virtual void setBranchNo(basar::Int16 const& branchNo) = 0;
    virtual void setUId(basar::Int32 const& uid) = 0;
    virtual void setText(basar::VarString const& text) = 0;
    virtual void setWindowsUser(basar::VarString const& windowsUser) = 0;
    virtual void setSourceApplication(basar::Int16 const& sourceApplication) = 0;
    virtual void setCallbackStatus(basar::Int16 const& callbackStatus) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_INEWCALLBACKCRITPOS_H
