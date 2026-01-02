/*
 * customernotfoundexception.h
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CUSTOMERNOTFOUND_EXCEPTION_H
#define GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CUSTOMERNOTFOUND_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace callback {
namespace exceptions {

class CustomerNotFoundException : public libcsc::exceptions::CSCExceptionBase
{
public:
    CustomerNotFoundException(basar::ExceptInfo const& sInfo);
    virtual ~CustomerNotFoundException();

private:
    CustomerNotFoundException();
};

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CUSTOMERNOTFOUND_EXCEPTION_H
