/* ---------------------------------------------------------------------- *
 *                            IFA_STAT.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef IFA_STAT_INCLUDED
#define IFA_STAT_INCLUDED

int ReadIfaStatus ( char* satzart, char *verz, char *errmld  );
int WriteIfaStatus( char* satzart, char *verz, char *errmld  );

#endif
