/*
 * callbackstatusdm.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSNDM_H

#include "icallbackstatusptr.h"
#include "icallbackstatus.h"

namespace libcsc {
    namespace callback {

        namespace repo {
            class CallbackStatusMapper;
        }

        namespace domMod {

            class CallbackStatusDM : public ICallbackStatus
            {
                // because of OR mapping
                friend class repo::CallbackStatusMapper;

            public:
                virtual ~CallbackStatusDM();

                static ICallbackStatusPtr create();

                virtual Int16 const& getCallbackStatusNo() const;
                virtual VarString const& getCallbackStatusName() const;
                virtual Int32 const& getCallbackStatusFlag() const;
            public:
                virtual void setCallbackStatusNo(Int16 const& callbackStatusNo);
                virtual void setCallbackStatusName(VarString const& callbackStatusName);
                virtual void setCallbackStatusFlag(Int32 const& callbackStatusFlag);

                virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

            protected:
                CallbackStatusDM();

            private:
                Int16 m_CallbackStatusNo;
                VarString m_CallbackStatusName;
                Int32 m_CallbackStatusFlag;

                CallbackStatusDM(const CallbackStatusDM&);
                CallbackStatusDM& operator=(const CallbackStatusDM&);
            };

        } // namespace domMod
    } // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKSTATUSDM_H


