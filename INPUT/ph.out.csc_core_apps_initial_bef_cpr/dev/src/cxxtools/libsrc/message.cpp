/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Routines to implement the message facility.

REVISION HISTORY

16 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
#include "message.hpp"
#include "messagedefs.h"

extern int pxGlobalLanguageId;
extern nString pxGlobalMessageFile;
/*----------------------------------------------------------------------------*/
/*  Construct a message from a printf-like format string and a variable list  */
/*  of arguments.                                                             */
/*----------------------------------------------------------------------------*/
nMessage :: nMessage
(
    const char   *format,
    ...
)
{
    char   buffer[cMSG_MAXLEN+1];
    va_list arglist;
    va_start (arglist, format);
    vsprintf(buffer, format, arglist);
    msg_.Clear();
    msg_ = buffer;
    va_end(arglist);
}

/*----------------------------------------------------------------------------*/
/*  Construct a message using the canned message file stream pointer, the     */
/*  canned message id and a variable number of arguments.                     */
/*----------------------------------------------------------------------------*/
nMessage :: nMessage
(
    std::ifstream *stream,
    const int      MsgId,
    ...
)
{
    va_list arglist;
    va_start (arglist, MsgId);
    int key = MsgId;
    if (pxGlobalMessageFile == nGlobal_CMSG )
    {
        key = key * 100;
        if ( IsMultiLanguage(key))
        {
          key += pxGlobalLanguageId;
        }
    }
    nSectionHdl msgfile(stream);
    GetCannedMsg(msgfile, key, arglist); // read the message
    va_end(arglist);
}

/*----------------------------------------------------------------------------*/
/*  Construct a message using the canned message file stream pointer, the     */
/*  canned message id and a va_list pointer.                                  */
/*----------------------------------------------------------------------------*/
nMessage :: nMessage
(
    std::ifstream *stream,
    const int      MsgId,
    va_list        arglist
)
{
    int key = MsgId;
    if (pxGlobalMessageFile == nGlobal_CMSG )
    {
        key = key * 100;
        if ( IsMultiLanguage(key))
        {
          key += pxGlobalLanguageId;
        }
    }
    nSectionHdl msgfile(stream);
    GetCannedMsg(msgfile, key, arglist); // read the message
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
nMessage :: nMessage
(
    const nMessage& src
) : msg_(src.msg_)
{
//    msg_ = src.msg_;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
nMessage :: ~nMessage()
{
    ;
}


/*----------------------------------------------------------------------------*/
/*  Read a message from the canned message file.                              */
/*----------------------------------------------------------------------------*/
void
nMessage :: GetCannedMsg
(
    nSectionHdl&   msgfile,
    const int      MsgId,
    va_list        argptr
)

{
    char k[cMSGID_WIDTH*4+1];
    sprintf(k, "%.*i", cMSGID_WIDTH, MsgId);
    nString key(k);
    msg_.Clear();
    msg_ = msgfile.PrintSectionTxt(&key, argptr);
    if ( msg_.IsEmpty() )
       msg_ = key + " : Message not found\n";
}

/*----------------------------------------------------------------------------*/
/*  This methode checks the MsgId against the nTextNumberTab wether the       */
/*  number exist in Multi languages or just in german                         */
/*  Return: false = only german, true = several language                      */
/*----------------------------------------------------------------------------*/
bool
nMessage :: IsMultiLanguage
(
    const int MsgId
)
{
    bool  retval = false;
    int   Key    = MsgId;
    int   LFlag  = 0;
    Key = Key/100000;

    int x = sizeof(nTextNumberTable) / sizeof(nTextNumberTabEntry);  // index calculation
    for (int i = 0; i < x; i++)
    {
       if ( Key == nTextNumberTable[i].MsgId )
       {
          LFlag = nTextNumberTable[i].LanguageFlag;         // match
          break;
       }
    }
    retval = (LFlag == 1);
    return retval;
}
