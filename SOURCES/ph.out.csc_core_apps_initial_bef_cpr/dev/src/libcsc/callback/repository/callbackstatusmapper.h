/*
 * callbackdstatusmapper.h
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_CALLBACKSTATUSMAPPER_H
#define GUARD_LIBCSC_CALLBACK_REPO_CALLBACKSTATUSMAPPER_H

#include <libbasar_definitions.h>
#include "callback/domainmodule/icallbackstatusptr.h"

namespace libcsc {
    namespace callback {

        namespace domMod {
            class CallbackStatusDM;
        }

        namespace repo {

            class CallbackSqlMapper;

            class CallbackStatusMapper
            {
                friend class CallbackSqlMapper;

            protected:
                CallbackStatusMapper(domMod::ICallbackStatusPtr callbackStatus);
                virtual ~CallbackStatusMapper();

                virtual void setCallbackStatusNo(basar::Int16 const callbackStatusNo);
                virtual void setCallbackStatusName(basar::VarString const callbackStatusName);
                virtual void setCallbackStatusFlag(basar::Int32 const callbackStatusFlag);

            private:
                domMod::CallbackStatusDM& m_CallbackStatus;

                CallbackStatusMapper& operator=(CallbackStatusMapper const&);
            };

        } // end namespace repo
    } // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_CALLBACKSTATUSMAPPER_H

