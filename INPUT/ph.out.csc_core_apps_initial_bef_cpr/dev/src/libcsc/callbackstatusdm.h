/*
 * callbackstatusdm.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H

#include "icallbackstatusptr.h"

namespace libcsc {
    namespace callback {

        namespace repo {
            class CallbackStatusMapper;
        }

        namespace domMod {

            class CallbackStatusDM : public ICallbackStatus
            {
                // because of OR mapping
                friend class repo::CallbackDivisionMapper;

            public:
                virtual ~CallbackStatusDM();

                static ICallbackStatusPtr create();

                virtual Int16 const& getCallbackStatusNo() const;
                virtual VarString const& getCallbackStatusName() const;
            public:
                virtual void setBranchNo(Int16 const& branchNo);
                virtual void setCallbackStatusName(VarString const& callbackStatusName);

                virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

            protected:
                CallbackStatusDM();

            private:
                Int16 m_CallbackStatusNo;
                VarString m_CallbackStatusName;

                CallbackStatusDM(const CallbackStatusDM&);
                CallbackStatusDM& operator=(const CallbackStatusDM&);
            };

        } // namespace domMod
    } // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CALLBACKDIVISIONDM_H


