/* ---------------------------------------------------------------------- *
 *                          asciidat.c                                    *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Enthaelt Funktionen zum Bearbeiten von              *
 *                    ASCII-dateien                                       *
 * ---------------------------------------------------------------------- *
 *   Autor          : Schmitt                                             *
 *   entwickelt am  : 15.12.1993                                          *
 *   letztes Update : 15.12.1993                                          *
 * ---------------------------------------------------------------------- */

#include "asciidat.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define TAB  0x09
#define CR   0x0d
#define LF   0x0a
#define DEND 0x1a

/*
static char eol[3] = { CR, LF, '\0' };
*/
static char eol[3] = { LF, '\0' };

/* --- Interne Struktur einer Datei-Beschreibung ------------------------ */

struct dat_desc
 {
   int     fd;
   int     datfd;         /* eigener fd */
   int     buflng;
   int     bufend;
   int     bufref;
   char    *datei;
   char    *buffer;
   ASC_FKT *af;
  };

static int dat_anz = 0;

static struct dat_desc **dat = (struct dat_desc **) NULL;

/* ---------------------------------------------------------------------- *
 * Funktion         : Alloc und Free der Dateibeschreibungs-Puffer        *
 * ---------------------------------------------------------------------- */

static void stru_free( int i )
  {
    free( dat[i]->datei );
    if ( dat[i]->buflng > 0 )
       free( dat[i]->buffer );
    free( dat[i] );
   }

static int stru_alloc( int i, char *datei, int fd, int buflng, ASC_FKT *af )
  {
    int j;
    int neu_fd;

    dat[i] = ( struct dat_desc * ) malloc( sizeof( struct dat_desc ) );
    if ( dat[i] == (struct dat_desc *) NULL ) return 0;
    dat[i]->datei = malloc( strlen(datei) + 1 );
    if ( dat[i]->datei == NULL )
      { free( dat[i] );
        return -1 ;
       }
    if ( buflng > 0 )
      {
        dat[i]->buffer = malloc(buflng + 1);    /* + 1 : neu 25.09.95 */
        if ( dat[i]->buffer == NULL )
          { free(dat[i]->datei);
            free(dat[i]);
            return -1;
           }
       }
    strcpy( dat[i]->datei, datei );
    dat[i]->fd     = fd;
    dat[i]->buflng = buflng;
    dat[i]->bufend = 0;
    dat[i]->bufref = 0;
    dat[i]->af     = af;
    neu_fd  = -1;
    for ( j = 0; j < i; j++ )
       if ( neu_fd < dat[j]->datfd ) neu_fd = dat[j]->datfd;
    dat[i]->datfd = neu_fd + 1;
    return dat[i]->datfd;
   }

static void buf_free( void )
  {
    if ( dat != (struct dat_desc **) NULL ) free( dat );
    dat = NULL;
   }

static int buf_alloc( int anz )
  {
    if ( anz == 0 )
      { buf_free( );
        return 1 ;
       }
    if ( dat == ( struct dat_desc ** ) NULL )
         dat =  ( struct dat_desc ** ) malloc( anz*sizeof(char *) );
       else
         dat =  ( struct dat_desc ** ) realloc( dat, anz*sizeof(char *) );
    if ( dat ==  ( struct dat_desc ** ) NULL ) return 0;
    return 1;
   }

