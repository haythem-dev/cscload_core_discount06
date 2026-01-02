/*
 * callbackstatusdm.cpp
 *
 *  Created on: 28.08.2024
 *  Author: sofien.tahari
 */

#include "callbackstatusdm.h"

namespace libcsc {
    namespace callback {
        namespace domMod {

            CallbackStatusDM::CallbackStatusDM()
            {
            }

            CallbackStatusDM::~CallbackStatusDM()
            {
            }

            ICallbackStatusPtr CallbackStatusDM::create()
            {
                return ICallbackStatusPtr(new CallbackStatusDM());
            }

            Int16 const& CallbackStatusDM::getCallbackStatusNo() const
            {
                return m_CallbackStatusNo;
            }

            VarString const& CallbackStatusDM::getCallbackStatusName() const
            {
                return m_CallbackStatusName;
            }

            Int32 const& CallbackStatusDM::getCallbackStatusFlag() const
            {
                return m_CallbackStatusFlag;
            }


            void CallbackStatusDM::setCallbackStatusNo(Int16 const& callbackStatusNo)
            {
                m_CallbackStatusNo = callbackStatusNo;
            }

            void CallbackStatusDM::setCallbackStatusName(VarString const& callbackStatusName)
            {
                m_CallbackStatusName = callbackStatusName;
            }

            void CallbackStatusDM::setCallbackStatusFlag(Int32 const& callbackStatusFlag)
            {
                m_CallbackStatusFlag = callbackStatusFlag;
            }

            std::ostream& CallbackStatusDM::toStream(std::ostream& strm /*= std::cout*/) const
            {
                strm
                    << "m_CallbackStatusNo=<" << m_CallbackStatusNo << ">"
                    << ", m_CallbackStatusName=<" << m_CallbackStatusName << ">"
                    << ", m_CallbackStatusFlag=<" << m_CallbackStatusFlag << ">";
                return strm;
            }

        } // namespace domMod
    } // namespace callback
} // namespace libcsc