/*
 * icritpos.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICRITPOS_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICRITPOS_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include "datatypes/property.hpp"
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICritPos : public base::IDomainModule
{
public:
    virtual ~ICritPos() {};

    virtual Int32 const& getPosNo() const = 0;
    virtual VarString const& getPosTypeTag() const = 0;
    virtual Int32 const& getCritNo() const = 0;
    virtual VarString const& getText() const = 0;
    virtual Int32 const& getUId() const = 0;
    virtual Int16 const& getBranchNo() const = 0;
    virtual Int32 const& getDate() const = 0;
    virtual Int32 const& getTime() const = 0;
    virtual VarString const& getWindowsUserId() const = 0;
    virtual Int16 const& getSourceApplication() const = 0;

public:
    virtual void setPosNo(Int32 const& posNo) = 0;
    virtual void setPosTypeTag(VarString const& posTypeTag) = 0;
    virtual void setCritNo(Int32 const& critNo) = 0;
    virtual void setText(VarString const& text) = 0;
    virtual void setUId(Int32 const& uId) = 0;
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setDate(Int32 const& date) = 0;
    virtual void setTime(Int32 const& time) = 0;
    virtual void setWindowsUserId(VarString const& windowsUserId) = 0;
    virtual void setSourceApplication(Int16 const& sourceApplication) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICRITPOS_H
