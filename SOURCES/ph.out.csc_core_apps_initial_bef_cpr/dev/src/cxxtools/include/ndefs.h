#ifndef NDEFS_DOTH
#define NDEFS_DOTH

/*----------------------------------------------------------------------------*/
/*  Data base request return codes.                                           */
/*----------------------------------------------------------------------------*/
/*  Condition codes, values range from 0-+100                                 */
#define cDBXR_NORMAL        0       // Normal response
#define cDBXR_NOTFOUND      1       // Requested component not found
//#define cDBXR_EOF         2       // Generic end of file condition
#define cDBXR_ENDOFDATA     3       // End of data reached during browse
#define cDBXR_ISDUPLICATE   4       // Attempt to insert a duplicate key or to read with a non-unique key
//#define cDBXR_ISLOCKED    5       // Requested component is locked

/*  Error codes, values range from -999 - 900                                 */
#define cDBXR_IOERROR         -999  // Generic i/o error
#define cDBXR_ISDOWN          -998  // Requested resource not available
//#define cDBXR_NOTAUTHORIZED -997  // User not authorized
//#define cDBXR_NOSPACE       -996  // No space available to insert
#define cDBXR_DEFINITION      -995  // Database definition error structure size mismatch

/*----------------------------------------------------------------------------*/
/*  Misc. manifest constants.                                                 */
/*----------------------------------------------------------------------------*/
#define cDEFAULT                    -1  /* default value                      */
#define cASCENDING                  +1  /* sort orders                        */
#define cDESCENDING                 -1


#endif
