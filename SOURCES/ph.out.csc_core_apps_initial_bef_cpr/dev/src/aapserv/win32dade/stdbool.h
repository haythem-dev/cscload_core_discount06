#ifndef _STDBOOL_H
#define _STDBOOL_H    1

/* This file intended to serve as a drop-in replacement for 
 *  stdbool.h on Windows
 *  Please add functionality as neeeded 
 */
#ifndef __cplusplus

typedef int bool;
#define false 0
#define true 1

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

#endif /* __cplusplus */

#endif /* _STDBOOL_H  */