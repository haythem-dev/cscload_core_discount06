
/* ---------------------------------------------------------------------- *
 *                          normdat.c                                     *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Enthaelt Norm-Funktionen zum Bearbeiten von         *
 *                    ASCII-dateien                                       *
 * ---------------------------------------------------------------------- *
 *   Autor          : Schmitt                                             *
 *   entwickelt am  : 15.12.1993                                          *
 *   letztes Update : 15.12.1993                                          *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include "asciidat.h"

/* --- Normale File-Funktionen : Parameter af = NULL bei AscOpen -------- */

static FILE *af[] = { NULL, NULL, NULL, NULL };

#define MAX_FILE  ( sizeof(af) / sizeof( FILE * ) )

static int a_open ( char *datei, char *mode )
  {
    int  fd;

    fd = 0;
    while ( fd < MAX_FILE && af[fd] != NULL ) fd++;
    if ( fd == MAX_FILE ) return -1;

    af[fd] = fopen( datei, mode );
    if ( af[fd] == NULL ) return -1;

    return fd;
   }

static int a_read ( int fd, char *puffer, int lng )
  {
    if ( af[fd] == NULL ) return 0;
    return fread( puffer, 1, lng, af[fd] );
   }

static int a_write ( int fd, char *puffer, int lng )
  {
    if ( af[fd] == NULL ) return -1;
    return fwrite( puffer, 1, lng, af[fd] );
   }

static int a_rewind ( int fd )
  {
    if ( af[fd] == NULL ) return -1;
    rewind( af[fd] );
    return 0;
   }

static int a_close ( int fd )
  {
    if ( af[fd] == NULL ) return -1;
    fclose( af[fd] );
    af[fd] = NULL;
    return 0;
   }

ASC_FKT AscNormFkt =
  {
    &a_open,
    &a_read,
    &a_write,
    &a_rewind,
    &a_close
   };

