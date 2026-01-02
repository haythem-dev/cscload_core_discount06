/*
 * sqlnotfoundexception.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "sqlnotfoundexception.h"

namespace libcsc {
namespace exceptions {

SqlNotFoundException::SqlNotFoundException(basar::ExceptInfo const& sInfo)
: CSCExceptionBase(sInfo, "SqlNotFoundException")
{
}

SqlNotFoundException::~SqlNotFoundException()
{
}

} // end namespace exceptions
} // end namespace libcsc
