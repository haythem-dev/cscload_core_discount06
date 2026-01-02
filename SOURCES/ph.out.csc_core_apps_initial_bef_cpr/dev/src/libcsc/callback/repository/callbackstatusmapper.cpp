/*
 * callbackstatusmapper.cpp
 *
 *  Created on: 29.08.2024
 *  Author: sofien.tahari
 */

#include "callbackstatusmapper.h"
#include "callback/domainmodule/callbackstatusdm.h"
#include "logger/loggerpool.h"

namespace libcsc {
    namespace callback {
        namespace repo {

            CallbackStatusMapper::CallbackStatusMapper(domMod::ICallbackStatusPtr callbackStatus)
                : m_CallbackStatus(*dynamic_cast<domMod::CallbackStatusDM*>(callbackStatus.get()))
            {
            }

            CallbackStatusMapper::~CallbackStatusMapper()
            {
            }

            void CallbackStatusMapper::setCallbackStatusNo(basar::Int16 const callbackStatusNo)
            {
                m_CallbackStatus.m_CallbackStatusNo = callbackStatusNo;
                m_CallbackStatus.m_CallbackStatusNo.setClean();
            }

            void CallbackStatusMapper::setCallbackStatusName(basar::VarString const callbackStatusName)
            {
                m_CallbackStatus.m_CallbackStatusName = callbackStatusName;
                m_CallbackStatus.m_CallbackStatusName.setClean();
            }

            void CallbackStatusMapper::setCallbackStatusFlag(basar::Int32 const callbackStatusFlag)
            {
                m_CallbackStatus.m_CallbackStatusFlag = callbackStatusFlag;
                m_CallbackStatus.m_CallbackStatusFlag.setClean();
            }

        } // end namespace repo
    } // end namespace callback
} // end namespace libcsc
