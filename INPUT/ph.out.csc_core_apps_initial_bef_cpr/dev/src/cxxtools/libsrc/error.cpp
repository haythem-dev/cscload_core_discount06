/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Generic error handling.

REVISION HISTORY

16 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: ERROR.CPP $
 *
 * *****************  Version 4  *****************
 * User: Y.bouma      Date: 6.02.07    Time: 15:31
 * Updated in $/prj/as/cxxtools/src
 *
 * *****************  Version 3  *****************
 * User: Y.bouma      Date: 6.02.07    Time: 15:29
 * Updated in $/prj/as/cxxtools/src
 */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */

#include "error.hpp"
#include <stdarg.h>
#include <stdio.h>

extern bool pxGlobalNoWriteToLog;
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
nError :: nError
(
    const nError& src
)

{
    *this = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
nError :: ~nError()
{
    ClearError();
}

/*----------------------------------------------------------------------------*/
/*  Assignment using operator =.                                              */
/*----------------------------------------------------------------------------*/
nError&
nError :: operator=
(
    const nError& src
)
{
    ClearError();
    state_      = src.state_;
    errornum_   = src.errornum_;
    type_       = src.type_;
    msg_        = src.msg_;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Clear error object.                                                       */
/*----------------------------------------------------------------------------*/
void
nError :: ClearError
(
)
{
    state_      = nSTATE_GOOD;
    errornum_   = 0;
    type_       = nERRTYPE_UNKNOWN;
    msg_.Clear();
}

int
nError :: InternalError
(
    std::ifstream  *stream,
    const int      MsgId,
    ...
)
{
    va_list arglist;
    va_start (arglist, MsgId);
    nMessage msg(stream, MsgId, arglist);
    va_end(arglist);
    return InternalError(msg, MsgId);
}
int
nError :: ExternalCondition
(
    std::ifstream  *stream,
    const int      MsgId,
    ...
)
{
    va_list arglist;
    va_start (arglist, MsgId);
    nMessage msg(stream, MsgId, arglist);
    va_end(arglist);
    return ExternalCondition(msg, MsgId);
}

int
nError :: ExternalError
(
    std::ifstream  *stream,
    const int      MsgId,
    ...
)
{
    va_list arglist;
    va_start (arglist, MsgId);
    nMessage msg(stream, MsgId, arglist);
    va_end(arglist);
    return ExternalError(msg, MsgId);
}

int
nError :: LogEvent
(
    std::ifstream *stream,
    const int      MsgId,
    ...
)
{
    va_list arglist;
    va_start (arglist, MsgId);
    nMessage msg(stream, MsgId, arglist);
    va_end(arglist);
    return LogEvent(msg, MsgId);
}

/*----------------------------------------------------------------------------*/
/*  Set error object.                                                         */
/*----------------------------------------------------------------------------*/
int
nError :: SetError
(
    const nMessage&   msg,
    const int   errornum,
          nErrorType t,
          nErrorState s
)
{
    ClearError();
    errornum_   = errornum;
    msg_        = msg.String();
    type_       = t;
    state_      = s;
    if ( !pxGlobalNoWriteToLog)
    {
       WriteLog(msg_, state_, errornum_);  // write self to log file
    }
    if ( type_ == nERRTYPE_EVENTLOG )   // then its just a log request
       ClearError();                    // and no error
    return errornum_;
}
