/*
 * customernotfoundexception.cpp
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#include "customernotfoundexception.h"

namespace libcsc {
namespace callback {
namespace exceptions {

CustomerNotFoundException::CustomerNotFoundException(basar::ExceptInfo const& sInfo)
: libcsc::exceptions::CSCExceptionBase(sInfo, "CustomerNotFoundException")
{
}

CustomerNotFoundException::~CustomerNotFoundException()
{
}

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc
