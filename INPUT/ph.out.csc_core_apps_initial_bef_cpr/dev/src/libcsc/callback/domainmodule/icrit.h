/*
 * icrit.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICRIT_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICRIT_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include "datatypes/property.hpp"
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
namespace callback {
namespace domMod {

class ICrit : public base::IDomainModule
{
public:
    virtual ~ICrit() {};

    virtual Int32 const& getCritNo() const = 0;
    virtual Int16 const& getBranchNo() const = 0;
    virtual Int32 const& getCustomerNo() const = 0;
    virtual Int16 const& getCstBranchNo() const = 0;
    virtual Int32 const& getDate() const = 0;
    virtual Int32 const& getTime() const = 0;
    virtual Int32 const& getUId() const = 0;
    virtual VarString const& getTitle() const = 0;
    virtual Int16 const& getCritLevel() const = 0;

public:
    virtual void setCritNo(Int32 const& critNo) = 0;
    virtual void setBranchNo(Int16 const& branchNo) = 0;
    virtual void setCustomerNo(Int32 const& customerNo) = 0;
    virtual void setCstBranchNo(Int16 const& cstBranchNo) = 0;
    virtual void setDate(Int32 const& date) = 0;
    virtual void setTime(Int32 const& time) = 0;
    virtual void setUId(Int32 const& uid) = 0;
    virtual void setTitle(VarString const& title) = 0;
    virtual void setCritLevel(Int16 const& critLevel) = 0;
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICRIT_H
