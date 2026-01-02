/*
 * icallbackdivision.h
 *
 *  Created on: 08.06.2016
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKSTATUS_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLSTATUS_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <base/isqlparameterbinder/idomainmodule.h>

namespace libcsc {
    namespace callback {
        namespace domMod {

            class ICallbackStatus : public base::IDomainModule
            {
            public:
                virtual ~ICallbackStatus() {};

                virtual Int16 const& getCallbackStatusNo() const = 0;
                virtual VarString const& getCallbackStatusName() const = 0;
                virtual Int32 const& getCallbackStatusFlag() const = 0;

            public:
                virtual void setCallbackStatusNo(Int16 const& CallbackStatusNo) = 0;
                virtual void setCallbackStatusName(VarString const& callbackStatusName) = 0;
                virtual void setCallbackStatusFlag(Int32 const& callbackStatusFlag) = 0;
            };

        } // namespace domMod
    } // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_ICALLBACKSTATUS_H
