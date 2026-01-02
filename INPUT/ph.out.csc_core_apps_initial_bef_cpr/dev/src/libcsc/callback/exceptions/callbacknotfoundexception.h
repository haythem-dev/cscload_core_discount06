/*
 * callbacklockedexception.h
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKNOTFOUND_EXCEPTION_H
#define GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKNOTFOUND_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace callback {
namespace exceptions {

class CallbackNotFoundException : public libcsc::exceptions::CSCExceptionBase
{
public:
    CallbackNotFoundException(basar::ExceptInfo const& sInfo);
    virtual ~CallbackNotFoundException();

private:
    CallbackNotFoundException();
};

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKNOTFOUND_EXCEPTION_H
