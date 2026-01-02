
/* ---------------------------------------------------------------------- *
 *                            ZPDATACARELF.c                              *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Datacare verwalten                                  *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 26.01.05                                            *
 *   letztes Update :                                                     *
 *   Autor          : K.Hinz  ( Kopie von ZPIFALF.C)                      *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.0 zpdatacarelf : 18/03/2013 : Rolf Raab";
}

/*!
\page page10 zpdatacarelf - Datacare verwalten
________________________________________________________________________________________
\version	1.1.0
\date		18.03.2013
\internal
- TH: AIX build
\endinternal
_______________________________________________________________________________________
\version	1.0.3
\date		27.10.2008
\internal
- RR: ret_buf von 1000 auf 2000 Bytes vergrößert (wg. zu hoher Anzahl Verzeichnisse).
\endinternal
_______________________________________________________________________________________
\version	1.0.2
\date		07.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal

*/

/* 1.0.2  07.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						 Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.0.3  27.10.2008 RR: ret_buf von 1000 auf 2000 Bytes vergrößert (wg. zu hoher Anzahl Verzeichnisse) */
/* 1.1.0  18.03.2013 TH: AIX build */


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ----- Prototype --------- */

long GetDatacareVerz( char *SatzartMode, char *buf, int gepackt );
long CreateDatacareVerz( char* QuellDirec, char *buf, int WithCopy );

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void GetDatacareVerzUsage( char *buf )
{
  strcat( buf, "1. Datacare-Verzeichnisse lesen:\n" \
               "   zpdatacarelf 1 [mode] [p]\n" \
               "     gibt die Datacare-Verzeichnisse aus\n" \
               "     ohne mode: alle Verzeichnisse\n" \
               "     mode = 0:  alle Verz. mit ArtikelStatus = unbearbeitet\n" \
               "     mode = 9:  alle Verz. mit Unterverzeichnis 'protokol'\n" \
               "     p       :  wenn mit p, dann Ausgabe gepackt\n" );
}

static void CreateDatacareVerzUsage( char *buf )
{
  strcat( buf, "2. Datacare-Verzeichnis erstellen:\n"\
               "   zpdatacarelf 2 [Quellverzeichnis] [c]\n" \
/*             "     erstellt im Verzeichnis $WSS/daten/datacareneud\n"  \ */
               "     erstellt im Verzeichnis $WSS/at/cdm/data/datacare\n"  \
               "     ein neues Datacare-Verzeichnis der Form lf000000\n" \
               "     Quellverzeichnis: Verzeichnis der Datacare-Dateien\n"\
/*             "              default: $WSS/daten/datacareneud/lfakt\n" \ */
               "              default: $WSS/at/cdm/data/datacare/lfakt\n" \
               "     c: Kopieren der Datacare-Dateien aus dem Quellverzeichnis\n" \
               "        in das neue Datacare-Verzeichnis\n" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   GetDatacareVerzUsage( buf );
   CreateDatacareVerzUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 1 )
        {
           s = GetDatacareVerz ( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "p" ) == 0 )
        {
           s = GetDatacareVerz ( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
           s = GetDatacareVerz ( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp ( argv[2], "p" ) == 0 )
        {
           s = GetDatacareVerz ( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          GetDatacareVerzUsage( buf );
        }
        break;

      case '2':
        if ( argc == 1 )
        {
          s = CreateDatacareVerz( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "c" ) == 0 )
        {
          s = CreateDatacareVerz( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
          s = CreateDatacareVerz( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp( argv[2], "c" ) == 0 )
        {
          s = CreateDatacareVerz( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          CreateDatacareVerzUsage( buf );
        }
        break;

      default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }
   return s;
}


