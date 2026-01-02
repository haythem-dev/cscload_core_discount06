#include "pxdefs.hpp"
#include "string.hpp"

/*----------------------------------------------------------------------------*/
/*  Converts integers representing state values to a 'LIKE' string. The       */
/*  resulting string may be used in a 'LIKE' clause of an SQL-Statement.      */
/*  The nString passed as 'str' should be pre-formatted with the default      */
/*  LIKE-pattern.                                                             */
/*  A variable number of integer arguments must be passed via the 'arglist'   */
/*  pointer. Each integer argument should contain a positive or negative      */
/*  value representing the offset of the state character to be set.           */
/*  Positive numbers result in setting a '1', negative numbers will set a '0'.*/
/*  The first number being out of bounds of the string size is considered to  */
/*  be the end of the variable argument list.                                 */
/*  Returns the number of state chars being set.                              */
/*----------------------------------------------------------------------------*/
int
pxStatesToLikeString
(
    nString&       str,
    va_list        arglist
)
{
    int   retval;                       // number of state values being set
    char  c;                            // current state char value
    int   strlen = (int) str.Length();  // get string length
    for (retval = 0; retval < strlen; retval++)
    {
       int i = va_arg(arglist, int);        // get state value
       if ( i < 0 )                     // then set state to '0' = OFF
       {
          c = '0';
          i = ~i;                       // make positive index
       }
       else
          c = '1';

       if ( i >= strlen )               // prevent bounds error
          break;
       str(i, 1) = c;                   // set state
    }

    str.Strip(nString::cTRAILING, '_'); // strip trailing underscores
    if (str.Length() < (size_t) strlen) // then trailing underscores where there,
       str += '%';                      // append 'end of like string' character

    return retval;
}
