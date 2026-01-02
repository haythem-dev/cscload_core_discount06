/*
 * callbacklockedexception.cpp
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#include "callbacklockedexception.h"

namespace libcsc {
namespace callback {
namespace exceptions {

CallbackLockedException::CallbackLockedException(basar::ExceptInfo const& sInfo)
: libcsc::exceptions::CSCExceptionBase(sInfo, "CallbackLockedException")
{
}

CallbackLockedException::~CallbackLockedException()
{
}

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc
