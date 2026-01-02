/*
 * sqltoomanyrowsexception.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_SQLTOOMANYROWS_EXCEPTION_H
#define GUARD_LIBCSC_SQLTOOMANYROWS_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace exceptions {

class SqlTooManyRowsException : public CSCExceptionBase
{
public:
    SqlTooManyRowsException(basar::ExceptInfo const& sInfo);
    virtual ~SqlTooManyRowsException();

private:
    SqlTooManyRowsException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_SQLTOOMANYROWS_EXCEPTION_H
