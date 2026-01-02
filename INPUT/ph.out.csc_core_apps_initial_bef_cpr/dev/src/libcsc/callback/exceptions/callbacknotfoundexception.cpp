/*
 * callbacknotfoundexception.cpp
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#include "callbacknotfoundexception.h"

namespace libcsc {
namespace callback {
namespace exceptions {

CallbackNotFoundException::CallbackNotFoundException(basar::ExceptInfo const& sInfo)
: libcsc::exceptions::CSCExceptionBase(sInfo, "CallbackNotFoundException")
{
}

CallbackNotFoundException::~CallbackNotFoundException()
{
}

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc
