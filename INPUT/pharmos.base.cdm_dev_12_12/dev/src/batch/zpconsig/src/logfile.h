/* ---------------------------------------------------------------------- *
 *                          logfile.h                                     *
 * ---------------------------------------------------------------------- */

#define S_INFO      0
#define S_ERROR    -1
#define S_WARNING  -2

int  write_logfile ( int status, char *function, char *strmsg);
