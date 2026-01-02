/*
 * sqltoomanyrowsexception.cpp
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#include "sqltoomanyrowsexception.h"

namespace libcsc {
namespace exceptions {

SqlTooManyRowsException::SqlTooManyRowsException(basar::ExceptInfo const& sInfo)
: CSCExceptionBase(sInfo, "SqlTooManyRowsException")
{
}

SqlTooManyRowsException::~SqlTooManyRowsException()
{
}

} // end namespace exceptions
} // end namespace libcsc
