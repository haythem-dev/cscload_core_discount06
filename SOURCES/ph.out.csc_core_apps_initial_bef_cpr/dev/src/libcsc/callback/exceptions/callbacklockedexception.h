/*
 * callbacklockedexception.h
 *
 *  Created on: 09.01.2017
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKLOCKED_EXCEPTION_H
#define GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKLOCKED_EXCEPTION_H

#include <exceptions/cscexceptionbase.h>

namespace libcsc {
namespace callback {
namespace exceptions {

class CallbackLockedException : public libcsc::exceptions::CSCExceptionBase
{
public:
    CallbackLockedException(basar::ExceptInfo const& sInfo);
    virtual ~CallbackLockedException();

private:
    CallbackLockedException();
};

} // end namespace exceptions
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_EXCEPTIONS_CALLBACKLOCKED_EXCEPTION_H
