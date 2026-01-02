/*
 * sqlnotfoundexception.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_SQLNOTFOUND_EXCEPTION_H
#define GUARD_LIBCSC_SQLNOTFOUND_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace exceptions {

class SqlNotFoundException : public CSCExceptionBase
{
public:
    SqlNotFoundException(basar::ExceptInfo const& sInfo);
    virtual ~SqlNotFoundException();

private:
    SqlNotFoundException();
};

} // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_SQLNOTFOUND_EXCEPTION_H
