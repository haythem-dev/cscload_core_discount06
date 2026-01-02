#ifndef NNTYPES_INC
#define NNTYPES_INC

/*----------------------------------------------------------------------------*/
/*  Misc. constant values                                                     */
/*----------------------------------------------------------------------------*/
#define cNEWLINE     '\n'               /* C definition of ASCII newline      */
#define cQUOTE       '\''               /* C definition for single quote      */
#define cDQUOTE      '\"'               /* C definition for double quote      */
#define cSPACE       ' '                /* white space character              */

#define cDEFAULT_NO  -1                 /* used for default numbers           */

/*----------------------------------------------------------------------------*/
/*  Misc. Macros                                                              */
/*----------------------------------------------------------------------------*/

#define mSIZEOF(struct_t, member) ((size_t) (sizeof( ((struct_t *)0)->member )))

#endif                                /* for ifndef NNTYPES_DOTH              */
