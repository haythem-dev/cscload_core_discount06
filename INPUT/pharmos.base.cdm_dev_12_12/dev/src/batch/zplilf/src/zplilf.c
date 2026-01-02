
/* ---------------------------------------------------------------------- *
 *                            ZPDATACARELF.c                              *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : LogIndex verwalten                                  *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 26.10.13                                            *
 *   letztes Update :                                                     *
 *   Autor          : T.Hörath  ( Kopie von ZPIFALF.C)                    *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.0.0 zplilf : 29/10/2013 : Thomas Hörath";
}

/*!
\page page29 zplilf
___________________________________________________________________________
\version	1.0.0
\date		18.03.2013
\internal
- TH: Initialisiert
\endinternal

*/

/* 1.0.0  18.03.2013 TH: 1st shot */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ----- Prototype --------- */

long GetLogindexVerz( char *SatzartMode, char *buf, int gepackt );
long CreateLogindexVerz( char* QuellDirec, char *buf, int WithCopy );

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void GetLogindexVerzUsage( char *buf )
{
  strcat( buf, "1. Logindex-Verzeichnisse lesen:\n" \
               "   zplilf 1 [mode] [p]\n" \
               "     gibt die Logindex-Verzeichnisse aus\n" \
               "     ohne mode: alle Verzeichnisse\n" \
               "     mode = 0:  alle Verz. mit ArtikelStatus = unbearbeitet\n" \
               "     mode = 9:  alle Verz. mit Unterverzeichnis 'protokol'\n" \
               "     p       :  wenn mit p, dann Ausgabe gepackt\n" );
}

static void CreateLogindexVerzUsage( char *buf )
{
  strcat( buf, "2. Logindex-Verzeichnis erstellen:\n"\
               "   zplilf 2 [Quellverzeichnis] [c]\n" \
               "     erstellt im Verzeichnis $WSS/ch/cdm/ws/data/logindex\n"  \
               "     ein neues Logindex-Verzeichnis der Form lf000000\n" \
               "     Quellverzeichnis: Verzeichnis der Logindex-Dateien\n"\
               "              default: $WSS/ch/cdm/ws/data/logindex/lfakt\n" \
               "     c: Kopieren der Logindex-Dateien aus dem Quellverzeichnis\n" \
               "        in das neue Logindex-Verzeichnis\n" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   GetLogindexVerzUsage( buf );
   CreateLogindexVerzUsage( buf );
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
           s = GetLogindexVerz ( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "p" ) == 0 )
        {
           s = GetLogindexVerz ( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
           s = GetLogindexVerz ( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp ( argv[2], "p" ) == 0 )
        {
           s = GetLogindexVerz ( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          GetLogindexVerzUsage( buf );
        }
        break;

      case '2':
        if ( argc == 1 )
        {
          s = CreateLogindexVerz( NULL, buf, 0 );
        }
        else if ( argc == 2 && strcmp( argv[1], "c" ) == 0 )
        {
          s = CreateLogindexVerz( NULL, buf, 1 );
        }
        else if ( argc == 2 )
        {
          s = CreateLogindexVerz( argv[1], buf, 0 );
        }
        else if ( argc == 3 && strcmp( argv[2], "c" ) == 0 )
        {
          s = CreateLogindexVerz( argv[1], buf, 1 );
        }
        else
        {
          s = 1;
          Usage( buf );
          CreateLogindexVerzUsage( buf );
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