static int get_fd( int datfd, int *ind )
  {
    int i;
    i = 0;
    while ( i < dat_anz )
     { if ( dat[i]->datfd == datfd )
         { *ind = i;
           return dat[i]->fd;
          }
       i++;
      }
    *ind = -1;
    return -1;
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscOpen( )                                          *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Oeffnet eine Datei                                  *
 * Eingabe-Parameter: datei  = Dateiname                                  *
 *                    mode   = "w", "r" , "a" (analog fopen)              *
 *                    buflg  = Interne Pufferlaenge                       *
 * Ausgabe-Parameter: datfd  = Dateikennzahl                              *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscOpen( char *datei, char *mode, int *datfd, int buflng, ASC_FKT *af )
#else
int AscOpen( datei, mode, datfd, buflng, af )
  char *datei;
  char *mode;
  int  *datfd;
  int  buflng;
  ASC_FKT *af;
#endif
  {
    int fd;
/*
    if ( af == NULL ) af = &AscNormFkt;
*/
    *datfd = -1;
    fd = (*af->open)( datei, mode );
    if ( fd == -1 ) return RDA_NOFILE;

    if ( !buf_alloc( dat_anz + 1 ) )
      { (*af->close)( fd ) ;
        return RDA_ALLOC1;
       }

    *datfd = stru_alloc( dat_anz, datei, fd, buflng, af );
    if ( *datfd == -1 )
      { (*af->close)( fd ) ;
        buf_alloc( dat_anz );
        return RDA_ALLOC2;
       }
    dat_anz++;
    return  RDA_OK;
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscOpenRd( )                                        *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Oeffnet eine Datei zum Lesen                        *
 * Eingabe-Parameter: datei  = Dateiname                                  *
 *                    buflg  = Interne Pufferlaenge                       *
 * Ausgabe-Parameter: datfd  = Dateikennzahl                              *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscOpenRd( char *datei, int *datfd, int buflng, ASC_FKT *af )
#else
int AscOpenRd( datei, datfd, buflng, af )
  char *datei;
  int  *datfd;
  int  buflng;
  ASC_FKT *af;
#endif
  {
    return AscOpen( datei, "r", datfd, buflng, af );
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscOpenCr( )                                        *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Legt eine Datei an und oeffnet sie zum Schreiben    *                *
 * Eingabe-Parameter: datei  = Dateiname                                  *
 * Ausgabe-Parameter: datfd  = Dateikennzahl                              *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscOpenCr ( char *datei, int *datfd, ASC_FKT *af )
#else
int AscOpenCr ( datei, datfd, af )
  char *datei;
  int  *datfd;
  ASC_FKT *af;
#endif
  {
    return AscOpen( datei, "w", datfd, 0, af );
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscClose( )                                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Schliesst eine Datei                                *                *
 * Eingabe-Parameter: datfd  = Dateikennzahl                              *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscClose( int datfd )
#else
int AscClose( datfd )
  int datfd;
#endif
  {
    int  i;
    int  j;
    int  fd;

    fd = get_fd( datfd, &i );
    if ( fd == -1 ) return RDA_NOPEN;

    ( *dat[i]->af->close ) ( fd );
    stru_free( i );
    dat_anz--;
    for ( j = i; j < dat_anz; j++ ) dat[j] = dat[j+1];
    buf_alloc( dat_anz );
    return  RDA_OK;
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscRewind()                                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Rewind   Datei                                      *                *
 * Eingabe-Parameter: datfd  = Dateikennzahl                              *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscRewind( int datfd )
#else
int AscRewind( datfd )
  int datfd;
#endif
  {
    int  i;
    int  fd;

    fd = get_fd( datfd, &i );
    if ( fd == -1 ) return RDA_NOPEN;

    ( *dat[i]->af->rewind ) ( fd );

    dat[i]->bufend = 0;
    dat[i]->bufref = 0;
    return  RDA_OK;
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscRead()                                           *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Liest die Naechste Zeile                            *                *
 * Eingabe-Parameter: datfd  = Dateikennzahl                              *
 *                    Zeile  = Zeiger auf den Puffer                      *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscRead( char *zeile, int  datfd )
#else
int AscRead( zeile, datfd )
  char *zeile;
  int  datfd;
#endif
  {
    int  i;
    int  j;
    int  ok, notend;
    char ze;
    int  fd;

    fd = get_fd( datfd, &i );
    if ( fd == -1 ) return RDA_NOPEN;

    ok = 1;
    notend = 1;
    j  = 0;
    while (ok && notend)
      { if ( dat[i]->bufref == dat[i]->bufend )
          {
            dat[i]->bufend =
                (*dat[i]->af->read) ( fd, dat[i]->buffer, dat[i]->buflng );
            dat[i]->bufref = 0;
           }
        ze = dat[i]->buffer[dat[i]->bufref++];
        notend = dat[i]->bufend > 0;
        if (notend)
          { switch(ze)
              { case TAB:
                  do { zeile[j++] = ' '; } while ( j%8 != 0 );
                  break;
                case LF:
                  /* EndBlanks entfernen */
                  j--;
                  while ( j >= 0 && zeile[j] == ' ' ) j--;
                  j++;
                  zeile[j] = '\0';
                  ok = 0;
                  break;
                case CR:
                  break;
                case DEND:
           /*     ok = 0;
                  notend = 0;
                  zeile[j] = '\0';
           */
                  break;
                default:
                  zeile[j++] = ze;
                  break;
               }
           }
       }
    if ( notend )
       return  RDA_OK;
     else
       return  RDA_EOF;
   }

/* ---------------------------------------------------------------------- *
 * Funktion         : AscWriteLng( )                                      *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Schreibt einen Puffer der Laenge lng                *                *
 * Eingabe-Parameter: datfd  = Dateikennzahl                              *
 *                    Zeile  = Zeiger auf den Puffer                      *
 *                    lng    = Pufferlaenge                               *
 * Return-Wert      : keiner                                              *
 * ---------------------------------------------------------------------- */

#ifdef __STDC__
int AscWriteLng( char *zeile, int lng, int datfd )
#else
int AscWriteLng( zeile, lng, datfd )
  char *zeile;
  int  lng;
  int  datfd;
#endif
  {
    int  j;
    int  i;
/*
    int  k;
    int  pos;
*/
    int  fd;

    fd = get_fd( datfd, &i );
    if ( fd == -1 ) return RDA_NOPEN;

    if ( lng == 0 )   return RDA_EOF;
    j = lng - 1;
    while ( j >= 0 && zeile[j] == ' ' ) j--;
    j++;
/*
    k = 0;
    pos = dat[i]->bufend;
    while ( k < j )
      {
        if ( pos == dat[i]->buflng )
          {
            fwrite( dat[i]->buffer, 1, pos, fd );
            pos = 0;
           }
        dat[i]->buffer[pos++] = zeile[k++];
       }
*/
    if ( j > 0 )
        (*dat[i]->af->write) ( fd, zeile, j );
    (*dat[i]->af->write) ( fd, eol,   1 );
    return  RDA_OK;
   }

