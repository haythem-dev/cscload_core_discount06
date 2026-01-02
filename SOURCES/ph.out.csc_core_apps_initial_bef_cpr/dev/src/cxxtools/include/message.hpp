/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

MESSAGE.HPP
Message string facility.

REVISION HISTORY

16 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
#ifndef NMESSAGE_INC
#define NMESSAGE_INC

#include "ndefs.h"
#include <stdarg.h>
#include "string.hpp"
#include "nsecfile.hpp"

#define cMSGID_WIDTH   5                 // width of canned message id
#define cMSG_MAXLEN    2048              // max msg length


class nMessage
{

public:
                nMessage(const char* format, ...);
                nMessage(std::ifstream *stream, const int MsgId, va_list arglist);
                nMessage(std::ifstream *stream, const int MsgId, ...);
                nMessage(const nMessage& src);

                ~nMessage();

    const nString&    String() const               { return msg_;}


protected :
    void        GetCannedMsg(nSectionHdl& msgfile, const int MsgId, va_list argptr);
    bool        IsMultiLanguage(const int MsgId);
private:
    nString     msg_;

};

#endif
