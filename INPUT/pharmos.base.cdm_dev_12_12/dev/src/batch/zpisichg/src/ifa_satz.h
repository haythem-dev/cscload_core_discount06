
/* ---------------------------------------------------------------------- *
 *                         Ifa_Satz.h                                     *
 * ---------------------------------------------------------------------- */

#ifndef IFA_SATZ_INCLUDED
#define IFA_SATZ_INCLUDED

#include "ifa_stru.h"

typedef int (*FILL_FKT) ( sSatzArt *pSart, int mode, char *errmld ) ;

struct SatzDesc
{
   char *satzart;
   sSatzArt sSart;
   int  mode;
   long Anzahl;
   long AsasAnzahl;
   FILL_FKT Fill;
};

typedef struct SatzDesc  sSatzDesc;

/* --------------------------------------- */

long GenIfaSatz( char *datei, sSatzDesc *psD, char *idd_file, char *errmld );


#endif
