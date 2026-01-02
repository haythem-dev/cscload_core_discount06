#ifndef PXDEFS_INC
#define PXDEFS_INC

#include <stdarg.h>
class nString;

/*----------------------------------------------------------------------------*/
/*  Misc. constants                                                           */
/*----------------------------------------------------------------------------*/
static const int cFlagBytesPerLong = 2; // number of flag bytes stored in a long

/*----------------------------------------------------------------------------*/
/*  Enumeration for message constant numbers.                                 */
/*  This messages are located in a code module and do always represent fatal  */
/*  errors. In those cases, no error message could be read from the canned    */
/*  message file.                                                             */
/*----------------------------------------------------------------------------*/
enum pxMsgNumber
{
    pxMSGNUM_UNKNOWN,                   // unknown message number
    pxMSGNUM_MEMLACK,                   // out of memory
    pxMSGNUM_OPENINI,                   // .ini file open error
    pxMSGNUM_OPENCMSG,                  // canned message file open error
    pxMSGNUM_SESSION_PARM,              // essential session parameter missing
    pxMSGNUM_SESSION_INIFILE            // essential session parameter missing
};

/*----------------------------------------------------------------------------*/
/*  Enumeration for canned message id's used for table names.                 */
/*----------------------------------------------------------------------------*/
enum tCMSG_TABLES
{
    CMSG_TABLES   = 90000
};

/*----------------------------------------------------------------------------*/
/*  Enumeration for canned message id's used for function names.              */
/*----------------------------------------------------------------------------*/
enum tCMSG_FUNCTIONS
{
    CMSG_FUNCTIONS_TABLE   = 91000,
    CMSG_FUNCTIONS_COMMON  = 91010,
    CMSG_FUNCTIONS_LOCKMAN = 91020
};

/*----------------------------------------------------------------------------*/
/*  Global server function prototypes.                                        */
/*----------------------------------------------------------------------------*/
char* pxErrorMsg(pxMsgNumber msgnum);
int pxStatesToLikeString(nString& str, va_list arglist);
#endif
